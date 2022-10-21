/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:32:10 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/21 15:30:03 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

/**
 * @brief appliques les dup2 si pipeout ou/et pipein
 * 
 * @param cmdtab 
 * @param ex 
 * @return int 
 */
int	ft_forkexe_dup_if_pipes(t_cmdtab *cmdtab, t_execarg *ex)
{
	if (cmdtab[ex->i].pipeout == 1)
	{
	 	if (ft_redi_cmdtab_has_heredoc(cmdtab, ex) == 0)//FIXME:FIXME:
			dup2(cmdtab[ex->i + 1].fd[1], STDOUT_FILENO);
		else
			close(cmdtab[ex->i + 1].fd[1]);
		close(cmdtab[ex->i + 1].fd[0]);
	}
	if (cmdtab[ex->i].pipein == 1)
	{
		if (ft_redi_cmdtab_has_heredoc(cmdtab, ex) == 0) //FIXME:FIXME:
		{
			// ft_putstr_fd("dup2 fd0 , STDIN if pipein\n", 2);
			dup2(cmdtab[ex->i].fd[0], STDIN_FILENO);
		}
		else
			close(cmdtab[ex->i].fd[0]);
		close(cmdtab[ex->i].fd[1]);
	}
	return (0);
}

/**
 * @brief ferme les bons côtés des pipes pour le father si pipein/out == 1
 * 
 * @param cmdtab 
 * @param ex 
 * @return int 
 */
int	ft_forkexe_father_close_pipes(t_cmdtab *cmdtab, t_execarg *ex)
{
	if (cmdtab[ex->i].pipeout == 1)
		close(cmdtab[ex->i + 1].fd[1]);
	if (cmdtab[ex->i].pipeout == 0 && ex->i > 1)
		close(cmdtab[ex->i].fd[1]);
	if (cmdtab[ex->i].pipein == 1)
		close(cmdtab[ex->i].fd[0]);
	return (0);
}

/**
 * @brief definis pipeout et pipeint pour chaques commandes
 * permet de definir les comportement a adopter en cas de pipe
 * @param cmdtab 
 * @return int 
 */
int	ft_pipe_init_cmdtab_pipe_in_out(t_cmdtab *cmdtab)
{
	int	i;

	i = 0;
	while(cmdtab[i].lst)
	{
		cmdtab[i].pipeout = 0;
		cmdtab[i++].pipein = 0;
	}
	i = -1;
	while(cmdtab[++i].lst)
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

int	ft_close_pipe(t_cmdtab *cmdtab, t_execarg *ex)
{
	if (ex->i >= 2)
	{
		// close(cmdtab[ex->i - 2].fd[0]);
		close(cmdtab[ex->i - 2].fd[1]);
	}
	return (0);
}