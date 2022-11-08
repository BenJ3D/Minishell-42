/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:57:02 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/08 13:15:19 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*ft_strndup(const char *s1, int 	len)
{
	char	*res;
	size_t	i;

	i = 0;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (s1[i] && i < len)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_var_no_env(t_data	*data, char	*buffer)
{
	int	len;
	char	*semi_final;
	int		pin;
	
	len = 0;
	data->scroller++;
	pin = data->scroller;
	semi_final = NULL;
	while(buffer[data->scroller] != '\'' && buffer[data->scroller] != '"' && \
		ft_isalnum(buffer[data->scroller]))
	{
		len++;
		data->scroller++;
	}
	if (len != 0)
	{
		semi_final = ft_strndup(buffer + pin, len);
		if (!semi_final)
			return (NULL);
	}
	return (semi_final);
}

char	*ft_double_quotes_env(t_data	*data, char	*buffer, char	*semi_final)
{
	int		len;
	int		pin;
	int		pan;
	char	*value_env;
	char	*final;

	len = 0;
	printf("%s\n", buffer + data->scroller);
	data->scroller++;
	pin = data->scroller;
	value_env = NULL;
	final = NULL;
	if (buffer[data->scroller] == '?')
	{
		if (semi_final == NULL)
			semi_final = ft_itoa(g_status % 255);
		else
		{
			value_env = ft_itoa(g_status % 255);
			semi_final = ft_strjoin(semi_final, value_env);
			free(value_env);
		}
		data->scroller++;
		return(semi_final);
	}
	else if (buffer[data->scroller] >= '0' && buffer[data->scroller] <= '9')
	{
		if (semi_final == NULL)
			semi_final = ft_var_no_env(data, buffer);
		else
		{
			value_env = ft_var_no_env(data, buffer);
			semi_final = ft_strjoin(semi_final, value_env);
			free(value_env);
		}
		return(semi_final);
	}
	while (buffer[data->scroller] && (ft_isalnum(buffer[data->scroller]) || \
		buffer[data->scroller] == '_') && buffer[data->scroller] != DOUBLE_QUOTE)
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
		if (data->cmdtoparse && (data->cmdtoparse->type == IN1 || data->cmdtoparse->type == IN2))
			pan = 0;
		else
		{
			value_env = ft_env_getstr_env_value(data->env, value_env);
			if (!value_env)
			{
				free(value_env);
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
	else
		final = ft_strdup("$");
	return (final);
}

char	*ft_parsing_env_variable(t_data	*data, char	*buffer)
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
	while (buffer[data->scroller] && (ft_isalnum(buffer[data->scroller]) || \
		buffer[data->scroller] == '_'))
	{
		data->scroller++;
		len++;
	}
	if (len != 0)
	{
		if (buffer[pin] == '?')
		{
			value_env = ft_itoa(g_status % 255);
			if (!value_env)
				return (NULL);
		}
		else if (buffer[pin] >= '0' && buffer[pin] <= '9')
		{
			data->scroller = pin;
			value_env = ft_var_no_env(data, buffer);
			if (!value_env)
				return (NULL);
		}
		else
		{
			value_env = ft_calloc(sizeof(char), len + 1);
			pan = 0;
			while (pin < data->scroller)
				value_env[pan++] = buffer[pin++];
			value_env[pan] = '\0';
			if (data->cmdtoparse && data->cmdtoparse->str[0] == '<')
				pan = 0;
			else
			{
				value_env = ft_env_getstr_env_value(data->env, value_env);
				if (!value_env)
					return (NULL);
			}
		}
	}
	else if (buffer[pin] == '?')
	{
		data->scroller++;
		value_env = ft_itoa(g_status % 255);
		if (!value_env)
			return (NULL);
	}
	else
		value_env = ft_strdup("$");
	return (value_env);
}
