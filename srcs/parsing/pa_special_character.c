/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_special_character.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:26:58 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/12 19:10:38 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_get_len_until_redirection(t_data	*data, char	*buffer, char special)
{
	int	i;

	i = 0;
	while (buffer[data->scroller] != '\0' && buffer[data->scroller] == special)
	{
		data->scroller++;
		i++;
	}
	return (i);
}

int	ft_redirect_me_now(t_data	*data, char	*buffer)
{
	int	len;

	len = 0;
	if (buffer[data->scroller] == '>')
	{
		len = ft_get_len_until_redirection(data, buffer, '>');
		if (len == 1)
			ft_buffercmd_in_lst(">", data, 0, 0);
		else if (len == 2)
			ft_buffercmd_in_lst(">>", data, 0, 0);
		else if (len > 2)
			return (0);
	}
	else if (buffer[data->scroller] == '<')
	{
		len = ft_get_len_until_redirection(data, buffer, '<');
		if (len == 1)
			ft_buffercmd_in_lst("<", data, 0, 0);
		else if (len == 2)
			ft_buffercmd_in_lst("<<", data, 0, 0);
		else if (len > 2)
			return (0);
	}
	return (1);
}

int	ft_pipes_spaces_check(char	*buffer)
{
	int	pin;

	pin = 0;
	while ((buffer[pin] < 33 || buffer[pin] > 126) && buffer[pin] != '\0')
		pin++;
	if (buffer[pin] == '|')
		return (0);
	return (1);
}

int	ft_parsing_for_a_pipe(t_data	*data, char	*buffer)
{
	int	len;

	len = 0;
	if (data->type_of_the_last_cmd == 3 || data->type_of_the_last_cmd == 4 || \
		data->type_of_the_last_cmd == 5 || data->type_of_the_last_cmd == 6)
		return (0);
	while (buffer[data->scroller] == '|')
	{
		data->scroller++;
		len++;
	}
	if (len == 1)
		ft_buffercmd_in_lst("|", data, 0, 0);
	else
		return (0);
	if (!ft_pipes_spaces_check(buffer + data->scroller))
		return (0);
	return (1);
}
