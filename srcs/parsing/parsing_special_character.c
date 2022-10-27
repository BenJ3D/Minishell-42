/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_special_character.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:26:58 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/27 17:59:43 by hmarconn         ###   ########.fr       */
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

t_list	*ft_redirect_me_now(t_data	*data, char	*buffer, t_list	*cmd)
{
	int	len;

	len = 0;
	if (buffer[data->i] == '>')
	{
		len = ft_get_len_until_redirection(data, buffer, '>');
		if (len == 1)
			cmd = ft_buffercmd_in_lst(">", cmd, data);
		else if (len == 2)
			cmd = ft_buffercmd_in_lst(">>", cmd, data);
		else if (len > 2)
			return (NULL);
	}
	else if (buffer[data->i] == '<')
	{
		len = ft_get_len_until_redirection(data, buffer, '<');
		if (len == 1)
			cmd = ft_buffercmd_in_lst("<", cmd, data);
		else if (len == 2)
			cmd = ft_buffercmd_in_lst("<<", cmd, data);
		else if (len > 2)
			return (NULL);
	}
	return (cmd);
}

t_list	*ft_parsing_for_a_pipe(t_data	*data, char	*buffer, t_list	*cmd)
{
	int	len;

	len = 0;
	while (buffer[data->i] == '|')
	{
		data->i++;
		len++;
	}
	if (len == 1)
		cmd = ft_buffercmd_in_lst("|", cmd, data);
	else
		return (NULL);
	if (!ft_pipes_spaces_check(data, buffer + data->i))
		error_management(data, buffer, cmd);
	return (cmd);
}