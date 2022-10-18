/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:26:09 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/18 14:59:40 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

t_list	*ft_total_parsing(t_data	*data, char	*buffer)
{
	int	i;
	int	len;
	int	len_max;
	char	*semi_final;
	int		pin;
	int		pan;
	char	*value_env;
	t_list	*cmd;

	i = 0;
	len = 0;
	cmd = NULL;
	len_max = ft_strlen_parsing(buffer);
	semi_final = NULL;
	ft_reset_quotes_checker(data);
	while (buffer[i])
	{
		ft_quotes_checker(data, buffer, i);
/*****************************************************************************/	
/* 							SI LES "" ET LES ''								 */
/*****************************************************************************/
		while (data->s_quotes_switch == 1 || data->d_quotes_switch == 1)
		{
/*						SI C'EST DES DOUBLE QUOTES							*/
			while (data->d_quotes_switch == 1)
			{
				if (buffer[i] == DOUBLE_QUOTE)
					i++;
				pin = i;
				len = 0;
				while (i < len_max && buffer[i] != '$' && buffer[i] != DOUBLE_QUOTE)
				{
					len++;
					i++;
				}
				if (len != 0)
				{
					semi_final = malloc(sizeof(char) * len + 1);
					if (!semi_final)
						exit(57);
					pan = 0;
					while (pin < i)
						semi_final[pan++] = buffer[pin++];
					semi_final[pan] = '\0';
				}
				if (buffer[i] == '$')
				{
					len = 0;
					i++;
					pin = i;
					while (buffer[i] && ((buffer[i] >= 'A' && buffer[i] <= 'Z') || buffer[i] == '_') && buffer[i] != DOUBLE_QUOTE)
					{
						i++;
						len++;
					}
					value_env = malloc(sizeof(char) * len + 1);
					if (!value_env)
						exit(58);
					pan = 0;
					while (pan < len)
						value_env[pan++] = buffer[pin++];
					value_env[pan] = '\0';
					value_env = ft_env_getstr_env_value(data->env, value_env);
					semi_final = ft_strjoin_parsing(semi_final, value_env);
					free(value_env);
					value_env = NULL;
				}
				printf("1 %s\n", semi_final);
				cmd = ft_buffercmd_in_lst_quotes(semi_final, cmd, data);
				free(semi_final);
				ft_quotes_checker(data, buffer, i);
				i++;
			}
/*						SI C'EST DES SIMPLE QUOTES							*/
			while (data->s_quotes_switch == 1)
			{
				if (buffer[i] == SIMPLE_QUOTE)
					i++;
				pin = i;
				len = 0;
				while (i < len_max && buffer[i] != SIMPLE_QUOTE)
				{
					len++;
					i++;
				}
				if (len != 0)
				{
					semi_final = malloc(sizeof(char) * len + 1);
					if (!semi_final)
						exit(57);
					pan = 0;
					while (pin < i)
						semi_final[pan++] = buffer[pin++];
					semi_final[pan] = '\0';
				}
				ft_quotes_checker(data, buffer, i);
				printf("2 %s\n", semi_final);
				cmd = ft_buffercmd_in_lst_quotes(semi_final, cmd, data);
				free(semi_final);
				i++;
			}
		}
/*****************************************************************************/	
/* 									SI $									 */
/*****************************************************************************/
		if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0 && buffer[i] == '$')
		{
			pin = i;
			i++;
			while (buffer[i] && ((buffer[i] >= 'A' && buffer[i] <= 'Z') || buffer[i] == '_'))
			{
				i++;
				len++;
			}
			if (buffer[i] != '\t' && buffer[i] != '\n' && buffer[i] != '\r' && buffer[i] != '\v' && buffer[i] != '\f' && buffer[i] != '\0')
				i = pin;
			else
			{
				value_env = malloc(sizeof(char) * len + 1);
				if (!value_env)
					exit (37);
				pan = 0;
				pin++;
				while (pin < i)
					value_env[pan++] = buffer[pin++];
				value_env[pan] = '\0';
				value_env = ft_env_getstr_env_value(data->env, value_env); 
				semi_final = ft_strjoin_parsing(semi_final, value_env);
				free(value_env);
				printf("3 %s\n", semi_final);
				cmd = ft_buffercmd_in_lst(semi_final, cmd, data);
				free(semi_final);
				ft_quotes_checker(data, buffer, i);
			}
			i++;
		}
/*****************************************************************************/	
/* 									SI NORMAL								 */
/*****************************************************************************/
		else if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0)
		{
			pin = i;
			len = 0;
			while (buffer[i] >= 33 && buffer[i] <= 126 && buffer[i] != '$' && buffer[i] != '\'' && buffer[i] != '"' && buffer[i] != '\0')
			{
				i++;
				len++;
			}
			semi_final = malloc(sizeof(char) * len + 1);
			if (!semi_final)
				return (0);
				pan = 0;
			while (pin < i)
			{
				semi_final[pan] = buffer[pin];
				pan++;
				pin++;
			}
			semi_final[pin] = '\0';
			printf("4 %s\n", semi_final);
			cmd = ft_buffercmd_in_lst(semi_final, cmd, data);
			free(semi_final);
			ft_quotes_checker(data, buffer, i);
			i++;
		}
	}		
	return (cmd);
}