/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:42:35 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/21 17:34:26 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_make_heredoc(t_data *data, t_cmdtab *cmdtab, t_execarg *ex)
{
	t_list *tmp;
	
	cmdtab[ex->i].heredoc = ft_strdup("");
	tmp = cmdtab[ex->i].lst;
	while (tmp)
	{
		if (tmp->type == IN2) //TODO:
		{
			free (cmdtab[ex->i].heredoc);
			// cmdtab[ex->i].heredoc = ft_heredoc_create(cmdtab[ex->i].lst->next->str); //FIXME:
		}
		tmp = tmp->next;
	}

	return (0);
}

int	ft_pars_heredoc(t_data *data, t_cmdtab *cmdtab)
{
	t_execarg ex;
	
	ex.i = 0;
	while(cmdtab[ex.i].lst)
	{
		if (ft_redi_cmdtab_has_heredoc(cmdtab, &ex)) //TODO:
			;
	}
	
	return (0);
}

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
		ret = ft_redi_in2(cmdtab, ex, data);
	}
	return (ret);
}

int	ft_redi_cmdtab_has_heredoc(t_cmdtab *cmdtab, t_execarg *ex)
{
	t_list *tmp;
	
	tmp = cmdtab[ex->i].lst;
	while (tmp)
	{
		if (tmp->type == IN2) //TODO:
			return (1);
		tmp = tmp->next;
	}
	return (0);
}