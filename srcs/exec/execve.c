/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:32:10 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/21 20:55:48 by bducrocq         ###   ########.fr       */
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
char	*ft_check_if_prog_exist_in_pathenv(char *progname, t_envlst *envlst) //TODO: norm
{
	char		*envpaths;
	char		**pathsplit;
	char		*pathhascheck;
	int			i;
	
	pathhascheck = NULL;
	envpaths = ft_env_getstr_env_value(envlst, "PATH");
	if (!envpaths || !progname)
		return (NULL);
	pathsplit = ft_split(envpaths, ':');
	i = 0;
	while (pathsplit[i])
	{
		if (pathhascheck)
			free (pathhascheck);
		pathhascheck = ft_strjoin_max("%s/%s", pathsplit[i], progname);
		if (!access(pathhascheck, R_OK))
		{
			ft_free_tab_char(pathsplit);
			free (envpaths);
			return (pathhascheck);
		}
		i++;
	}
	ft_free_tab_char(pathsplit);
	free (envpaths);
	return (NULL);
}

/**
 * @brief //TODO: check parmit une liste si il y a une builtin
 * 
 * @return int 
 */
int	ft_check_if_builtin(void)
{

	return (0);
}

/**
 * @brief //TODO: filtre pour savoir si exe une builtin ou non et creer le fork
 * 
 * @param cmdtab 
 * @param data 
 * @return int 
 */
int	ft_filter_cmdtab_before_execve(t_cmdtab *cmdtab, t_data *data)
{
	
	return (0);
}

int	ft_run_execve(t_cmdtab *cmdtab, t_data *data)
{
	char	**argv;
	char	**envp;
	char	*progpath;
	pid_t	father;

	argv = ft_lstcmd_to_cmdarg_for_execve(cmdtab[0].lst);
	// dbg_display_argv(argv);
	progpath = ft_check_if_prog_exist_in_pathenv(argv[0], data->env);
	envp = ft_env_convert_envlst_to_tab(data->env);
	if (progpath)
	{
		father = fork();
		if (father > 0)
			wait(0);
		if (father == 0)
		{
			execve(progpath, argv, envp);
			free (progpath);
			ft_free_tab_char(argv);
			ft_free_tab_char(envp);
			
			ft_exit(data);
		} 
	}
	free (progpath);
	ft_free_tab_char(argv);
	ft_free_tab_char(envp);
	return (0);
}