/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_others.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:55:59 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/07 16:34:36 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_parsing_others(t_data	*data, char *buffer, int	len_max)
{
	int	len;
	int	pin;
	int	pan;
	char	*semi_final;
	char	*final;
	char	*doll;

	len = 0;
	semi_final = NULL;
	final = NULL;
	doll = NULL;
	data->quotes_in_parsing = 0;
	while ((data->scroller < len_max && buffer[data->scroller] >= 33 && \
		buffer[data->scroller] <= 126) && buffer[data->scroller] != '<' && \
			buffer[data->scroller] != '>' && buffer[data->scroller] != '|')
	{
		pin = data->scroller;
		len = 0;
		semi_final = NULL;
		while (buffer[data->scroller] && buffer[data->scroller] >= 33 && \
		buffer[data->scroller] <= 126 && buffer[data->scroller] != '<' && \
			buffer[data->scroller] != '>' && buffer[data->scroller] != '$' && \
				buffer[data->scroller] != '\'' && buffer[data->scroller] != '"' \
					&& buffer[data->scroller] != '|')
		{
			data->scroller++;
			len++;
		}
		if (len != 0)
		{
			semi_final = ft_calloc(sizeof(char), (len + 1));
			if (!semi_final)
				exit (11);
			pan = 0;
			while (pin < data->scroller)
				semi_final[pan++] = buffer[pin++];
			semi_final[pan] = '\0';
		}
		if (buffer[data->scroller] == '$')
		{
			if (semi_final == NULL)
				semi_final = ft_parsing_env_variable(data, buffer);
			else
			{
				doll = ft_parsing_env_variable(data, buffer);
				if (doll != NULL)
					semi_final = ft_strjoin(semi_final, doll);
			}
		}
		else if (buffer[data->scroller] == '"' || buffer[data->scroller] == '\'')
		{
			if(buffer[data->scroller] == '"')
				data->d_quotes_switch = 1;
			else
				data->s_quotes_switch = 1;
			if (semi_final == NULL)
			{
				semi_final = ft_quotes(data, buffer, len_max);
				if (semi_final == NULL && (buffer[++data->scroller] < 33 || buffer[data->scroller] > 126))
				{
						ft_buffercmd_in_lst_quotes("\0", data, 1);
						free(semi_final);
						data->quotes_in_parsing = 0;
						return (1);
				}
				else
					data->scroller--;
			}
			else
			{
				doll = ft_quotes(data, buffer, len_max);
				if (doll != NULL)
					semi_final = ft_strjoin(semi_final, doll);
			}
			ft_reset_quotes_checker(data);
			data->quotes_in_parsing = 1;
			data->scroller++;
		}
		if (final == NULL)
		{
			if (semi_final != NULL)
			{
				final = ft_strdup(semi_final);
				semi_final = NULL;
			}
		}
		else
		{
			if (semi_final != NULL)
				final = ft_strjoin(final, semi_final);
			semi_final = NULL;
		}
	}
	if (final != NULL)
	{
		if (data->quotes_in_parsing == 1)
			ft_buffercmd_in_lst_quotes(final, data, 1);
		else
			ft_buffercmd_in_lst(final, data, 0);
	}
	data->quotes_in_parsing = 0;
	free(final);
	final = NULL;
	return (1);
}