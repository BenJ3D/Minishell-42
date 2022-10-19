/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:26:09 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/19 16:32:04 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

t_list	*ft_total_parsing(t_data	*data, char	*buffer)
{
	int	len;
	int	len_max;
	char	*semi_final;
	int		pin;
	int		pan;
	char	*value_env;
	t_list	*cmd;

	len = 0;
	cmd = NULL;
	data->i = 0;
	len_max = ft_strlen_parsing(buffer);
	semi_final = NULL;
	ft_reset_quotes_checker(data);
	while (buffer[data->i])
	{
		ft_quotes_checker(data, buffer, data->i);
/*****************************************************************************/	
/* 							SI LES "" ET LES ''								 */
/*****************************************************************************/
		while (data->s_quotes_switch == 1 || data->d_quotes_switch == 1)
		{
/*						SI C'EST DES DOUBLE QUOTES							*/
			cmd = ft_quotes(data, buffer, cmd, len_max);
// 			while (data->d_quotes_switch == 1)
// 			{
// 				if (buffer[data->i] == DOUBLE_QUOTE)
// 					data->i++;
// 				pin = data->i;
// 				len = 0;
// 				while (data->i < len_max && buffer[data->i] != '$' && buffer[data->i] != DOUBLE_QUOTE)
// 				{
// 					len++;
// 					data->i++;
// 				}
// 				if (len != 0)
// 				{
// 					semi_final = malloc(sizeof(char) * len + 1);
// 					if (!semi_final)
// 						exit(57);
// 					pan = 0;
// 					while (pin < data->i)
// 						semi_final[pan++] = buffer[pin++];
// 					semi_final[pan] = '\0';
// 				}
// 				if (buffer[data->i] == '$')
// 				{
// 					len = 0;
// 					data->i++;
// 					pin = data->i;
// 					while (buffer[data->i] && ((buffer[data->i] >= 'A' && buffer[data->i] <= 'Z') || buffer[data->i] == '_') && buffer[data->i] != DOUBLE_QUOTE)
// 					{
// 						data->i++;
// 						len++;
// 					}
// 					value_env = malloc(sizeof(char) * len + 1);
// 					if (!value_env)
// 						exit(58);
// 					pan = 0;
// 					while (pan < len)
// 						value_env[pan++] = buffer[pin++];
// 					value_env[pan] = '\0';
// 					value_env = ft_env_getstr_env_value(data->env, value_env);
// 					semi_final = ft_strjoin_parsing(semi_final, value_env);
// 					value_env = NULL;
// 					free(value_env);
// 				}
// 				printf("1 %s\n", semi_final);
// 				cmd = ft_buffercmd_in_lst_quotes(semi_final, cmd, data);
// 				semi_final = NULL;
// 				free(semi_final);
// 				ft_quotes_checker(data, buffer, data->i);
// 				printf("%c\n", buffer[data->i]);
// 			}
// /*						SI C'EST DES SIMPLE QUOTES							*/
// 			while (data->s_quotes_switch == 1)
// 			{
// 				if (buffer[data->i] == SIMPLE_QUOTE)
// 					data->i++;
// 				pin = data->i;
// 				len = 0;
// 				while (data->i < len_max && buffer[data->i] != SIMPLE_QUOTE)
// 				{
// 					len++;
// 					data->i++;
// 				}
// 				if (len != 0)
// 				{
// 					semi_final = malloc(sizeof(char) * len + 1);
// 					if (!semi_final)
// 						exit(57);
// 					pan = 0;
// 					while (pin < data->i)
// 						semi_final[pan++] = buffer[pin++];
// 					semi_final[pan] = '\0';
// 				}
// 				ft_quotes_checker(data, buffer, data->i);
// 				printf("2 %s\n", semi_final);
// 				cmd = ft_buffercmd_in_lst_quotes(semi_final, cmd, data);
// 				semi_final = NULL;
// 				free(semi_final);
// 				printf("%c\n", buffer[data->i]);
// 			}
		}
/*****************************************************************************/	
/* 									SI $									 */
/*****************************************************************************/
		if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0 && buffer[data->i] == '$')
		{
			pin = data->i;
			data->i++;
			while (buffer[data->i] && ((buffer[data->i] >= 'A' && buffer[data->i] <= 'Z') || buffer[data->i] == '_'))
			{
				data->i++;
				len++;
			}
			if (buffer[data->i] >= 33 && buffer[data->i] <= 126)
				data->i = pin;
			else
			{
				if (len != 0)
				{
					value_env = malloc(sizeof(char) * len + 1);
					if (!value_env)
						exit (37);
					pan = 0;
					pin++;
					while (pin < data->i)
						value_env[pan++] = buffer[pin++];
					value_env[pan] = '\0';
					value_env = ft_env_getstr_env_value(data->env, value_env); 
					semi_final = ft_strjoin_parsing(semi_final, value_env);
					value_env = NULL;
					free(value_env);
					printf("3 %s\n", semi_final);
					cmd = ft_buffercmd_in_lst(semi_final, cmd, data);
					semi_final = NULL;
					free(semi_final);
					ft_quotes_checker(data, buffer, data->i);
				}
				else
					; //TODO faire en sorte que ca prennet le $ en compte pour l'imprimer
			}
		}
		else if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0 && buffer[data->i] == '|')
		{
			
		}
		else if ((data->s_quotes_switch == 0 && data->d_quotes_switch == 0) && (buffer[data->i] == '<' || buffer[data->i] == '>'))
		{
			
		}
/*****************************************************************************/	
/* 									SI NORMAL								 */
/*****************************************************************************/
		else if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0)
		{
			pin = data->i;
			len = 0;
			while (buffer[data->i] >= 33 && buffer[data->i] <= 126 && buffer[data->i] != '$' && buffer[data->i] != '\'' && buffer[data->i] != '"')
			{
				printf("%c\n", buffer[data->i]);
				data->i++;
				len++;
			}
			if (len != 0)
			{
				semi_final = malloc(sizeof(char) * len + 1);
				if (!semi_final)
					return (0);
					pan = 0;
				while (pin < data->i)
				{
					semi_final[pan] = buffer[pin];
					pan++;
					pin++;
				}
				semi_final[pin] = '\0';
				printf("4 %s\n", semi_final);
				cmd = ft_buffercmd_in_lst(semi_final, cmd, data);
				semi_final = NULL;
				free(semi_final);
				ft_quotes_checker(data, buffer, data->i);	
			}
		}
		data->i++;	
	}
	return (cmd);
}