/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:12:40 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/02 19:09:41 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*ft_double_quotes(t_data	*data, char	*buffer, int len_max)
{
	int		pin;
	int		pan;
	int		len;
	char	*final;
	char	*semi_final;
	char	*trollo;

	semi_final = NULL;
	final = NULL;
	trollo = NULL;
	if (buffer[data->scroller] == DOUBLE_QUOTE)
		data->scroller++;
	while (data->d_quotes_switch == 1 && buffer[data->scroller] != '\0')
	{
		pin = data->scroller;
		len = 0;
		while (buffer[data->scroller] && buffer[data->scroller] \
			 != '$' && buffer[data->scroller] != DOUBLE_QUOTE)
		{
			len++;
			data->scroller++;
		}
		if (len != 0)
		{
			semi_final = ft_calloc(sizeof(char), len + 1);
			if (!semi_final)
				exit(57);
			pan = 0;
			while (pin < data->scroller)
				semi_final[pan++] = buffer[pin++];
			semi_final[pan] = '\0';
		}
		if (buffer[data->scroller] == '$')
		{
			if (final == NULL)
				final = ft_double_quotes_env(data, buffer, semi_final);
			else
			{
				trollo = ft_double_quotes_env(data, buffer, semi_final);
				final = ft_strjoin(final, trollo);
			}
		}
		else if (final != NULL)
			final = ft_strjoin(final, semi_final);
		else
		{
			final = ft_strdup(semi_final);
			free(semi_final);
		}
		semi_final = NULL;
		ft_quotes_checker(data, buffer, data->scroller);
	}
	return (final);
}

char	*ft_simple_quotes(t_data	*data, char	*buffer, int len_max)
{
	int		pin;
	int		pan;
	int		len;
	char	*semi_final;

	semi_final = NULL;
	if (buffer[data->scroller] == SIMPLE_QUOTE)
		data->scroller++;
	pin = data->scroller;
	len = 0;
	while (data->scroller < len_max && buffer[data->scroller] != SIMPLE_QUOTE)
	{
		len++;
		data->scroller++;
	}
	if (len != 0)
	{
		semi_final = ft_calloc(sizeof(char), len + 1);
		if (!semi_final)
			exit(57);
		pan = 0;
		while (pin < data->scroller)
			semi_final[pan++] = buffer[pin++];
		semi_final[pan] = '\0';
	}
	ft_quotes_checker(data, buffer, data->scroller);
	return (semi_final);
}

char	*ft_quotes(t_data	*data, char	*buffer, int len_max)
{
	char	*final;

	final = NULL;
	if (data->d_quotes_switch == 1)
		final = ft_double_quotes(data, buffer, len_max);
	if (data->s_quotes_switch == 1)
		final = ft_simple_quotes(data, buffer, len_max);
	return (final);
}
