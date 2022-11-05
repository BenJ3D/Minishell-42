/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/05 19:58:26 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_builtin_cd_change_pwdenv(t_envlst *env, char *newpwd, char *oldpwd)
{
	ft_builtin_export_api(env, "PWD", newpwd);
	ft_builtin_export_api(env, "OLDPWD", oldpwd);
	return (0);
}


int	ft_builtin_cd_point(t_envlst *env, char **argv, t_data *data)
{


}

int	ft_builtin_cd(t_envlst *env, char **argv, t_data *data)
{
	char	*errline;
	char	*futurpwd;
	char	*currentpwd;

	g_status = 0;
	currentpwd = getcwd(NULL, PATH_MAX);
	if (argv[1] == NULL)
	{
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
			free (currentpwd);
		}
		return (0);
	}
	else if (argv[1][0] == '.' && argv[1][1] == '\0')
	{
		free (currentpwd);
		return (0);
	}
	else if (argv[1][0] == '-' && argv[1][1] == '\0')
	{
		futurpwd = ft_env_getstr_env_value(env, "OLDPWD");
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
			free (currentpwd);
			ft_builtin_pwd();
		}
		else
		{
			ft_err_display_line_error(data, "cd", "OLDPWD not set");
			g_status = 1;
		}
		return (0);
	}
	else if (chdir(argv[1]))
	{
		g_status = errno;
		errline = ft_strjoin_max("%s%s: %s%s%s", COLOR_CYAN, \
			data->pgr_name, COLOR_PURPLE, argv[1], COLOR_RED);
		perror(errline);
		free (errline);
		free (currentpwd);
		return (1);
	}
	futurpwd = getcwd(NULL, PATH_MAX);
	ft_builtin_cd_change_pwdenv(env, futurpwd, currentpwd);
	free (futurpwd);
	free (currentpwd);
	return (0);
}
