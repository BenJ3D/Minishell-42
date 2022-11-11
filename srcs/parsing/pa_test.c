/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:26:09 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/11 21:35:36 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_total_parsing_complementary(t_data *data, char *buffer)
{
	if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0 && \
		buffer[data->scroller] == '|')
	{
		if (!ft_parsing_for_a_pipe(data, buffer) || data->cmdtoparse == NULL)
			return (0);
	}
	else if ((data->s_quotes_switch == 0 && data->d_quotes_switch == 0) && \
		(buffer[data->scroller] == '<' || buffer[data->scroller] == '>'))
	{
		if (!ft_redirect_me_now(data, buffer) || data->cmdtoparse == NULL || \
						!ft_redirection_files_check(buffer + data->scroller))
			return (0);
	}
	else if (buffer[data->scroller] >= 33 && buffer[data->scroller] <= 126)
	{
		ft_pa_others(data, buffer);
		if (data->cmdtoparse == NULL)
			return (2);
	}
	if (buffer[data->scroller] && (buffer[data->scroller] < 33 || \
		buffer[data->scroller] > 126))
		data->scroller++;
	return (1);
}

int	ft_total_parsing(t_data	*data, char	*buffer)
{
	int		pin;

	data->first_cmd = 0;
	data->cmdtoparse = NULL;
	data->scroller = 0;
	data->len_max = ft_strlen_parsing(buffer);
	ft_reset_quotes_checker(data);
	while (buffer[data->scroller])
	{
		ft_quotes_checker(data, buffer, data->scroller);
		pin = ft_total_parsing_complementary(data, buffer);
		if (pin == 0)
			return (0);
		else if (pin == 2)
			return (2);
	}
	if (data->cmdtoparse == NULL)
		return (2);
	ft_reset_quotes_checker(data);
	if (data->type_of_the_last_cmd == 3 || data->type_of_the_last_cmd == 4 || \
		data->type_of_the_last_cmd == 5 || data->type_of_the_last_cmd == 6 || \
		data->type_of_the_last_cmd == 2)
		return (0);
	return (1);
}
