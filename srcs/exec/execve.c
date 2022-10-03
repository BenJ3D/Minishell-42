/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:32:10 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/04 00:41:35 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>

// ft_lstcmd_to_cmdarg_for_execve

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

int	ft_command_not_found_message(char **argv, t_data *data)
{
	char *line2;

	if (argv[0] != NULL)
	{

		line2 = ft_strjoin_max("%s%s: %s%s: %scommand not found%s\n",
								COLOR_CYAN, data->pgr_name, COLOR_PURPLE, 
								argv[0], COLOR_RED, COLOR_NONE);
		ft_putstr_fd(line2, 2);
		free(line2);
	}
	else
		return (1);
	return (0);
}

int	ft_create_fork_pipe_out();

/**
 * @brief //TODO: check parmit une liste si il y a une builtin
 * 
 * @return int 
 */
int	ft_exec_is_builtin(t_data *data, char **argv, \
												t_cmdtab *cmdtab, t_execarg *ex) //TODO: TODO:
{
	if (*argv ==  NULL)
		return (0);
	else if (cmdtab[ex->i].isbuilt == BUILT_CD)
		ft_builtin_cd(data->env, argv);
	else if (cmdtab[ex->i].isbuilt == BUILT_ECHO)
		ft_builtin_echo(argv);
	else if (cmdtab[ex->i].isbuilt == BUILT_ENV)
		ft_builtin_env(data->env);
	else if (cmdtab[ex->i].isbuilt == BUILT_EXIT)
		ft_exit(data);
	else if (cmdtab[ex->i].isbuilt == BUILT_EXPORT)
		ft_builtin_export(data->env, argv);
	else if (cmdtab[ex->i].isbuilt == BUILT_PWD)
		ft_builtin_pwd(data->env, argv);
	else if (cmdtab[ex->i].isbuilt == BUILT_UNSET)
		ft_builtin_unset(data->env, argv);
	return (0);
}

/**
 * @brief		check si argv[0] est une builtin
 * 
 * @return int return 0 if not built-in; else return 1 to 7 builtin type
 */
int	ft_check_is_builtin(t_data *data, char **argv, t_cmdtab *cmdtab, t_execarg *ex) //TODO: TODO:
{	
	if (*argv ==  NULL)
		return (-1);
	if (!ft_strncmp(argv[0], "cd", 3))
		cmdtab[ex->i].isbuilt = BUILT_CD;
	else if (!ft_strncmp(argv[0], "echo", 5))
		cmdtab[ex->i].isbuilt = BUILT_ECHO;
	else if (!ft_strncmp(argv[0], "env", 4))
		cmdtab[ex->i].isbuilt = BUILT_ENV;
	else if (!ft_strncmp(argv[0], "export", 7))
		cmdtab[ex->i].isbuilt = BUILT_EXPORT;
	else if (!ft_strncmp(argv[0], "unset", 6))
		cmdtab[ex->i].isbuilt = BUILT_UNSET;
	else if (!ft_strncmp(argv[0], "pwd", 4))
		cmdtab[ex->i].isbuilt = BUILT_PWD;
	else if (!ft_strncmp(argv[0], "exit", 5))
		cmdtab[ex->i].isbuilt = BUILT_EXIT;
	else
		cmdtab[ex->i].isbuilt = NO_BUILTIN;
	
	return (cmdtab[ex->i].isbuilt);
}

// /**
//  * @brief //TODO: check parmit une liste si il y a une builtin
//  * 
//  * @return int 
//  */
// int	ft_check_is_builtin(t_data *data, char **argv, \
// 												t_cmdtab *cmdtab, t_execarg *ex) //TODO: TODO:
// {	
// 	int	ret;
// 	ret = 0;
// 	if (*argv ==  NULL)
// 		return (0);
// 	if (cmdtab[ex->i].pipeout == 1)
// 		ret = ft_check_is_builtin_with_pipe(data, argv, cmdtab, ex);
// 	if (!ft_strncmp(argv[0], "cd", 3) && cmdtab[ex->i].pipeout == 0)
// 		ft_builtin_cd(data->env, argv);
// 	else if (!ft_strncmp(argv[0], "echo", 5) && cmdtab[ex->i].pipeout == 0)
// 		ft_builtin_echo(argv);
// 	else if (!ft_strncmp(argv[0], "env", 4) && cmdtab[ex->i].pipeout == 0)
// 		ft_builtin_env(data->env);
// 	else if (!ft_strncmp(argv[0], "exit", 5) && cmdtab[ex->i].pipeout == 0)
// 		ft_exit(data);
// 	else if (!ft_strncmp(argv[0], "export", 7) && cmdtab[ex->i].pipeout == 0)
// 		ft_builtin_export(data->env, argv);
// 	else if (!ft_strncmp(argv[0], "pwd", 4) && cmdtab[ex->i].pipeout == 0)
// 		ft_builtin_pwd(data->env, argv);
// 	else if (!ft_strncmp(argv[0], "unset", 6) && cmdtab[ex->i].pipeout == 0)
// 		ft_builtin_unset(data->env, argv);
// 	else
// 		return (1);
// 	return (ret);
// }

