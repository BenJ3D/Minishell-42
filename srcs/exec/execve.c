/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:32:10 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/22 01:20:46 by bducrocq         ###   ########.fr       */
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
	if (!envpaths)
		return (NULL);
	if (!progname)
	{
		free (envpaths);
		return (NULL);
	}
	pathsplit = ft_split(envpaths, ':');
	i = 0;
	while (pathsplit[i])
	{
		pathhascheck = ft_strjoin_max("%s/%s", pathsplit[i], progname);
		if (!access(pathhascheck, X_OK)) // TODO: FIXME: peut etre check exe
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

int	ft_command_not_found_message(t_data *data)
{
	char *line2;

	if (data->buffer[0] != '\0')
	{

		line2 = ft_strjoin_max("%sMiniHell: %s%s: %scommand not found%s\n",
							   COLOR_CYAN, COLOR_PURPLE, data->buffer, 
							   COLOR_RED, COLOR_NONE);
		ft_putstr_fd(line2, 2);
		free(line2);
	}
	return (0);
}

/**
 * @brief //TODO: check parmit une liste si il y a une builtin
 * 
 * @return int 
 */
int	ft_check_builtin(t_data	*data, char **argv)
{
	if (*argv ==  NULL)
		return (0);
	else if (!ft_strncmp(argv[0], "cd", 3))
		ft_builtin_cd(data->env, argv);
	else if (!ft_strncmp(argv[0], "echo", 5))
		ft_builtin_echo(argv);
	else if (!ft_strncmp(argv[0], "env", 4))
		ft_builtin_env(data->env);
	else if (!ft_strncmp(argv[0], "exit", 5))
		ft_exit(data);
	else if (!ft_strncmp(argv[0], "export", 7))
		ft_builtin_export(data->env, argv);
	else if (!ft_strncmp(argv[0], "pwd", 4))
		ft_builtin_pwd(data->env, argv);
	else if (!ft_strncmp(argv[0], "unset", 6))
		ft_builtin_unset(data->env, argv);
	else 
		return (1);
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
	int		ret;

	argv = ft_lstcmd_to_cmdarg_for_execve(cmdtab[0].lst);
	// dbg_display_argv(argv);
	progpath = ft_check_if_prog_exist_in_pathenv(argv[0], data->env);
	ret = ft_check_builtin(data, argv);
	if (!progpath && ret == 1)
			ft_command_not_found_message(data);
	else if (progpath && ret == 1) // ret 1 pour ne pas faire la buitin + le prog trouver
	{
		father = fork();
		if (father > 0)
			wait(0);
		if (father == 0)
		{
			envp = ft_env_convert_envlst_to_tab(data->env);
			execve(progpath, argv, envp);
			free (progpath);
			ft_free_tab_char(argv);
			ft_free_tab_char(envp);
			
			ft_exit(data);
		} 
	}
	free (progpath);
	ft_free_tab_char(argv);
	// ft_free_tab_char(envp); //\\ deplacer dans le if father == 0
	return (0);
}