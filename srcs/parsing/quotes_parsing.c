/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:12:40 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/31 14:59:50 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*ft_strdup_parsing(const char *s1)
{
	char	*res;
	size_t	i;

	i = 0;
	res = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!res)
		return (NULL);
	while (s1[i])
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

int	ft_double_quotes(t_data	*data, char	*buffer, int len_max)
{
	int		pin;
	int		pan;
	int		len;
	char	*final;
	char	*semi_final;

	semi_final = NULL;
	final = NULL;
	if (buffer[data->i] == DOUBLE_QUOTE)
		data->i++;
	while (data->d_quotes_switch == 1 && buffer[data->i] != '\0')
	{
		pin = data->i;
		len = 0;
		while (data->i < len_max && buffer[data->i] != '$' && buffer[data->i] \
			!= DOUBLE_QUOTE)
		{
			len++;
			data->i++;
		}
		if (len != 0)
		{
			semi_final = ft_calloc(sizeof(char), len + 1);
			if (!semi_final)
				exit(57);
			pan = 0;
			while (pin < data->i)
				semi_final[pan++] = buffer[pin++];
			semi_final[pan] = '\0';
		}
		printf("ici %s\n", semi_final);
		if (buffer[data->i] == '$')
			final = ft_double_quotes_env(data, buffer, semi_final);
		else
			final = ft_strdup_parsing((const)semi_final);
		semi_final = NULL;
		ft_quotes_checker(data, buffer, data->i);
	}
	if (semi_final != NULL)
	{
		ft_buffercmd_in_lst_quotes(final, data, 1);
		free(final);
	}
	else
		return (0);
	return (1);
}

void	ft_simple_quotes(t_data	*data, char	*buffer, int len_max)
{
	int		pin;
	int		pan;
	int		len;
	char	*semi_final;

	semi_final = NULL;
	if (buffer[data->i] == SIMPLE_QUOTE)
		data->i++;
	pin = data->i;
	len = 0;
	while (data->i < len_max && buffer[data->i] != SIMPLE_QUOTE)
	{
		len++;
		data->i++;
	}
	if (len != 0)
	{
		semi_final = ft_calloc(sizeof(char), len + 1);
		if (!semi_final)
			exit(57);
		pan = 0;
		while (pin < data->i)
			semi_final[pan++] = buffer[pin++];
		semi_final[pan] = '\0';
		ft_buffercmd_in_lst_quotes(semi_final, data, 1);
		free(semi_final);
	}
	ft_quotes_checker(data, buffer, data->i);
}

void	ft_quotes(t_data	*data, char	*buffer, int len_max)
{
	if (data->d_quotes_switch == 1)
		ft_double_quotes(data, buffer, len_max);
	while (data->s_quotes_switch == 1)
		ft_simple_quotes(data, buffer, len_max);
}
