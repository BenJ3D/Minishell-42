/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_cmd_types.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:36:27 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/09 18:23:52 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

t_list	*ft_dct_rd(t_list	*tmp, t_data	*data)
{
	if (tmp->str[1] == '>')
		tmp->type = OUT2;
	else
		tmp->type = OUT1;
	tmp->next->type = OUTFILE;
	tmp = tmp->next;
	if (tmp && tmp->str[0] != '|')
		data->first_cmd = 1;
	tmp = tmp->next;
	return (tmp);
}

t_list	*ft_dct_rg(t_list	*tmp, t_data	*data)
{
	if (tmp->str[1] == '<')
		tmp->type = IN2;
	else
		tmp->type = IN1;
	if (tmp->next)
	{
		if (tmp->type == IN1)
			tmp->next->type = INFILE;
		else
			tmp->next->type = INQUOTE;
		tmp = tmp->next;
		if (tmp && tmp->str[0] != '|')
			data->first_cmd = 1;
	}
	tmp = tmp->next;
	return (tmp);
}

t_list	*ft_dct_pipe(t_list	*tmp, t_data	*data)
{
	tmp->type = PIPE;
	data->first_cmd = 1;
	tmp = tmp->next;
	return (tmp);
}

t_list	*ft_dct_prime(t_list	*tmp, t_data	*data)
{
	if (data->first_cmd == 1 && tmp->str[0] != '|')
	{
		tmp = ft_cmd_first_type(data, tmp);
		if (tmp && tmp->type == 0)
		{
			data->first_arg = 1;
			data->first_cmd = 0;
		}
		tmp = tmp->next;
	}
	else if (tmp->str[0] == '>' && tmp->heavy == 0)
		tmp = ft_dct_rd(tmp, data);
	else if (tmp->str[0] == '<' && tmp->heavy == 0)
		tmp = ft_dct_rg(tmp, data);
	else if (tmp->str[0] == '|' && tmp->heavy == 0)
	{
		tmp = ft_dct_pipe(tmp, data);
		data->first_arg = 0;
	}
	else
	{
		tmp->type = ARG;
		tmp = tmp->next;
	}
	return (tmp);
}

/**
 * @brief donne un type a chaque commande, pour faciliter le parsing en execve
 * ATTENTION : les erreurs de syntax doivent deja etre gerer en amont, 
 * sinon risque de SEGV
 * @param  lst la lst avec toutes les commandes du buffer pas encore split
 * @return int 
 */
int	ft_define_cmd_type(t_list *lst, t_data	*data)
{
	t_list	*tmp;

	if (!lst)
		return (-1);
	tmp = lst;
	data->first_cmd = 1;
	data->first_arg = 0;
	while (tmp)
	{
		if (data->first_cmd == 1 && tmp->str[0] == '|' && tmp->heavy == 0 && \
			data->first_arg == 0)
			return (0);
		tmp = ft_dct_prime(tmp, data);
	}
	return (1);
}
