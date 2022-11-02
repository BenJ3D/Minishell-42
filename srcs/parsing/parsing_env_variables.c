/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_env_variables.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:57:02 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/02 13:38:04 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

char	*ft_strndup(const char *s1, int 	len)
{
	char	*res;
	size_t	i;

	i = 0;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (s1[i] && i < len)
	{
		res[i] = s1[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

static char	*ft_echo_var_no_env(t_data	*data, char	*buffer)
{
	int	len;
	char	*semi_final;
	
	len = 0;
	data->i++;
	semi_final = NULL;
	while(buffer[data->i] != '\'' && buffer[data->i] != '"' && ft_isalnum(buffer[data->i]))
	{
		len++;
		data->i++;
	}
	if (len != 0)
	{
		semi_final = ft_strndup(buffer + data->i, len);
		if (!semi_final)
			return (NULL);
	}
	return (semi_final);
}

char	*ft_double_quotes_env(t_data	*data, char	*buffer, char	*semi_final)
{
	int		len;
	int		pin;
	int		pan;
	char	*value_env;

	len = 0;
	data->i++;
	pin = data->i;
	value_env = NULL;
	printf("test\n");
	if (buffer[data->i] >= '0' && buffer[data->i] <= '9')
	{
		if (semi_final == NULL)
			semi_final = ft_echo_var_no_env(data, buffer); //TODO coder cette fonction ou en tout cas cette hypothese
		else
		{
			value_env = ft_echo_var_no_env(data, buffer);
			semi_final = ft_strjoin(semi_final, value_env);
			free(value_env);
		}
		return(semi_final);
	}
	printf("test2\n");
	while (buffer[data->i] && (ft_isalnum(buffer[data->i]) ||  buffer[data->i] == '_') && buffer[data->i] != DOUBLE_QUOTE)
	{
		data->i++;
		len++;
	}
	if (len != 0)
	{
		value_env = ft_calloc(sizeof(char), len + 1);
		pan = 0;
		while (pan < len)
			value_env[pan++] = buffer[pin++];
		value_env[pan] = '\0';
		
		if (data->cmdtoparse->type != IN1 && data->cmdtoparse->type != IN2)
		{
			value_env = ft_env_getstr_env_value(data->env, value_env);
			if (!value_env)
			{
				free(value_env);
				return (NULL);
			}
		}
		if (semi_final != NULL)
		{
			semi_final = ft_strjoin_parsing(semi_final, value_env);
			free(value_env);
		}
	}
	printf("tes3\n");
	return (semi_final);
}

t_list	*ft_parsing_env_variable(t_data	*data, char	*buffer)
{
	int		pin;
	int		pan;
	int		len;
	char	*value_env;

	if (!data->cmdtoparse)
		data->i++;
	if (data->cmdtoparse && data->cmdtoparse->str[0] != '<')
		data->i++;
	pin = data->i;
	len = 0;
	while (buffer[data->i] && (buffer[data->i] >= 33 && buffer[data->i] <= 126))
	{
		data->i++;
		len++;
	}
	if (len != 0)
	{
		value_env = ft_calloc(sizeof(char), len + 1);
		pan = 0;
		while (pin < data->i)
			value_env[pan++] = buffer[pin++];
		value_env[pan] = '\0';
		if (data->cmdtoparse && data->cmdtoparse->str[0] == '<')
			pan = 0;
		else
		{
			value_env = ft_env_getstr_env_value(data->env, value_env);
			if (!value_env)
				return (data->cmdtoparse);
		}
		ft_buffercmd_in_lst(value_env, data, 0);
		free(value_env);
		ft_quotes_checker(data, buffer, data->i);
	}
	else
		ft_buffercmd_in_lst("$", data, 1);
	return (data->cmdtoparse);
}
