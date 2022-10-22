/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_others.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:55:59 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/22 16:05:10 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

t_list	*ft_parsing_others(t_data	*data, t_list	*cmd, char	*buffer)
{
	int	pin;
	int	len;
	int	pan;
	char	*semi_final;

	len = 0;
	while (buffer[data->i] < 33 && buffer[data->i] > 126 && buffer[data->i] != '\0' && buffer[data->i] \
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
		semi_final = malloc(sizeof(char) * len + 1);
		if (!semi_final)
			return (0);
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

t_list	*ft_parsing_env_variable(t_data	*data, t_list	*cmd, char	*buffer)
{
	int		pin;
	int		pan;
	int		len;
	char	*value_env;

	pin = data->i;
	data->i++;
	len = 0;
	while (buffer[data->i] && (buffer[data->i] >= 33 && buffer[data->i] <= 126))
	{
		data->i++;
		len++;
	}
	if (len != 0)
	{
		value_env = malloc(sizeof(char) * len + 1);
		if (!value_env)
			exit (37);
		pan = 0;
		pin++;
		while (pin < data->i)
			value_env[pan++] = buffer[pin++];
		value_env[pan] = '\0';
		value_env = ft_env_getstr_env_value(data->env, value_env); 
		if (!value_env)
			return (cmd);
		cmd = ft_buffercmd_in_lst(value_env, cmd, data);
		printf("3 %s\n", value_env);
		free(value_env);
		ft_quotes_checker(data, buffer, data->i);
	}
	else
		 cmd = ft_buffercmd_in_lst("$", cmd, data);
	return (cmd);
}
