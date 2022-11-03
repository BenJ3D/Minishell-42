/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:32:10 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/03 23:00:42 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_check_if_cmd_has_a_backslash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	ft_command_not_found_message(char **argv, t_data *data)
{
	if (argv[0] != NULL)
	{
		if (ft_check_if_cmd_has_a_backslash(argv[0]))
		{
			ft_err_display_line_error(data, argv[0], \
												"No such file or directory");
			g_status = 127;
		}
		else
		{
			ft_err_display_line_error(data, argv[0], "command not found");
			g_status = 127;
		}
	}
	else
		return (0);
	return (127);
}

int	ft_forkexe(t_data *data, t_execarg *ex, t_cmdtab *cmdtab)
{
	char	**envp;
	pid_t	father;
	char	*errline;

	father = -2;
	errno = 0;
	if ((cmdtab[ex->i].pipeout == 1) || (cmdtab[ex->i].pipein == 1) \
												|| (cmdtab[ex->i].isbuilt == 0))
		father = ft_createfork(data, ex, envp);
	if (father == 0)
	{
		ft_forkexe_dup_if_pipes(cmdtab, ex);
		if (ft_redirection(data, cmdtab, ex))
			exit(errno);
		envp = ft_env_convert_envlst_to_tab(data->env);
		if (cmdtab[ex->i].isbuilt > 0)
			ft_exec_is_builtin(data, ex->argv, cmdtab, ex);
		else
		{
			if (ex->progpath)
			{
				errline = ft_strjoin_max("%s%s: %s%s%s", COLOR_CYAN, \
					data->pgr_name, COLOR_PURPLE, ex->progpath, COLOR_PURPLE);
				execve(ex->progpath, ex->argv, envp);
				g_status = errno;
				perror(errline);
				free (errline);
			}
			else
			{
				errline = ft_strjoin_max("%s%s: %s%s%s", COLOR_CYAN, \
						data->pgr_name, COLOR_PURPLE, ex->argv[0], COLOR_RED);
				execve(ex->argv[0], ex->argv, envp);
				g_status = errno;
				perror(errline);
				free (errline);
			}
		}
		free(ex->progpath);
		ft_free_tab_char(envp);
		ft_exit(data, ex->argv);
	}
	else
		ft_forkexe_father_close_pipes(cmdtab, ex);
	if (cmdtab[ex->i].isbuilt > 0 && cmdtab[ex->i].pipeout == 0 && father == -2)
	{
		if (ft_redirection(data, cmdtab, ex) == 0)
		{
			ft_exec_is_builtin(data, ex->argv, cmdtab, ex);
			dup2(data->savefd[1], STDOUT_FILENO);
			if (cmdtab[ex->i].pipeout == 1 || cmdtab[ex->i].pipein == 1)
				close (cmdtab[ex->i].fdredipipe[0]);
		}
	}
	return (father);
}

static int	ft_parent_waitpid(t_cmdtab *cmdtab, t_data *data)
{
	int	i;

	i = 0;
	while (cmdtab[i].lst)
	{
		if (cmdtab[i].pipeout == 1)
			close(cmdtab[i].fd[0]);
		waitpid(cmdtab[i].pid, &g_status, 0);
		i++;
	}
	return (0);
}

int	ft_init_cmd(t_cmdtab *cmdtab)
{
	int	i;

	i = 0;
	while (cmdtab[i].lst)
		cmdtab[i++].hdcpath = NULL;
	return (0);
}

int	ft_run_execve_norm1(t_data *data, t_cmdtab *cmdtab, t_execarg *ex)
{
	if (!ex->progpath && cmdtab[ex->i].isbuilt <= 0 && ex->stat == STAT_NONE)
	{	
		if (cmdtab[ex->i].pipein == 1 || cmdtab[ex->i].pipeout == 1)
			cmdtab[ex->i].pid = fork();
		if (cmdtab[ex->i].pipein == 1 || cmdtab[ex->i].pipeout == 1)
		{
			if (cmdtab[ex->i].pid == 0)
			{
				exit(ft_command_not_found_message(ex->argv, data));
			}
		}
		else
		{
			g_status = ft_command_not_found_message(ex->argv, data);
			errno = g_status;
		}
	}
	else if (ft_cmdtab_has_cmd(cmdtab, ex) \
										!= NULL && ex->stat != STAT_ISDIR)
		cmdtab[ex->i].pid = ft_forkexe(data, ex, cmdtab);
	else
		ft_check_redi_if_has_no_cmd(cmdtab, ex, data);
}

int	ft_run_execve(t_cmdtab *cmdtab, t_data *data)
{
	t_execarg	ex;

	ex.i = 0;
	cmdtab[ex.i].pid = -1;
	ft_pipe_init_cmdtab_pipe_in_out(cmdtab);
	ft_heredoc_init(cmdtab, data);
	while (cmdtab[ex.i].lst)
	{
		if (cmdtab[ex.i].pipeout)
			ft_create_pipe(cmdtab, &ex);
		ex.argv = ft_lstcmd_to_cmdarg_for_execve(cmdtab[ex.i].lst);
		ex.progpath = ft_check_if_prog_exist_in_pathenv(ex.argv[0], data->env);
		cmdtab[ex.i].isbuilt = ft_check_is_builtin(data, ex.argv, cmdtab, &ex);
		ex.stat = 0;
		ex.stat = ft_stat_check(cmdtab, &ex, data, ex.progpath);
		ft_run_execve_norm1(data, cmdtab, &ex);
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
	ex.i = 0;
	while (cmdtab[ex.i].lst)
	{
		if (cmdtab[ex.i].fd[0] != 0)
			close(cmdtab[ex.i].fd[0]);
		if (cmdtab[ex.i].fd[1] != 0)
			close(cmdtab[ex.i].fd[1]);
		ex.i++;
	}
	if (cmdtab[0].pid > 0)
		ft_parent_waitpid(cmdtab, data);
	ex.i = 0;
	while (cmdtab[ex.i].lst)
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
