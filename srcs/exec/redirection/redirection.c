/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:42:35 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/19 20:35:40 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_redirection(t_data *data, t_cmdtab *cmdtab, t_execarg *ex) //TODO:TODO:
{
	t_list	*tmp;

	tmp = cmdtab[ex->i].lst;
	cmdtab[ex->i].rediarg = ft_strdup("");
	while (tmp)
	{
		if (tmp->type >= IN1 && tmp->type <= OUT2)
		
		tmp = tmp->next;
	}	
	return (0);
}

int	ft_dupredi(t_data *data, t_cmdtab *cmdtab, t_execarg *ex)
{
	if (cmdtab[ex->i].reditype == OUT1)
		ft_redi_out1(cmdtab, ex);
	else if (cmdtab[ex->i].reditype == OUT2)
		ft_redi_out2(cmdtab, ex);
	else if (cmdtab[ex->i].reditype == IN1)
		ft_redi_in1(cmdtab, ex);
	else if (cmdtab[ex->i].reditype == IN2)
		ft_redi_in2(cmdtab, ex, data);
	return (0);
}