int	ft_forkexe(t_data *data, t_execarg *ex, t_cmdtab *cmdtab)
{
	char	**envp;
	pid_t	father;

	father = fork();
	if (father == 0)
	{
		if (cmdtab[ex->i].pipeout == 1)
			dup2(cmdtab[ex->i + 1].fd[1], STDOUT_FILENO);
		if (cmdtab[ex->i].pipein == 1)
		{
			dup2(cmdtab[ex->i].fd[0], STDIN_FILENO);
			close(cmdtab[ex->i].fd[0]);
		}
		envp = ft_env_convert_envlst_to_tab(data->env);
		execve(ex->progpath, ex->argv, envp);
		free(ex->progpath);
		ft_free_tab_char(ex->argv);
		ft_free_tab_char(envp);
		ft_exit(data); // FIXME: utile ?
	}
	if (cmdtab[ex->i].pipeout == 1)
		close(cmdtab[ex->i + 1].fd[1]);
	// close(data->fd[0]);
	// close(data->fd[1]);
	return (father);
}

int	ft_cmdtab_init_info(t_cmdtab *cmdtab)
{
	int	i;

	i = 0;
	while(cmdtab[i].lst)
	{
		cmdtab[i].pipeout = 0;
		cmdtab[i++].pipein = 0;
	}
	i = 0;
	while(cmdtab[i].lst)
	{
		if (i > 0)
		{
				cmdtab[i].pipein = 1;
			if (ft_check_if_cmd_has_pipe(cmdtab[i].lst))
				cmdtab[i].pipeout = 1;
		}
		else 
		{
				cmdtab[i].pipein = 0;
			if (ft_check_if_cmd_has_pipe(cmdtab[i].lst))
				cmdtab[i].pipeout = 1;
		}
		i++;
	}
	return (0);
}

int	ft_create_pipe(t_cmdtab *cmdtab, t_execarg *ex)
{
	if (ex->i == 0)
		pipe(cmdtab[ex->i].fd);
	pipe(cmdtab[ex->i + 1].fd);
	return (0);
}

int	ft_run_execve(t_cmdtab *cmdtab, t_data *data)
{
	t_execarg	ex;
	int			ret;
	pid_t		child;

	ex.i = 0;
	ft_cmdtab_init_info(cmdtab);
	while(cmdtab[ex.i].lst)
	{
		if (cmdtab[ex.i].pipeout)
			ft_create_pipe(cmdtab, &ex);
		ex.argv = ft_lstcmd_to_cmdarg_for_execve(cmdtab[ex.i].lst); //TODO:
		ex.progpath = ft_check_if_prog_exist_in_pathenv(ex.argv[0], data->env);
		ret = ft_check_is_builtin(data, ex.argv, cmdtab, &ex);
		if (!ex.progpath && ret == 1)
			ft_command_not_found_message(ex.argv, data);
		else if (ex.progpath && ret == 1) // ret 1 pour ne pas faire la buitin + le prog trouver
			child = ft_forkexe(data, &ex, cmdtab);
		free(ex.progpath);
		ex.i++;
		ft_free_tab_char(ex.argv);
	}
	while (cmdtab[ex.i].lst)
	{
		close(cmdtab[ex.i].fd[0]);
		close(cmdtab[ex.i].fd[1]);
		ex.i++;
	}
	waitpid(child, NULL, 0);
	ex.i = 0;
	// ft_free_tab_char(envp); //\\ deplacer dans le if father == 0
	return (0);
}