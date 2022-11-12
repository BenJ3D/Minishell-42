/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/12 19:10:38 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_builtin_cd_change_pwdenv(t_envlst *env, \
													char *newpwd, char *oldpwd)
{
	if (newpwd)
		ft_builtin_export_api(env, "PWD", newpwd);
	if (oldpwd)
		ft_builtin_export_api(env, "OLDPWD", oldpwd);
	return (0);
}

static int	ft_builtin_cd_point(t_envlst *env, char **argv, \
											char *currentpwd, t_data *data)
{
	char	*futurpwd;
	char	*errline;

	futurpwd = ft_env_getstr_env_value(env, "HOME");
	if (futurpwd != NULL)
	{
		if (chdir(futurpwd))
		{
			g_status = errno;
			errline = ft_strjoin_max("%s%s: %s%s%s", COLOR_CYAN, \
				data->pgr_name, COLOR_PURPLE, argv[1], COLOR_RED);
			perror(errline);
			free (errline);
			return (1);
		}
		ft_builtin_cd_change_pwdenv(env, futurpwd, currentpwd);
		free (futurpwd);
	}
	return (0);
}

static int	ft_builtin_cd_moins(t_envlst *env, char **argv, \
								char *currentpwd, t_data *data)
{
	char	*futurpwd;
	char	*errline;

	futurpwd = ft_env_getstr_env_value(env, "OLDPWD");
	if (futurpwd != NULL)
	{
		if (chdir(futurpwd))
		{
			errline = ft_strjoin_max("%s%s: %s%s%s", COLOR_CYAN, \
				data->pgr_name, COLOR_PURPLE, argv[1], COLOR_RED);
			perror(errline);
			free (errline);
			return ((g_status = errno));
		}
		ft_builtin_cd_change_pwdenv(env, futurpwd, currentpwd);
		free (futurpwd);
		ft_builtin_pwd(data);
		return (g_status = 0);
	}
	else
		ft_err_display_line_error(data, "cd", "OLDPWD not set");
	free (futurpwd);
	return ((g_status = 1));
}

static int	ft_builtin_cd_err(char **argv, t_data *data)
{
	char	*errline;

	g_status = errno;
	errline = ft_strjoin_max("%s%s: %s%s%s", COLOR_CYAN, \
		data->pgr_name, COLOR_PURPLE, argv[1], COLOR_RED);
	perror(errline);
	free (errline);
	return (g_status);
}

int	ft_builtin_cd(t_envlst *env, char **argv, t_data *data, int ret)
{
	char	*futurpwd;
	char	currentpwd[PATH_MAX];

	g_status = 0;
	ft_bzero(currentpwd, PATH_MAX);
	if (!getcwd(currentpwd, PATH_MAX))
	{
		g_status = errno;
		ft_err_display_line_error(data, "cd", "No such file or directory");
	}
	if (argv[1] == NULL)
		ret = ft_builtin_cd_point(env, argv, currentpwd, data);
	else if (argv[1][0] == '.' && argv[1][1] == '\0')
		ret = 0;
	else if (argv[1][0] == '-' && argv[1][1] == '\0')
		ret = ft_builtin_cd_moins(env, argv, currentpwd, data);
	else if (chdir(argv[1]))
		ret = ft_builtin_cd_err(argv, data);
	else if (ret == 0 && currentpwd[0] != '\0')
	{
		futurpwd = getcwd(NULL, PATH_MAX);
		ft_builtin_cd_change_pwdenv(env, futurpwd, currentpwd);
		free(futurpwd);
	}
	return (ret);
}
