/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:32:10 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/25 22:00:58 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

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
	char	*envpaths;
	char	**pathsplit;
	char	*pathhascheck;
	int		i;

	if (!progname)
	{
		free (envpaths);
		return (NULL);
	}
	if(progname[0] == '/')
		if (!access(progname, X_OK))
		{
			pathhascheck = ft_strdup(progname);
			return (pathhascheck);
		}
	pathhascheck = ft_strjoin_max("%s", progname);
	if (ft_strlen(pathhascheck) >= 3) //tcheck avec repertoire courant
		if(pathhascheck[0] == '.')
			if (!access(pathhascheck, X_OK))
				return (pathhascheck);
	free(pathhascheck);
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

/**
 * @brief //TODO: check parmit une liste si il y a une builtin
 * 
 * @return int 
 */
int	ft_exec_is_builtin(t_data *data, char **argv, \
												t_cmdtab *cmdtab, t_execarg *ex) //TODO: TODO:
{
	if (*argv ==  NULL)
		return (-1);
	else if (cmdtab[ex->i].isbuilt == BUILT_CD)
		ft_builtin_cd(data->env, argv);
	else if (cmdtab[ex->i].isbuilt == BUILT_ECHO)
		ft_builtin_echo(argv);
	else if (cmdtab[ex->i].isbuilt == BUILT_ENV)
		ft_builtin_env(data->env);
	else if (cmdtab[ex->i].isbuilt == BUILT_EXIT)
		ft_exit(data);
	else if (cmdtab[ex->i].isbuilt == BUILT_EXPORT)
		ft_builtin_export(data->env, argv, data);
	else if (cmdtab[ex->i].isbuilt == BUILT_PWD)
		ft_builtin_pwd(data->env, argv);
	else if (cmdtab[ex->i].isbuilt == BUILT_UNSET)
		ft_builtin_unset(data, argv);
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

pid_t	ft_createfork(t_data *data, t_execarg *ex, char **envp)
{
	pid_t	father;
	
	if ((father = fork()) == -1)
		{
			perror("fork");
			free(ex->progpath);
			ft_free_tab_char(ex->argv);
			ft_free_tab_char(envp);
			ft_exit(data);
		}
	return (father);
}

int	ft_forkexe(t_data *data, t_execarg *ex, t_cmdtab *cmdtab)
{
	char	**envp;
	pid_t	father;
	
	father = -2;
	errno = 0;
	if ((cmdtab[ex->i].pipeout == 1) || (cmdtab[ex->i].pipein == 1) \
										|| (cmdtab[ex->i].isbuilt == 0))
		father = ft_createfork(data, ex, envp);

	if (father == 0)
	{
		ft_forkexe_dup_if_pipes(cmdtab, ex);
		if (ft_redirection(data, cmdtab, ex))
			exit (errno);
		envp = ft_env_convert_envlst_to_tab(data->env);
		if (cmdtab[ex->i].isbuilt > 0)
			ft_exec_is_builtin(data, ex->argv, cmdtab, ex);
		else
		{
			execve(ex->progpath, ex->argv, envp);
		}
		free(ex->progpath);
		ft_free_tab_char(ex->argv);
		ft_free_tab_char(envp);
		ft_exit(data); // FIXME: utile ?
	}
	else
	{
		ft_forkexe_father_close_pipes(cmdtab, ex);
		// dup2(data->savefd[1], STDOUT_FILENO); //TODO
	}
	if (cmdtab[ex->i].isbuilt > 0 && cmdtab[ex->i].pipeout == 0 && father == -2)
	{
		if (ft_redirection(data, cmdtab, ex) == 0)
		{
			ft_exec_is_builtin(data, ex->argv, cmdtab, ex);
			dup2(data->savefd[1], STDOUT_FILENO); //TODO:
			if (cmdtab[ex->i].pipeout == 1 || cmdtab[ex->i].pipein == 1 )
				close (cmdtab[ex->i].fdredipipe[0]); //FIXME: provoque exit si builtin
		}
	}
		// dup2(data->savefd[0], STDIN_FILENO);//TODO:TODO:
		// if (cmdtab[ex->i].isbuilt > 0 && cmdtab[ex->i].pipeout == 0 && father == -2)
		// 	ft_exec_is_builtin(data, ex->argv, cmdtab, ex);
		// dup2(data->savefd[1], STDOUT_FILENO); //TODO:TODO:
		// close (cmdtab[ex->i].fdredipipe[0]); //FIXME: provoque exit si builtin
	
	return (father);
}

static int	ft_parent_waitpid(t_cmdtab *cmdtab, t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (cmdtab[i].lst)
	{
		if (cmdtab[i].pipeout == 1)
			close(cmdtab[i].fd[0]);
		waitpid(cmdtab[i].pid, &status, 0);
		if (WEXITSTATUS(status))
			kill(cmdtab[i].pid, SIGKILL);//TODO:
		i++;
	}
	return (0);
}

int	ft_run_execve(t_cmdtab *cmdtab, t_data *data)
{
	t_execarg	ex;
	int			ret;
	pid_t		child;
	int			status;

	ex.i = 0;
	cmdtab[ex.i].pid = -1;
	ft_pipe_init_cmdtab_pipe_in_out(cmdtab);
	ft_heredoc_init(cmdtab, data);
	while(cmdtab[ex.i].lst)
	{
		printf("cmdtab[%i].hdcfd = %i\n", ex.i, cmdtab[ex.i].hdcfd);
		ex.i++;
	}
	ex.i = 0;
	while(cmdtab[ex.i].lst)
	{
		if (cmdtab[ex.i].pipeout)
			ft_create_pipe(cmdtab, &ex);
		ex.argv = ft_lstcmd_to_cmdarg_for_execve(cmdtab[ex.i].lst); //TODO:
		ex.progpath = ft_check_if_prog_exist_in_pathenv(ex.argv[0], data->env);
		cmdtab[ex.i].isbuilt = ft_check_is_builtin(data, ex.argv, cmdtab, &ex);
		if (!ex.progpath && cmdtab[ex.i].isbuilt <= 0)
			ft_command_not_found_message(ex.argv, data);
		else
			cmdtab[ex.i].pid = ft_forkexe(data, &ex, cmdtab);
		free(ex.progpath);
		ex.i++;
		ft_free_tab_char(ex.argv);
		if (cmdtab[ex.i].pipein == 1)
			ft_close_pipe(cmdtab, &ex);
	}
	if (ex.i == 1 && cmdtab[0].pipeout == 1)
	{
			close(cmdtab[ex.i].fd[1]);
			close(cmdtab[ex.i - 1].fd[1]);
	}
	
	ex.i = 0; //TODO: test
	while(cmdtab[ex.i].lst)
	{
		if (cmdtab[ex.i].fd[0] != 0)
			close(cmdtab[ex.i].fd[0]);
		if (cmdtab[ex.i].fd[1] != 0)
			close(cmdtab[ex.i].fd[1]);
		ex.i++;
	}

	if (cmdtab[0].pid > 0)
		ft_parent_waitpid(cmdtab, data);
	ex.i = 0; //TODO: test
	while(cmdtab[ex.i].lst)
	{
		if (ft_redi_cmdtab_has_heredoc(cmdtab, &ex))
		{
			close(cmdtab[ex.i].hdcfd);
			unlink(cmdtab[ex.i].hdcpath);
			free(cmdtab[ex.i].hdcpath);
		}
		ex.i++;
	}
	return (0);
}