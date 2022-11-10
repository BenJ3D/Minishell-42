/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_double_quotes_env_cmp.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:24:45 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/10 16:53:30 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*ft_pa_dq_env(t_data	*data, char	*buffer, char	*semi_final, \
	int len)
{
	char	*value_env;
	char	*final;
	int		pan;

	pan = 0;
	value_env = ft_pa_fill_value(data, buffer, len);
	if (data->cmdtoparse && (data->cmdtoparse->type == IN1 || \
		data->cmdtoparse->type == IN2))
		pan = 0;
	else
	{
		value_env = ft_pa_dq_env_bis(data, value_env);
		if (!value_env)
		{
			printf("'%s', value_env\n", __func__);
			free(value_env);
			value_env = NULL;
			return (semi_final);
		}
	}
	final = ft_pq_dq_env_final(semi_final, value_env);
	return (final);
}

int	ft_pa_dq_len(t_data	*data, char	*buffer)
{
	int	len;

	len = 0;
	while (buffer[data->scroller] && (ft_isalnum(buffer[data->scroller]) || \
		buffer[data->scroller] == '_') && buffer[data->scroller] != \
			DOUBLE_QUOTE)
	{
		data->scroller++;
		len++;
	}
	return (len);
}

char	*ft_double_quotes_env(t_data	*data, char	*buffer, char	*semi_final)
{
	int		len;
	int		pin;
	char	*final;

	len = 0;
	data->scroller++;
	pin = data->scroller;
	if (buffer[data->scroller] == '?')
	{
		final = ft_padq_env_code_error(data, semi_final);
		return (final);
	}
	else if (buffer[data->scroller] >= '0' && buffer[data->scroller] <= '9')
	{
		semi_final = ft_padq_env_digits(data, semi_final, buffer);
		return (semi_final);
	}
	len = ft_pa_dq_len(data, buffer);
	if (len != 0)
		final = ft_pa_dq_env(data, buffer, semi_final, len);
	else
		final = ft_strdup("$");
	return (final);
}
