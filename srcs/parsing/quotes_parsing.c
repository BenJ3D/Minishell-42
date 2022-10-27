/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:12:40 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/27 18:18:58 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

t_list	*ft_double_quotes(t_data	*data, t_list	*cmd, char	*buffer, int len_max)
{
	int		pin;
	int		pan;
	int		len;
	char	*semi_final;

	semi_final = NULL;
	while (data->d_quotes_switch == 1 && buffer[data->i] != '\0')
	{
		if (buffer[data->i] == DOUBLE_QUOTE)
				data->i++;
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
		printf("semi_final %s\n", semi_final);
		if (buffer[data->i] == '$')
			semi_final = ft_double_quotes_env(data, buffer, semi_final, cmd);
		if (semi_final != NULL)
		{
			printf("1 %s\n", semi_final);
			cmd = ft_buffercmd_in_lst_quotes(semi_final, cmd, data);
			printf("%s\n", semi_final);
			free(semi_final);
		}
		else
			return (cmd);
		ft_quotes_checker(data, buffer, data->i);
	}
	return (cmd);
}

t_list	*ft_simple_quotes(t_data	*data, t_list	*cmd, char	*buffer, int len_max)
{
	int		pin;
	int		pan;
	int		len;
	char	*semi_final;

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
		cmd = ft_buffercmd_in_lst_quotes(semi_final, cmd, data);
		printf("2 %s\n", semi_final);
		free(semi_final);
	}
	ft_quotes_checker(data, buffer, data->i);
	return (cmd);
}

t_list	*ft_quotes(t_data	*data, char	*buffer, t_list	*cmd, int len_max)
{
	if (data->d_quotes_switch == 1)
		cmd = ft_double_quotes(data, cmd, buffer, len_max);
	while (data->s_quotes_switch == 1)
		cmd = ft_simple_quotes(data, cmd, buffer, len_max);
	return (cmd);
}
