/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:42:35 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/20 03:39:57 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_redirection(t_data *data, t_cmdtab *cmdtab, t_execarg *ex) //TODO:TODO:
{
	t_list	*tmp;
	int		ret;

	tmp = cmdtab[ex->i].lst;
	while (tmp)
	{
		if (tmp->type >= IN1 && tmp->type <= OUT2)
		{
			if (cmdtab[ex->i].rediarg != NULL)
				free (cmdtab[ex->i].rediarg);
			cmdtab[ex->i].reditype = tmp->type;
			cmdtab[ex->i].rediarg = ft_strdup(tmp->next->str);
			if ((ret = ft_dupredi(data, cmdtab, ex)))
				return (ret);
		}
		tmp = tmp->next;
	}	
	return (0);
}

int	ft_dupredi(t_data *data, t_cmdtab *cmdtab, t_execarg *ex)
{
	int	ret;
	if (cmdtab[ex->i].reditype == OUT1)
		ret = ft_redi_out1(cmdtab, ex);
	else if (cmdtab[ex->i].reditype == OUT2)
		ret = ft_redi_out2(cmdtab, ex);
	else if (cmdtab[ex->i].reditype == IN1)
		ret = ft_redi_in1(cmdtab, ex);
	else if (cmdtab[ex->i].reditype == IN2)
	{
		// dup2(data->savefd[0], STDIN_FILENO);//TODO:TODO:
		ret = ft_redi_in2(cmdtab, ex, data);
	}
	return (ret);
}

