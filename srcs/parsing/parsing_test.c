/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:26:09 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/20 11:57:59 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

t_list	*ft_total_parsing(t_data	*data, char	*buffer)
{
	int	len_max;
	t_list	*cmd;

	cmd = NULL;
	data->i = 0;
	len_max = ft_strlen_parsing(buffer);
	ft_reset_quotes_checker(data);
	while (buffer[data->i])
	{
		ft_quotes_checker(data, buffer, data->i);
		while (data->s_quotes_switch == 1 || data->d_quotes_switch == 1)
		{
			printf("test1\n");
			cmd = ft_quotes(data, buffer, cmd, len_max);
			printf("Test2\n");
		}
		if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0 && buffer[data->i] == '$')
			cmd = ft_parsing_env_variable(data, cmd, buffer);
		else if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0 && buffer[data->i] == '|')
		{
			while (buffer[data->i] == '|')
				data->i++;
			cmd = ft_buffercmd_in_lst("|", cmd, data);
		}
		// else if ((data->s_quotes_switch == 0 && data->d_quotes_switch == 0) && (buffer[data->i] == '<' || buffer[data->i] == '>'))
		// {
			
		// }
		else if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0)
			cmd = ft_parsing_others(data, cmd, buffer);
		if (buffer[data->i])
			data->i++;	
	}
	return (cmd);
}