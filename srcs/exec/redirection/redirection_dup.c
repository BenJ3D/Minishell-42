/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:42:35 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/21 15:35:20 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_redi_out1(t_cmdtab *cmdtab, t_execarg *ex)
{
	if ((cmdtab[ex->i].fdredi = open(cmdtab[ex->i].rediarg,
									 O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
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
	if ((cmdtab[ex->i].fdredi = open(cmdtab[ex->i].rediarg,
									O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
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
	if ((cmdtab[ex->i].fdredi = open(cmdtab[ex->i].rediarg, O_RDONLY)) < 0)
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
