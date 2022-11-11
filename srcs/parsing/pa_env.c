/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:58:53 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/11 11:54:24 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	ft_pa_env_set(t_data	*data)
{
	if (!data->cmdtoparse)
		data->scroller++;
	else if (data->cmdtoparse->str && data->cmdtoparse->str[1] != '<')
		data->scroller++;
}

char	*ft_pa_env_regular_bis(t_data	*data, char	*value_env)
{
	char	*tmp;

	tmp = ft_strdup(value_env);
	free(value_env);
	value_env = ft_env_getstr_env_value(data->env, tmp);
	free(tmp);
	if (!value_env)
	{
		if (data->type_of_the_last_cmd == 3 || data->type_of_the_last_cmd == 5 \
			|| data->type_of_the_last_cmd == 6)
			value_env = ft_strdup("$");
		else
		{
			free(value_env);
			value_env = NULL;
			return (NULL);
		}
	}
	return (value_env);
}

char	*ft_pa_env_regular_len(t_data	*data, char	*buffer, int len, int pin)
{
	char	*value_env;
	int		pan;

	value_env = ft_calloc(sizeof(char), len + 1);
	if (!value_env)
		return (NULL);
	pan = 0;
	while (pin < data->scroller)
		value_env[pan++] = buffer[pin++];
	value_env[pan] = '\0';
	if (data->cmdtoparse && data->cmdtoparse->str[1] == '<')
		pan = 0;
	else
		value_env = ft_pa_env_regular_bis(data, value_env);
	return (value_env);
}

char	*ft_pa_env_positive_len(t_data	*data, char	*buffer, int len, int pin)
{
	char	*value_env;

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
		value_env = ft_pa_env_regular_len(data, buffer, len, pin);
	return (value_env);
}

char	*ft_pa_env_regular_prime(t_data	*data, char	*buffer, int len, int pin)
{
	char	*value_env;

	value_env = NULL;
	if (len != 0)
		value_env = ft_pa_env_positive_len(data, buffer, len, pin);
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
