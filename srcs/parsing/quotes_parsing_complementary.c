/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parsing_complementary.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:06:47 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/12 19:10:38 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_dq_specials_doll(t_data	*data, char	*semi_final)
{
	char	*final;

	final = NULL;
	if (semi_final != NULL)
	{
		final = ft_strjoin(semi_final, "$");
	}
	else
		final = ft_strdup("$");
	data->scroller++;
	return (final);
}

char	*ft_dq_specials(t_data	*data, char	*buffer, char	*semi_final, \
	char	*final)
{
	if (buffer[data->scroller] == '$' && \
		ft_isalnum(buffer[data->scroller + 1]) == 1)
		final = ft_dq_get_env(data, buffer, semi_final, final);
	else if (buffer[data->scroller] == '$' && \
		ft_isalnum(buffer[data->scroller + 1]) == 0)
		final = ft_dq_specials_doll(data, semi_final);
	else if (final != NULL)
	{
		final = ft_strjoin_parsing(final, semi_final);
		free(semi_final);
	}
	else
	{
		if (semi_final != NULL)
		{
			final = ft_strdup(semi_final);
			free(semi_final);
		}
	}
	semi_final = NULL;
	return (final);
}
