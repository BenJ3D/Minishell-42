/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:42:35 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/19 23:24:06 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_redirection(t_data *data, t_cmdtab *cmdtab, t_execarg *ex) //TODO:TODO:
{
	t_list	*tmp;

	tmp = cmdtab[ex->i].lst;
	while (tmp)
	{
		if (tmp->type >= IN1 && tmp->type <= OUT2)
		{
			if (cmdtab[ex->i].rediarg != NULL)
				free (cmdtab[ex->i].rediarg);
			cmdtab[ex->i].reditype = tmp->type;
			cmdtab[ex->i].rediarg = ft_strdup(tmp->next->str);
			ft_dupredi(data, cmdtab, ex);
		}
		tmp = tmp->next;
	}	
	return (0);
}

int	ft_dupredi(t_data *data, t_cmdtab *cmdtab, t_execarg *ex)
{
	if (cmdtab[ex->i].reditype == OUT1)
	{
		// printf("dupredi OUT1\n");
		ft_redi_out1(cmdtab, ex);
	}
	else if (cmdtab[ex->i].reditype == OUT2)
	{
		// printf("dupredi OUT1\n");
		ft_redi_out2(cmdtab, ex);
	}
	else if (cmdtab[ex->i].reditype == IN1)
	{
		// printf("dupredi IN1\n");
		ft_redi_in1(cmdtab, ex);
	}
	else if (cmdtab[ex->i].reditype == IN2)
	{
		// printf("dupredi IN2\n");
		dup2(data->savefd[0], STDIN_FILENO);//TODO:TODO:
		ft_redi_in2(cmdtab, ex, data);
	}
	return (0);
}

