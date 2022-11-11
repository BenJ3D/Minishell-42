/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:32:10 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/11 21:30:42 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_forkexe_exe(t_data *data, t_execarg *ex, char **envp)
{
	char	*errline;

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
	return (0);
}

int	ft_forkexe_child(t_data *data, t_execarg *ex, t_cmdtab *cmdtab, char **envp)
{
	ft_forkexe_dup_if_pipes(cmdtab, ex);
	if (ft_redirection(data, cmdtab, ex))
		exit(errno);
	envp = ft_env_convert_envlst_to_tab(data->env);
	if (cmdtab[ex->i].isbuilt > 0)
		ft_exec_is_builtin(data, ex->argv, cmdtab, ex);
	else
		ft_forkexe_exe(data, ex, envp);
	free(ex->progpath);
	ft_free_tab_char(envp);
	if (cmdtab[ex->i].isbuilt > 0)
		ft_exit_exit(data);
	else
		ft_exit(data, ex->argv);
	return (0);
}

int	ft_forkexe(t_data *data, t_execarg *ex, t_cmdtab *cmdtab)
{
	char	**envp;
	pid_t	father;

	envp = NULL;
	father = -2;
	errno = 0;
	if ((cmdtab[ex->i].pipeout == 1) || (cmdtab[ex->i].pipein == 1) \
												|| (cmdtab[ex->i].isbuilt == 0))
		father = ft_createfork(data, ex);
	if (father == 0)
		ft_forkexe_child(data, ex, cmdtab, envp);
	else
		ft_forkexe_father_close_pipes(cmdtab, ex);
	if (cmdtab[ex->i].isbuilt > 0 && cmdtab[ex->i].pipeout == 0 && father == -2)
	{
		if (ft_redirection(data, cmdtab, ex) == 0)
		{
			ft_exec_is_builtin(data, ex->argv, cmdtab, ex);
			dup2(data->savefd[1], STDOUT_FILENO);
			dup2(data->savefd[0], STDIN_FILENO);
			if (cmdtab[ex->i].pipeout == 1 || cmdtab[ex->i].pipein == 1)
				close (cmdtab[ex->i].fdredipipe[0]);
		}
	}
	return (father);
}

/**
 * @brief return 1 si la cmdtab a une CMD
 * 
 * @param cmdtab 
 * @param ex 
 * @return char* 
 */
int	ft_cmdtab_has_cmd(t_cmdtab *cmdtab, int i)
{
	t_list	*tmp;

	tmp = cmdtab[i].lst;
	while (tmp)
	{
		if (tmp->type == 0)
			return (1);
		tmp = tmp->next;
	}
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
