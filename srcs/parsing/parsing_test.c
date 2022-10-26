/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:26:09 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/26 12:01:17 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

static t_list	*ft_redirect_me_now(t_data	*data, char	*buffer, t_list	*cmd)
{
	int	len;

	len = 0;
	if (buffer[data->i] == '>')
	{
		while (buffer[data->i] != '\0' && buffer[data->i] == '>')
		{
			len++;
			data->i++;
		}
		if (len == 1)
			cmd = ft_buffercmd_in_lst(">", cmd, data);
		else if (len == 2)
			cmd = ft_buffercmd_in_lst(">>", cmd, data);
		else if (len > 2)
			return (NULL);
	}
	else if (buffer[data->i] == '<')
	{
		while (buffer[data->i] != '\0' && buffer[data->i] == '<')
		{
			len++;
			data->i++;			
		}
		if (len == 1)
			cmd = ft_buffercmd_in_lst("<", cmd, data);
		else if (len == 2)
			cmd = ft_buffercmd_in_lst("<<", cmd, data);
		else if (len > 2)
			return (NULL);
	}
	return (cmd);	
}

static t_list	*ft_parsing_for_a_pipe(t_data	*data, char	*buffer, t_list	*cmd)
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
	return (cmd); 
}

t_list	*ft_total_parsing(t_data	*data, char	*buffer)
{
	int	len_max;
	t_list	*cmd;
	int		pin;

	cmd = NULL;
	data->i = 0;
	len_max = ft_strlen_parsing(buffer);
	ft_reset_quotes_checker(data);
	while (buffer[data->i])
	{
		printf("test '%c'\n", buffer[data->i]);
		ft_quotes_checker(data, buffer, data->i);
		while (data->s_quotes_switch == 1 || data->d_quotes_switch == 1)
		{
			cmd = ft_quotes(data, buffer, cmd, len_max);
			if (cmd == NULL)
			{
				error_management(data, buffer, cmd);
				return (NULL);
			}
		}
		if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0 && buffer[data->i] == '$')
		{
			cmd = ft_parsing_env_variable(data, cmd, buffer);
			if (cmd == NULL)
			{
				error_management(data, buffer, cmd);
				return (NULL);
			}
		}
		else if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0 && buffer[data->i] == '|')
		{
			cmd = ft_parsing_for_a_pipe(data, buffer, cmd);
			if (cmd == NULL)
			{
				error_management(data, buffer, cmd);
				return (NULL);
			}
		}
		else if ((data->s_quotes_switch == 0 && data->d_quotes_switch == 0) && (buffer[data->i] == '<' || buffer[data->i] == '>'))
		{
			cmd = ft_redirect_me_now(data, buffer, cmd);
			if (cmd == NULL)
			{
				error_management(data, buffer, cmd);
				return (NULL);
			}
		}
		else if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0)
		{
			cmd = ft_parsing_others(data, cmd, buffer);
			if (cmd == NULL)
			{
				error_management(data, buffer, cmd);
				return (NULL);
			}
		}
		if (buffer[data->i] && (buffer[data->i] < 33 || buffer[data->i] > 126) && (buffer[data->i] != '|'))
		{
			printf("ici\n");
			data->i++;
		}
	}
	if (cmd == NULL)
	{
		error_management(data, buffer, cmd);
		return (NULL);
	}
	ft_reset_quotes_checker(data);
	return (cmd);
}