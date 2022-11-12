/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_findprog.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:32:10 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/12 19:10:38 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_check_if_prog_exist_in_pathenv_2(char *progname, t_envlst *envlst)
{
	char	*envpaths;
	char	**pathsplit;
	char	*pathhascheck;
	int		i;

	envpaths = ft_env_getstr_env_value(envlst, "PATH");
	if (!envpaths)
		return (NULL);
	pathsplit = ft_split(envpaths, ':');
	i = 0;
	while (pathsplit[i])
	{
		pathhascheck = ft_strjoin_max("%s/%s", pathsplit[i], progname);
		if (!access(pathhascheck, X_OK))
		{
			ft_free_tab_char(pathsplit);
			free (envpaths);
			return (pathhascheck);
		}
		i++;
		free(pathhascheck);
	}
	ft_free_tab_char(pathsplit);
	free (envpaths);
	return (NULL);
}

/**
 * @brief check dans tous les path présent dans env si un programe existe
 * 
 * @param progname
 * @param envlst
 * @return char* return le path complet si il existe, null à l'inverse
 */
char	*ft_check_if_prog_exist_in_pathenv(char *progname, t_envlst *envlst)
{
	char	*pathhascheck;

	if (!progname)
		return (NULL);
	if (progname[0] == '/')
	{
		if (!access(progname, X_OK))
		{
			pathhascheck = ft_strdup(progname);
			return (pathhascheck);
		}
	}
	pathhascheck = ft_strjoin_max("%s", progname);
	if (ft_strlen(pathhascheck) >= 3)
		if (pathhascheck[0] == '.')
			if (!access(pathhascheck, X_OK))
				return (pathhascheck);
	free(pathhascheck);
	pathhascheck = ft_check_if_prog_exist_in_pathenv_2(progname, envlst);
	if (pathhascheck != NULL)
		return (pathhascheck);
	return (NULL);
}
