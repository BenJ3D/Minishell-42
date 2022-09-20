/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:32:10 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/20 18:26:05 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>

// ft_lstcmd_to_cmdarg_for_execve

char	*get_next_path(char *envpaths)
{
	char		*path;
	int			i;
	static int	ipath = 0;
	
	i = ipath;
	while(envpaths[i])
	{
		if (envpaths[i++] == ':')
		{
			ipath = i + 1;
			break;
		}
	}
	path = ft_calloc(i + 1, sizeof(path));
	ft_strlcpy(path, (envpaths + ipath), i);

	return (path);
}

/**
 * @brief check dans tous les path présent dans env si un programe existe
 * 
 * @param progname 
 * @param envlst 
 * @return char* return le path complet si il existe, null à l'inverse
 */
char	*ft_check_if_prog_exist_in_pathenv(char *progname, t_envlst *envlst) //TODO:
{
	char		*envpaths;
	char		**pathsplit;
	int			i;

	envpaths = ft_env_getstr_env_value(envlst, "PATH");
	pathsplit = ft_split(envpaths, ':');
	i = 0;
	while (pathsplit[i])
	{
		printf("dbgGetNextPath:%s\n", pathsplit[i++]);
	}
	ft_free_tabstr(pathsplit);
	free (envpaths);
	return (NULL);
}

int	ft_run_execve(t_cmdtab *cmdtab, t_data *data)
{
	char	**argv;
	char	**envp;
	char	*progpath;
	int		ipath;

	ipath = 0;
	argv = ft_lstcmd_to_cmdarg_for_execve(cmdtab[0].lst);
	dbg_display_argv(argv);
	ft_check_if_prog_exist_in_pathenv(argv[0], data->env);
	
	envp = ft_env_convert_envlst_to_tab(data->env);
	execve(progpath, argv, envp);
	ft_free_tabstr(argv);
	ft_free_tabstr(envp);
	return (0);
}