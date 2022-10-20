/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:12:40 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/20 14:50:19 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*ft_double_quotes_env(t_data	*data, char	*buffer, char	*semi_final)
{
	int	len;
	int	pin;
	int	pan;
	char	*value_env;

	len = 0;
	data->i++;
	pin = data->i;
	value_env = NULL;
	while (buffer[data->i] && ((buffer[data->i] >= 'A' && buffer[data->i] <= \
		'Z') || buffer[data->i] == '_') && buffer[data->i] != DOUBLE_QUOTE)
	{
		data->i++;
		len++;
	}
	if (len != 0)
	{
		value_env = malloc(sizeof(char) * len + 1);
		if (!value_env)
			exit(58);
		pan = 0;
		while (pan < len)
			value_env[pan++] = buffer[pin++];
		value_env[pan] = '\0';
		value_env = ft_env_getstr_env_value(data->env, value_env);
		if (!value_env)
		{
			free(value_env);
			return (NULL);
		}
		printf("ici %s\n", value_env);
		if (semi_final != NULL)
		{
			printf("%s\n", semi_final);
			semi_final = ft_strjoin_parsing(semi_final, value_env);
			free(value_env);
		}
		else
		{
			printf("test\n");	
			return (value_env);
		}
	}
	return (semi_final);
}

t_list	*ft_double_quotes(t_data	*data, t_list	*cmd, char	*buffer, int len_max)
{
	int	pin;
	int	pan;
	int	len;
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
			semi_final = malloc(sizeof(char) * len + 1);
			if (!semi_final)
				exit(57);
			pan = 0;
			while (pin < data->i)
				semi_final[pan++] = buffer[pin++];
			semi_final[pan] = '\0';
		}
		printf("semi_final %s\n", semi_final);
		if (buffer[data->i] == '$')
			semi_final = ft_double_quotes_env(data, buffer, semi_final);
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
	int	pin;
	int	pan;
	int	len;
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
		semi_final = malloc(sizeof(char) * len + 1);
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

t_list	*ft_quotes(t_data	*data, char	*buffer, t_list	*cmd, int	len_max)
{
	if (data->d_quotes_switch == 1)
		cmd = ft_double_quotes(data, cmd, buffer, len_max);
	while (data->s_quotes_switch == 1)
		cmd = ft_simple_quotes(data, cmd, buffer, len_max);
	return (cmd);
}
