/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parsing_complementary.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:06:47 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/10 17:25:58 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*ft_dq_specials(t_data	*data, char	*buffer, char	*semi_final, \
	char	*final)
{
	if (buffer[data->scroller] == '$')
		final = ft_dq_get_env(data, buffer, semi_final, final);
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
	printf("'%s' semi_final\n", __func__);
	semi_final = NULL;
	return (final);
}
