/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:42:35 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/03 22:22:39 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_redi_out1(t_cmdtab *cmdtab, t_execarg *ex)
{
	cmdtab[ex->i].fdredi = open(cmdtab[ex->i].rediarg, \
											O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmdtab[ex->i].fdredi < 0)
	{
		perror(cmdtab[ex->i].rediarg);
		return (errno);
	}
	else
	{
		dup2(cmdtab[ex->i].fdredi, STDOUT_FILENO);
		close(cmdtab[ex->i].fdredi);
	}
	return (0);
}

int	ft_redi_out2(t_cmdtab *cmdtab, t_execarg *ex)
{
	cmdtab[ex->i].fdredi = open(cmdtab[ex->i].rediarg, \
										O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmdtab[ex->i].fdredi < 0)
	{
		perror(cmdtab[ex->i].rediarg);
		return (errno);
	}
	else
	{
		dup2(cmdtab[ex->i].fdredi, STDOUT_FILENO);
		close(cmdtab[ex->i].fdredi);
	}
	return (0);
}

int	ft_redi_in1(t_cmdtab *cmdtab, t_execarg *ex)
{
	cmdtab[ex->i].fdredi = open(cmdtab[ex->i].rediarg, O_RDONLY);
	if (cmdtab[ex->i].fdredi < 0)
	{
		perror(cmdtab[ex->i].rediarg);
		return (errno);
	}
	else
	{
		dup2(cmdtab[ex->i].fdredi, STDIN_FILENO);
		close(cmdtab[ex->i].fdredi);
	}
	return (0);
}

int	ft_redi_in2(int hdc_fd, t_cmdtab *cmdtab, t_execarg *ex)
{
	hdc_fd = open(cmdtab[ex->i].hdcpath, O_RDONLY);
	if (hdc_fd < 0)
	{
		perror(cmdtab[ex->i].hdcpath);
		return (errno);
	}
	else
	{
		dup2(hdc_fd, STDIN_FILENO);
		close(hdc_fd);
	}
	return (0);
}
