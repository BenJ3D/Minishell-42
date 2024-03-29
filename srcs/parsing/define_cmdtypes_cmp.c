/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_cmdtypes_cmp.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:22:01 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/12 19:10:38 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_dct_data_reload(t_data	*data)
{
	data->first_arg = 1;
	data->first_cmd = 0;
}

t_list	*ft_cft_prime(t_list	*tmp)
{
	if (tmp->str[1] == '>')
		tmp->type = OUT2;
	else
		tmp->type = OUT1;
	tmp->next->type = OUTFILE;
	tmp = tmp->next;
	return (tmp);
}

t_list	*ft_cmd_first_type(t_data	*data, t_list	*tmp)
{
	if (tmp->str[0] == '>' && tmp->heavy == 0)
		tmp = ft_cft_prime(tmp);
	else if (tmp->str[0] == '<' && tmp->heavy == 0)
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
		}
	}
	else
	{
		if (data->first_arg == 0)
			tmp->type = CMD;
		else
			tmp->type = ARG;
	}
	return (tmp);
}
