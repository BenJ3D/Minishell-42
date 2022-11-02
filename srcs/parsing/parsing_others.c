/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_others.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:55:59 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/02 19:29:59 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

// int	ft_parsing_others(t_data	*data, char	*buffer)
// {
// 	int		pin;
// 	int		len;
// 	int		pan;
// 	char	*semi_final;

// 	len = 0;
// 	while (buffer[data->scroller] < 33 && buffer[data->scroller] > 126 && buffer[data->scroller] \
// 		!= '\0' && buffer[data->scroller] \
// 		!= '$' && buffer[data->scroller] != '\'' && buffer[data->scroller] != '"')
// 		data->scroller++;
// 	pin = data->scroller;
// 	while (buffer[data->scroller] != '\0' && buffer[data->scroller] >= 33 && buffer[data->scroller] \
// 		<= 126 && (buffer[data->scroller] != '>' && buffer[data->scroller] != '<'))
// 	{
// 		data->scroller++;
// 		len++;
// 	}
// 	if (len != 0)
// 	{
// 		semi_final = ft_calloc(sizeof(char), len + 1);
// 		pan = 0;
// 		while (pan < len && pin < data->scroller)
// 		{
// 			ft_quotes_checker(data, buffer, data->scroller);
// 			if (data->s_quotes_switch == 1 || data->d_quotes_switch == 1)
// 				pin++;
// 			else
// 			{
// 				if (buffer[pin] == '"' || buffer[pin] == '\'')
// 					pin++;
// 				else
// 				{
// 					semi_final[pan] = buffer[pin];
// 					pan++;
// 					pin++;
// 				}
// 			}
// 		}
// 		semi_final[pan] = '\0';
// 		ft_buffercmd_in_lst(semi_final, data, 0);
// 		free(semi_final);
// 		semi_final = NULL;
// 		ft_quotes_checker(data, buffer, data->scroller);
// 	}
// 	return (1);
// }


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
	while ((buffer[data->scroller] && buffer[data->scroller] >= 33 && \
		buffer[data->scroller] <= 126) && buffer[data->scroller] != '<' && \
			buffer[data->scroller] != '>' && buffer[data->scroller] != '|')
	{
		pin = data->scroller;
		len = 0;
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
				doll = ft_double_quotes_env(data, buffer, semi_final);
				semi_final = ft_strjoin(semi_final, doll);
			}
		}
		else if (buffer[data->scroller] == '"' || buffer[data->scroller] == '\'')
		{
			if (semi_final == NULL)
				semi_final = ft_quotes(data, buffer, len_max);
			else
				doll = ft_quotes(data, buffer, len_max);
				printf("%s %s\n", semi_final, doll);
				semi_final = ft_strjoin(semi_final, doll);
		}
		if (final != NULL)
		{
			final = ft_strjoin(final, semi_final);
		}
		else
		{
			final = ft_strdup(semi_final);
			free(semi_final);
			semi_final = NULL;
		}
	}
	ft_buffercmd_in_lst(final, data, 0);
	free(final);
	final = NULL;
	return (1);
}