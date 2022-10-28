/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_special_character.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:26:58 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/28 19:50:39 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_get_len_until_redirection(t_data	*data, char	*buffer, char special)
{
	int	i;

	i = 0;
	while (buffer[data->i] != '\0' && buffer[data->i] == special)
	{
		data->i++;
		i++;
	}
	return (i);
}

int	ft_redirect_me_now(t_data	*data, char	*buffer)
{
	int	len;

	len = 0;
	if (buffer[data->i] == '>')
	{
		len = ft_get_len_until_redirection(data, buffer, '>');
		if (len == 1)
			ft_buffercmd_in_lst(">", data, 0);
		else if (len == 2)
			ft_buffercmd_in_lst(">>", data, 0);
		else if (len > 2)
			return (0);
	}
	else if (buffer[data->i] == '<')
	{
		len = ft_get_len_until_redirection(data, buffer, '<');
		if (len == 1)
			ft_buffercmd_in_lst("<", data, 0);
		else if (len == 2)
			ft_buffercmd_in_lst("<<", data, 0);
		else if (len > 2)
			return (0);
	}
	return (1);
}

int	ft_pipes_spaces_check(t_data	*data, char	*buffer)
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
	printf("test de parsing\n");
	printf("le type de celui d'avant %d\n", data->cmdtoparse->type);
	if (data->cmdtoparse->type == IN1 || data->cmdtoparse->type == IN2 || \
		data->cmdtoparse->type == OUT1 || data->cmdtoparse->type == OUT2)
	{
		printf("testeur\n");		
		error_management(data);
	}
	while (buffer[data->i] == '|')
	{
		
		data->i++;
		len++;
	}
	if (len == 1)
		ft_buffercmd_in_lst("|", data, 0);
	else
		return (0);
	if (!ft_pipes_spaces_check(data, buffer + data->i)){
		return (0);
	}
	return (1);
}