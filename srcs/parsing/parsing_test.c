/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:26:09 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/02 13:18:55 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_total_parsing(t_data	*data, char	*buffer)
{
	int		len_max;
	int		pin;

	data->first_cmd = 0;
	data->cmdtoparse = NULL;
	data->i = 0;
	len_max = ft_strlen_parsing(buffer);
	ft_reset_quotes_checker(data);
	while (buffer[data->i])
	{
		ft_quotes_checker(data, buffer, data->i);
		while (data->s_quotes_switch == 1 || data->d_quotes_switch == 1)
		{
			ft_quotes(data, buffer, len_max);
			if (data->cmdtoparse == NULL)
			{
				error_management(data);
				return (0);
			}
		}
		if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0 && \
			buffer[data->i] == '$')
		{
			ft_parsing_env_variable(data, buffer);
			if (data->cmdtab == NULL)
			{
				error_management(data);
				return (0);
			}
		}
		else if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0 && \
			buffer[data->i] == '|')
		{
			ft_parsing_for_a_pipe(data, buffer);
			if (data->cmdtoparse == NULL)
			{
				error_management(data);
				return (0);
			}
		}
		else if ((data->s_quotes_switch == 0 && data->d_quotes_switch == 0) && \
			(buffer[data->i] == '<' || buffer[data->i] == '>'))
		{
			ft_redirect_me_now(data, buffer);
			if (data->cmdtoparse == NULL || !ft_redirection_files_check(data, buffer + \
				data->i))
			{
				error_management(data);
				return (0);
			}
		}
		else if ((data->s_quotes_switch == 0 && data->d_quotes_switch == 0) && \
			buffer[data->i] >= 33 && buffer[data->i] <= 126)
		{
			ft_parsing_others(data, buffer);
			if (data->cmdtoparse == NULL)
			{
				error_management(data);
				return (0);
			}
		}
		if (buffer[data->i] && (buffer[data->i] < 33 || buffer[data->i] > 126) \
			&& (buffer[data->i] != '|'))
			data->i++;
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
