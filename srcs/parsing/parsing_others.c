/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_others.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:55:59 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/09 13:50:17 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*ft_parsing_others_normal(t_data	*data, char	*buffer, int len, int pin)
{
	int		pan;
	char	*semi_final;

	semi_final = NULL;
	semi_final = ft_calloc(sizeof(char), (len + 1));
	if (!semi_final)
		exit (11);
	pan = 0;
	while (pin < data->scroller)
		semi_final[pan++] = buffer[pin++];
	semi_final[pan] = '\0';
	return (semi_final);
}

char	*ft_parsing_others_normal_env(t_data	*data, char	*buffer, char	*semi_final)
{
	if (semi_final == NULL)
		semi_final = ft_parsing_env_variable(data, buffer);
	else
		semi_final = ft_double_quotes_env(data, buffer, semi_final);
	return (semi_final);
}

char	*ft_parsing_others_not_normal_env(t_data	*data, char	*buffer, char	*semi_final, int pin, int len)
{
	int	pan;

	if (semi_final == NULL)
	{
		pin = data->scroller;
		len = 0;
		while (buffer[data->scroller] != '\0' && buffer[data->scroller] \
			>= 33 && buffer[data->scroller] <= 126)
		{
			len++;
			data->scroller++;
		}
		semi_final = ft_calloc(sizeof(char), (len + 1));
		if (!semi_final)
			exit (11);
		pan = 0;
		while (pin < data->scroller)
			semi_final[pan++] = buffer[pin++];
		semi_final[pan] = '\0';
	}
	return (semi_final);
}

void	ft_parsing_others_final(t_data	*data, char	*final)
{
	if (data->quotes_in_parsing == 1)
		ft_buffercmd_in_lst_quotes(final, data, 1, 0);
	else
		ft_buffercmd_in_lst(final, data, 0, 0);
	free(final);
}

int	ft_parsing_others(t_data	*data, char *buffer, int len_max)
{
	int		len;
	int		pin;
	int		pan;
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
			semi_final = ft_parsing_others_normal(data, buffer, len_max, pin);
		if (buffer[data->scroller] == '$' && data->type_of_the_last_cmd != 4)
			semi_final = ft_parsing_others_normal_env(data, buffer, \
				semi_final);
		else if (buffer[data->scroller] == '$' && data->type_of_the_last_cmd \
			== 4)
			semi_final = ft_parsing_others_not_normal_env(data, buffer, \
				semi_final, pin, len);
		else if (buffer[data->scroller] == '"' || buffer[data->scroller] == \
			'\'')
		{	
			if (buffer[data->scroller] == '"')
				data->d_quotes_switch = 1;
			else
				data->s_quotes_switch = 1;
			if (semi_final == NULL)
			{
				semi_final = ft_quotes(data, buffer, len_max);
				if (!semi_final)
				{
					if (buffer[data->scroller + 1] && (buffer[data->scroller \
						+ 1] <= 32 || buffer[data->scroller + 1] > 126))
					{
						data->scroller++;
						ft_buffercmd_in_lst_quotes(" ", data, 1, 1);
						return (0);
					}
				}
			}
			else
			{
				doll = ft_quotes(data, buffer, len_max);
				if (doll != NULL)
				{
					semi_final = ft_strjoin(semi_final, doll);
					free(doll);
					doll = NULL;
				}
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
				free(semi_final);
				semi_final = NULL;
			}
		}
		else
		{
			if (semi_final != NULL)
			{
				final = ft_strjoin(final, semi_final);
				free(semi_final);
				semi_final = NULL;
			}
		}
	}
	free(semi_final);
	if (final != NULL)
		ft_parsing_others_final(data, final);
	data->quotes_in_parsing = 0;
	return (1);
}