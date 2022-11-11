/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_others.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:55:59 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/11 15:22:53 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_pa_others_quotes_alone(t_data	*data, char	*buffer)
{
	printf("Testici\n");
	if (buffer[data->scroller + 1] == '\0' || (buffer[data->scroller + 1] && \
		(buffer[data->scroller + 1] <= 32 || buffer[data->scroller + 1] > 126)))
	{
		printf("ici\n");
		data->scroller++;
		ft_buffercmd_in_lst_quotes(" ", data, 1, 1);
		return (0);
	}
	return (1);
}

char	*ft_pa_others_bis(t_data	*data, char	*buffer, char	*semi_final, \
	char	*final)
{
	if (buffer[data->scroller] == '$' && data->type_of_the_last_cmd != 4)
		semi_final = ft_pa_others_normal_env(data, buffer, semi_final);
	else if (buffer[data->scroller] == '$' && data->type_of_the_last_cmd \
		== 4)
		semi_final = ft_parsing_others_not_normal_env(data, buffer, \
			semi_final);
	else if (buffer[data->scroller] == '"' || buffer[data->scroller] == \
		'\'')
	{	
		ft_parsing_others_setings(data, buffer, 1);
		if (semi_final == NULL)
		{
			semi_final = ft_quotes(data, buffer);
			if (!semi_final && !final)
				if (!ft_pa_others_quotes_alone(data, buffer))
					return (0);
		}
		else
			semi_final = ft_pa_others_existing_quotes(data, buffer, \
				semi_final);
		ft_parsing_others_setings(data, buffer, 2);
	}
	data->quotes_in_parsing = 0;
	return (semi_final);
}

char	*ft_pa_others_cmp(t_data	*data, char	*buffer, char	*final)
{
	int		len;
	char	*semi_final;

	while ((data->scroller < data->len_max && buffer[data->scroller] >= 33 && \
		buffer[data->scroller] <= 126) && buffer[data->scroller] != '<' && \
			buffer[data->scroller] != '>' && buffer[data->scroller] != '|')
	{
		semi_final = NULL;
		len = ft_pa_others_len(data, buffer);
		if (len != 0)
			semi_final = ft_pa_others_normal(data, buffer, len);
		semi_final = ft_pa_others_bis(data, buffer, semi_final, final);
		final = ft_parsing_make_final(semi_final, final);
	}
	return (final);
}

int	ft_pa_others(t_data	*data, char *buffer)
{
	char	*final;

	final = NULL;
	data->quotes_in_parsing = 0;
	final = ft_pa_others_cmp(data, buffer, final);
	if (final != NULL)
		ft_parsing_others_final(data, final);
	return (1);
}
