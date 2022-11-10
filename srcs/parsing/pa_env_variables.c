/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_env_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:57:02 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/10 22:49:42 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*ft_strndup(const char *s1, int len)
{
	char	*res;
	size_t	i;

	i = 0;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (s1[i] && i < (size_t)len)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_parsing_env_variable(t_data	*data, char	*buffer)
{
	int		pin;
	int		len;
	char	*value_env;

	ft_pa_env_set(data);
	pin = data->scroller;
	len = 0;
	while (buffer[data->scroller] && (ft_isalnum(buffer[data->scroller]) || \
		buffer[data->scroller] == '_'))
	{
		data->scroller++;
		len++;
	}
	value_env = ft_pa_env_regular_prime(data, buffer, len, pin);
	return (value_env);
}

char	*ft_var_no_env(t_data	*data, char	*buffer)
{
	int		len;
	char	*semi_final;
	int		pin;

	len = 0;
	data->scroller++;
	pin = data->scroller;
	semi_final = NULL;
	while (buffer[data->scroller] != '\'' && buffer[data->scroller] != '"' && \
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
