/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_related.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:49:40 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/18 14:00:48 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"


void	ft_reset_quotes_checker(t_data	*data)
{
	data->s_quotes_switch = 0;
	data->d_quotes_switch = 0;
}

void	ft_quotes_checker(t_data	*data, char	*str, int i)
{
	if (str[i] == SIMPLE_QUOTE && data->d_quotes_switch == 0)
	{
		if (data->s_quotes_switch == 0)
			data->s_quotes_switch = 1;
		else if (data->s_quotes_switch == 1)
			data->s_quotes_switch = 0;
	}
	else if (str[i] == DOUBLE_QUOTE && data->s_quotes_switch == 0)
	{
		if (data->d_quotes_switch == 0)
			data->d_quotes_switch = 1;
		else if (data->d_quotes_switch == 1)
			data->d_quotes_switch = 0;	
	}
}

int		ft_node_quote_checker(t_data	*data)
{
	t_list	*begin;
	int		i;

	i = 0;
	ft_reset_quotes_checker(data);
	begin = data->cmdtoparse;
	while (begin)
	{
		printf("%s\n", begin->str);
		while (begin->str[i])
		{
			printf("test\n");
			ft_quotes_checker(data, begin->str, i);
			i++;
		}
		i = 0;
		begin = begin->next;
	}
	if (data->s_quotes_switch == 1 || data->d_quotes_switch == 1)
		return (0);
	else
		return (1);
}

static int	ft_len_buffer(char	*str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_full_prompt_quote_check(t_data	*data, char	*buffer)
{
	int	i;
	int	len;

	i = 0;
	len = ft_len_buffer(buffer);
	ft_reset_quotes_checker(data);
	while (i < len)
	{
		ft_quotes_checker(data, buffer, i);
		i++;
	}
	if (data->s_quotes_switch == 1 || data->d_quotes_switch == 1)
		return (0);
	else
		return (1);
}
