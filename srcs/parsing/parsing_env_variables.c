/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:57:02 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/27 12:08:43 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*ft_double_quotes_env(t_data	*data, char	*buffer, char	*semi_final, t_list	*cmd)
{
	int		len;
	int		pin;
	int		pan;
	char	*value_env;

	len = 0;
	data->i++;
	pin = data->i;
	value_env = NULL;
	while (buffer[data->i] && ((buffer[data->i] >= 'A' && buffer[data->i] <= \
		'Z') || buffer[data->i] == '_') && buffer[data->i] != DOUBLE_QUOTE)
	{
		data->i++;
		len++;
	}
	if (len != 0)
	{
		value_env = ft_calloc(sizeof(char), len + 1);
		pan = 0;
		while (pan < len)
			value_env[pan++] = buffer[pin++];
		value_env[pan] = '\0';
		if (cmd->type != IN1 && cmd->type != IN2)
		{
			value_env = ft_env_getstr_env_value(data->env, value_env);
			if (!value_env)
			{
				free(value_env);
				return (NULL);
			}
		}
		if (semi_final != NULL)
		{
			semi_final = ft_strjoin_parsing(semi_final, value_env);
			free(value_env);
		}
	}
	return (semi_final);
}

t_list	*ft_parsing_env_variable(t_data	*data, t_list	*cmd, char	*buffer)
{
	int		pin;
	int		pan;
	int		len;
	char	*value_env;

	if (cmd->str[0] != '<')
		data->i++;
	pin = data->i;
	len = 0;
	while (buffer[data->i] && (buffer[data->i] >= 33 && buffer[data->i] <= 126))
	{
		data->i++;
		len++;
	}
	if (len != 0)
	{
		value_env = ft_calloc(sizeof(char), len + 1);
		pan = 0;
		while (pin < data->i)
			value_env[pan++] = buffer[pin++];
		value_env[pan] = '\0';
		if (cmd->str[0] != '<')
		{
			value_env = ft_env_getstr_env_value(data->env, value_env);
			if (!value_env)
				return (cmd);
		}
		cmd = ft_buffercmd_in_lst(value_env, cmd, data);
		free(value_env);
		ft_quotes_checker(data, buffer, data->i);
	}
	else
		cmd = ft_buffercmd_in_lst("$", cmd, data);
	return (cmd);
}
