/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:26:09 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/28 16:07:49 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

t_list	*ft_total_parsing(t_data	*data, char	*buffer)
{
	int		len_max;
	t_list	*cmd;
	int		pin;

	data->first_cmd = 0;
	cmd = NULL;
	data->i = 0;
	len_max = ft_strlen_parsing(buffer);
	ft_reset_quotes_checker(data);
	while (buffer[data->i])
	{
		ft_quotes_checker(data, buffer, data->i);
		while (data->s_quotes_switch == 1 || data->d_quotes_switch == 1)
		{
			cmd = ft_quotes(data, buffer, cmd, len_max);
			printf("ici :%d\n", cmd->heavy);
			if (cmd == NULL)
			{
				error_management(data, buffer, cmd);
				return (NULL);
			}
		}
		if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0 && \
			buffer[data->i] == '$')
		{
			cmd = ft_parsing_env_variable(data, cmd, buffer);
			printf("ici :%d\n", cmd->heavy);
			if (cmd == NULL)
			{
				error_management(data, buffer, cmd);
				return (NULL);
			}
		}
		else if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0 && \
			buffer[data->i] == '|')
		{
			cmd = ft_parsing_for_a_pipe(data, buffer, cmd);
			printf("ici :%d\n", cmd->heavy);
			if (cmd == NULL)
			{
				error_management(data, buffer, cmd);
				return (NULL);
			}
		}
		else if ((data->s_quotes_switch == 0 && data->d_quotes_switch == 0) && \
			(buffer[data->i] == '<' || buffer[data->i] == '>'))
		{
			cmd = ft_redirect_me_now(data, buffer, cmd);
			printf("ici :%d\n", cmd->heavy);
			if (cmd == NULL || !ft_redirection_files_check(data, buffer + \
				data->i))
			{
				error_management(data, buffer, cmd);
				return (NULL);
			}
		}
		else if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0)
		{
			cmd = ft_parsing_others(data, cmd, buffer);
			printf("ici :%d\n", cmd->heavy);
			if (cmd == NULL)
			{
				error_management(data, buffer, cmd);
				return (NULL);
			}
		}
		if (buffer[data->i] && (buffer[data->i] < 33 || buffer[data->i] > 126) \
			&& (buffer[data->i] != '|'))
			data->i++;
	}
	if (cmd == NULL)
	{
		error_management(data, buffer, cmd);
		return (NULL);
	}
	ft_reset_quotes_checker(data);
	return (cmd);
}
