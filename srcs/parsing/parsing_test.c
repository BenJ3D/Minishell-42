/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:26:09 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/18 12:12:06 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

static char	*ft_strjoin_parsing(char	*s1, char *s2)
{
	int		len;
	int		b;
	int		a;
	char	*s3;

	len = 0;
	b = 0;
	a = 0;
	len = ft_strlen((const char *)s1) + ft_strlen((const char *)s2);
	s3 = malloc(sizeof(char) * len + 1);
	if (!s3)
		return (NULL);
	while (s1 && s1[b] != '\0')
	{
			s3[b] = s1[b];
			b++;
	}
	while (s2 && s2[a] != '\0')
	{
			s3[b++] = s2[a];
			a++;
	}
	s3[b] = '\0';
	free (s1);
	return (s3);
}

int	ft_strlen_parsing(char	*str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);	
}

static t_list	*ft_split_buffercmd_in_lst(char *buffer, int bufi)
{
	int		i;
	int		len;
	char	*str;
	t_list *cmd;
	
	cmd = NULL;
	while (buffer[bufi])
	{
		while(ft_isspace(buffer[bufi]) && buffer[bufi] && buffer[bufi] != '|')
			bufi = bufi + 1;
		if (buffer[bufi] == '\0')
			return (cmd);
		len = ft_strlen_next_word(buffer + bufi);
		str = ft_calloc(len + 1, sizeof(char));
		if (!str)
			return (NULL);
		i = 0;
		while(len-- > 0)
			str[i++] = buffer[bufi++];
		ft_lstadd_back(&cmd, ft_lstnew(str));
		free(str);
	}
	return (cmd);
}

int	ft_total_parsing(t_data	*data, char	*buffer)
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
	printf("%s\n", buffer);
	semi_final = NULL;
	ft_reset_quotes_checker(data);
	while (buffer[i])
	{
		ft_quotes_checker(data, buffer, i);
		str = NULL;
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
					printf("%s\n", semi_final);
				}
				if (buffer[i] == '$')
				{
					len = 0;
					i++;
					pin = i;
					printf("%c\n", buffer[i]);
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
					printf("%s\n", value_env);
					value_env = ft_env_getstr_env_value(data->env, value_env);
					printf("%s\n", value_env);
					semi_final = ft_strjoin_parsing(semi_final, value_env);
					printf("%s\n", semi_final);
					free(value_env);
				}
				//TODO ranger dans la liste chainée
				cmd = ft_buffercmd_in_lst(semi_final, cmd, data);
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
					printf("%s\n", semi_final);
					//TODO ranger dans la liste chainée
				}
				ft_quotes_checker(data, buffer, i);
				free(semi_final);
				i++;
			}
		}
/*****************************************************************************/	
/* 									SI $									 */
/*****************************************************************************/
		if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0 && buffer[i] == '$')
		{
			printf("ici\n");
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
				printf("%s\n", semi_final);
				free(value_env);
				//TODO ranger dans la liste chainée
				cmd = ft_buffercmd_in_lst(semi_final, cmd, data);
				free(semi_final);
				ft_quotes_checker(data, buffer, i);
			}
		}
/*****************************************************************************/	
/* 									SI NORMAL								 */
/*****************************************************************************/
		else if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0)
		{
			pin = i;
			len = 0;
			while (buffer[i] >= 33 && buffer[i] <= 126 && buffer[i] != '$' && buffer[i] != '\'' && buffer[i] != '"')
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
			printf("%s\n", semi_final);
			//TODO ranger dans la liste chainée
			cmd = ft_buffercmd_in_lst(semi_final, cmd, data);
			free(semi_final);
			ft_quotes_checker(data, buffer, i);
		}
	}		
	return (0);
}