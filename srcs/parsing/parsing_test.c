/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:26:09 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/03 18:46:35 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_total_parsing(t_data	*data, char	*buffer)
{
	int		len_max;
	int		pin;

	data->first_cmd = 0;
	data->cmdtoparse = NULL;
	data->scroller = 0;
	len_max = ft_strlen_parsing(buffer);
	ft_reset_quotes_checker(data);
	while (buffer[data->scroller])
	{
		ft_quotes_checker(data, buffer, data->scroller);
		if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0 && \
			buffer[data->scroller] == '|')
		{
			if(!ft_parsing_for_a_pipe(data, buffer))
				return (0);
			if (data->cmdtoparse == NULL)
			{
				error_management(data);
				return (0);
			}
		}
		else if ((data->s_quotes_switch == 0 && data->d_quotes_switch == 0) && \
			(buffer[data->scroller] == '<' || buffer[data->scroller] == '>'))
		{
			ft_redirect_me_now(data, buffer);
			if (data->cmdtoparse == NULL || !ft_redirection_files_check(data, buffer + \
				data->scroller))
			{
				error_management(data);
				return (0);
			}
		}
		else if (buffer[data->scroller] >= 33 && buffer[data->scroller] <= 126)
		{
			ft_parsing_others(data, buffer, len_max);
			if (data->cmdtoparse == NULL)
			{
				error_management(data);
				return (0);
			}
		}
		if (buffer[data->scroller] && (buffer[data->scroller] < 33 || \
			buffer[data->scroller] > 126))
			data->scroller++;
	}
	if (data->cmdtoparse == NULL)
	{
		error_management(data);
		return (0);
	}
	ft_reset_quotes_checker(data);
	if (data->type_of_the_last_cmd == 3 || data->type_of_the_last_cmd == 4 || \
		data->type_of_the_last_cmd == 5 || data->type_of_the_last_cmd == 6)
	{	
		error_management(data);
		return (0);
	}
	return (1);
}
