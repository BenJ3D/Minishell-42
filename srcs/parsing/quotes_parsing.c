/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:12:40 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/11 11:19:00 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*ft_dq_get_env(t_data	*data, char	*buffer, char	*semi_final, \
	char	*final)
{
	char	*trollo;

	if (final == NULL)
	{
		final = ft_double_quotes_env(data, buffer, semi_final);
		printf("'%s', semi_final\n", __func__);
		//free(semi_final);
		semi_final = NULL;
	}
	else
	{
		trollo = ft_double_quotes_env(data, buffer, semi_final);
		final = ft_strjoin_parsing(final, trollo);
		printf("'%s', trollo\n", __func__);
		free(trollo);
		trollo = NULL;
	}
	return (final);
}

int	ft_dq_len(t_data	*data, char	*buffer)
{
	int	len;

	len = 0;
	while (buffer[data->scroller] && buffer[data->scroller] \
		!= '$' && buffer[data->scroller] != DOUBLE_QUOTE)
	{
		len++;
		data->scroller++;
	}
	return (len);
}

char	*ft_double_quotes(t_data	*data, char	*buffer)
{
	int		pin;
	int		len;
	char	*final;
	char	*semi_final;

	semi_final = NULL;
	final = NULL;
	if (buffer[data->scroller] == DOUBLE_QUOTE)
		data->scroller++;
	while (data->d_quotes_switch == 1 && buffer[data->scroller] != '\0')
	{
		pin = data->scroller;
		len = ft_dq_len(data, buffer);
		if (len != 0)
			semi_final = ft_pa_others_normal(data, buffer, \
			len);
		final = ft_dq_specials(data, buffer, semi_final, final);
		semi_final = NULL;
		ft_quotes_checker(data, buffer, data->scroller);
	}
	return (final);
}

char	*ft_simple_quotes(t_data	*data, char	*buffer)
{
	int		pin;
	int		len;
	char	*semi_final;

	semi_final = NULL;
	if (buffer[data->scroller] == SIMPLE_QUOTE)
		data->scroller++;
	pin = data->scroller;
	len = 0;
	while (data->scroller < data->len_max && buffer[data->scroller] != \
		SIMPLE_QUOTE)
	{
		len++;
		data->scroller++;
	}
	if (len != 0)
		semi_final = ft_pa_others_normal(data, buffer, \
			len);
	ft_quotes_checker(data, buffer, data->scroller);
	return (semi_final);
}

char	*ft_quotes(t_data	*data, char	*buffer)
{
	char	*final;

	final = NULL;
	if (data->d_quotes_switch == 1)
		final = ft_double_quotes(data, buffer);
	if (data->s_quotes_switch == 1)
		final = ft_simple_quotes(data, buffer);
	return (final);
}
