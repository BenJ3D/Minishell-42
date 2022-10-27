/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_others.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:55:59 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/27 11:57:34 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

t_list	*ft_parsing_others(t_data	*data, t_list	*cmd, char	*buffer)
{
	int		pin;
	int		len;
	int		pan;
	char	*semi_final;

	len = 0;
	while (buffer[data->i] < 33 && buffer[data->i] > 126 && buffer[data->i] \
		!= '\0' && buffer[data->i] \
		!= '$' && buffer[data->i] != '\'' && buffer[data->i] != '"')
		data->i++;
	pin = data->i;
	while (buffer[data->i] != '\0' && buffer[data->i] >= 33 && buffer[data->i] \
		<= 126 && (buffer[data->i] != '>' && buffer[data->i] != '<'))
	{
		data->i++;
		len++;
	}
	if (len != 0)
	{
		semi_final = ft_calloc(sizeof(char), len + 1);
		pan = 0;
		while (pan < len && pin < data->i)
		{
			ft_quotes_checker(data, buffer, data->i);
			if (data->s_quotes_switch == 1 || data->d_quotes_switch == 1)
				pin++;
			else
			{
				if (buffer[pin] == '"' || buffer[pin] == '\'')
					pin++;
				else
				{
					semi_final[pan] = buffer[pin];
					pan++;
					pin++;
				}
			}
		}
		semi_final[pan] = '\0';
		printf("4 %s\n", semi_final);
		cmd = ft_buffercmd_in_lst(semi_final, cmd, data);
		semi_final = NULL;
		free(semi_final);
		ft_quotes_checker(data, buffer, data->i);
	}
	return (cmd);
}
