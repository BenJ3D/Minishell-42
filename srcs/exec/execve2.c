/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:32:10 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/04 12:25:52 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_run_execve_norm1(t_data *data, t_cmdtab *cmdtab, t_execarg *ex)
{
	if (!ex->progpath && cmdtab[ex->i].isbuilt <= 0 && ex->stat == STAT_NONE)
	{	
		if (cmdtab[ex->i].pipein == 1 || cmdtab[ex->i].pipeout == 1)
			cmdtab[ex->i].pid = fork();
		if (cmdtab[ex->i].pipein == 1 || cmdtab[ex->i].pipeout == 1)
		{
			if (cmdtab[ex->i].pid == 0)
				exit(ft_command_not_found_message(ex->argv, data));
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
	return (0);
}

int	ft_run_execve_init(t_cmdtab *cmdtab, t_execarg *ex, t_data *data)
{
	ex->i = 0;
	cmdtab[ex->i].pid = -1;
	ft_pipe_init_cmdtab_pipe_in_out(cmdtab);
	ft_heredoc_init(cmdtab, data);
	return (0);
}

int	ft_run_execve2_norm(t_cmdtab *cmdtab, t_execarg *ex, t_data *data)
{
	if (ex->i == 1 && cmdtab[0].pipeout == 1)
	{
		close(cmdtab[ex->i].fd[1]);
		close(cmdtab[ex->i - 1].fd[1]);
	}
	ex->i = 0;
	while (cmdtab[ex->i].lst)
	{
		if (cmdtab[ex->i].fd[0] != 0)
			close(cmdtab[ex->i].fd[0]);
		if (cmdtab[ex->i].fd[1] != 0)
			close(cmdtab[ex->i].fd[1]);
		ex->i++;
	}
	if (cmdtab[0].pid > 0)
		ft_parent_waitpid(cmdtab, data);
	ft_execve_clear_hdcfd(ex, cmdtab);
	return (0);
}

int	ft_run_execve(t_cmdtab *cmdtab, t_data *data)
{
	t_execarg	ex;

	ft_run_execve_init(cmdtab, &ex, data);
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
	ft_run_execve2_norm(cmdtab, &ex, data);
	return (0);
}

void	ft_execve_clear_hdcfd(t_execarg *ex, t_cmdtab *cmdtab)
{
	ex->i = 0;
	while (cmdtab[ex->i].lst)
	{
		if (ft_redi_cmdtab_has_heredoc(cmdtab, ex))
		{
			close(cmdtab[ex->i].hdcfd);
			unlink(cmdtab[ex->i].hdcpath);
			free(cmdtab[ex->i].hdcpath);
		}
		ex->i++;
	}
}
