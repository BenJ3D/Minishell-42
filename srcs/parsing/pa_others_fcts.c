/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_others_fcts.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:18:35 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/11 15:48:07 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	ft_parsing_others_setings(t_data	*data, char	*buffer, int choice)
{
	if (choice == 1)
	{
		if (buffer[data->scroller] == '"')
			data->d_quotes_switch = 1;
		else
			data->s_quotes_switch = 1;
	}
	else if (choice == 2)
	{
		ft_reset_quotes_checker(data);
		data->quotes_in_parsing = 1;
		data->scroller++;
	}
}

int	ft_pa_others_len(t_data	*data, char	*buffer)
{
	int	len;

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
	return (len);
}

char	*ft_pa_others_existing_quotes(t_data	*data, char	*buffer, \
	char	*semi_final)
{
	char	*doll;

	doll = ft_quotes(data, buffer);
	if (doll != NULL)
	{
		semi_final = ft_strjoin_parsing(semi_final, doll);
		free(doll);
		doll = NULL;
	}
	return (semi_final);
}
