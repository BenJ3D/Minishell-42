/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:57:02 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/02 11:34:44 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*ft_double_quotes_env(t_data	*data, char	*buffer, char	*semi_final)
{
	int		len;
	int		pin;
	int		pan;
	char	*value_env;
	char	*final;

	len = 0;
	data->scroller++;
	pin = data->scroller;
	value_env = NULL;
	final = NULL;
	while (buffer[data->scroller] && ((buffer[data->scroller] >= 'A' && buffer[data->scroller] <= \
		'Z') || buffer[data->scroller] == '_') && buffer[data->scroller] != DOUBLE_QUOTE)
	{
		data->scroller++;
		len++;
	}
	if (len != 0)
	{
		value_env = ft_calloc(sizeof(char), len + 1);
		pan = 0;
		while (pan < len)
			value_env[pan++] = buffer[pin++];
		value_env[pan] = '\0';
		
		if (data->cmdtoparse->type != IN1 && data->cmdtoparse->type != IN2)
		{
			value_env = ft_env_getstr_env_value(data->env, value_env);
			if (!value_env)
			{
				free(value_env);
				printf(" test %s\n", semi_final);
				return (semi_final);
			}
		}
		if (semi_final != NULL)
		{
			final = ft_strjoin_parsing(semi_final, value_env);
			free(value_env);
		}
		else
		{
			final = ft_strdup(value_env);
			free(value_env);
		}
	}
	return (final);
}

t_list	*ft_parsing_env_variable(t_data	*data, char	*buffer)
{
	int		pin;
	int		pan;
	int		len;
	char	*value_env;

	value_env = NULL;
	if (!data->cmdtoparse)
		data->scroller++;
	else if (data->cmdtoparse->str && data->cmdtoparse->str[0] != '<')
		data->scroller++;
	pin = data->scroller;
	len = 0;
	while (buffer[data->scroller] && (buffer[data->scroller] >= 33 && buffer[data->scroller] <= 126) \
		&& (buffer[data->scroller] != '\'' && buffer[data->scroller] != '"'))
	{
		data->scroller++;
		len++;
	}
	if (len != 0)
	{
		value_env = ft_calloc(sizeof(char), len + 1);
		pan = 0;
		while (pin < data->scroller)
			value_env[pan++] = buffer[pin++];
		value_env[pan] = '\0';
		if (data->cmdtoparse && data->cmdtoparse->str[0] != '<')
			pan = 0;
		else
		{
			value_env = ft_env_getstr_env_value(data->env, value_env);
			if (!value_env)
				return (data->cmdtoparse);
		}
		ft_buffercmd_in_lst(value_env, data, 0);
		free(value_env);
		ft_quotes_checker(data, buffer, data->scroller);
	}
	else
		ft_buffercmd_in_lst("$", data, 1);
	return (data->cmdtoparse);
}
