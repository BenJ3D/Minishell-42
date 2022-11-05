/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/05 02:04:02 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_builtin_cd_change_pwdenv(t_envlst *env, char *newpwd, char *oldpwd)
{
	ft_builtin_export_api(env, "PWD", newpwd);
	ft_builtin_export_api(env, "OLDPWD", oldpwd);
	return (0);
}

int	ft_builtin_cd(t_envlst *env, char **argv, t_data *data)
{
	char	*errline;
	char	*gethome;
	char	*currentpwd;

	g_status = 0;
	currentpwd = getcwd(NULL, PATH_MAX);
	if (argv[1][0] == '.' && argv[1][0] == '\0')
		return (0);
	if (argv[1] == '\0')
	{
		gethome = ft_env_getstr_env_value(env, "HOME");
		if (gethome != NULL)
		{
			if (chdir(gethome))
			{
				g_status = errno;
				errline = ft_strjoin_max("%s%s: %s%s%s", COLOR_CYAN, \
					data->pgr_name, COLOR_PURPLE, argv[1], COLOR_RED);
				perror(errline);
				free (errline);
			}
			ft_builtin_cd_change_pwdenv(env, gethome, currentpwd);
			free (gethome);
			free (currentpwd);
		}
	}
	else if (chdir(argv[1]))
	{
		g_status = errno;
		errline = ft_strjoin_max("%s%s: %s%s%s", COLOR_CYAN, \
			data->pgr_name, COLOR_PURPLE, argv[1], COLOR_RED);
		perror(errline);
		free (errline);
		return (1);
	}
	else
		ft_builtin_cd_change_pwdenv(env, argv[1], currentpwd);
	return (g_status);
}
