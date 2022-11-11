/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_others_complementary.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:22:58 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/11 16:38:58 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*ft_pa_others_normal(t_data	*data, char	*buffer, int len)
{
	int		pan;
	char	*semi_final;
	int		pin;

	pin = data->scroller - len;
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

char	*ft_pa_others_normal_env(t_data	*data, char	*buffer, char	*semi_final)
{
	if (semi_final == NULL)
		semi_final = ft_parsing_env_variable(data, buffer);
	else
		semi_final = ft_double_quotes_env(data, buffer, semi_final);
	return (semi_final);
}

char	*ft_parsing_make_final(char	*semi_final, char	*final)
{
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
			final = ft_strjoin_parsing(final, semi_final);
			free(semi_final);
			semi_final = NULL;
		}
	}
	return (final);
}

char	*ft_parsing_others_not_normal_env(t_data	*data, char	*buffer, \
	char	*semi_final)
{
	int	pan;
	int	pin;
	int	len;

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
	final = NULL;
}
