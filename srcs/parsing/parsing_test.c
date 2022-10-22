/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:26:09 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/22 16:20:41 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

static t_list	*ft_redirect_me_now(t_data	*data, char	*buffer, t_list	*cmd)
{
	int	len;

	len = 0;
	printf("hey\n");
	if (buffer[data->i] == '>')
	{
		printf("are you kidding me\n");
		while (buffer[data->i] != '\0' && buffer[data->i] == '>')
		{
			len++;
			data->i++;
		}
		printf("surely you must be\n");
		if (len == 1)
			cmd = ft_buffercmd_in_lst(">", cmd, data);
		else if (len == 2)
			cmd = ft_buffercmd_in_lst(">>", cmd, data);
		else if (len > 2)
			return (NULL);
		printf("because you are supposed to work\n");
	}
	else if (buffer[data->i] == '<')
	{
		while (buffer[data->i] != '\0' && buffer[data->i] == '<')
		{
			len++;
			data->i++;			
		}
		if (len == 1)
			cmd = ft_buffercmd_in_lst("<", cmd, data);
		else if (len == 2)
			cmd = ft_buffercmd_in_lst("<<", cmd, data);
		else if (len > 2)
			return (NULL);
	}
	return (cmd);	
}

t_list	*ft_total_parsing(t_data	*data, char	*buffer)
{
	int	len_max;
	t_list	*cmd;
	int		pin;

	cmd = NULL;
	data->i = 0;
	len_max = ft_strlen_parsing(buffer);
	ft_reset_quotes_checker(data);
	while (buffer[data->i])
	{
		ft_quotes_checker(data, buffer, data->i);
		while (data->s_quotes_switch == 1 || data->d_quotes_switch == 1)
		{
			printf("test1\n");
			cmd = ft_quotes(data, buffer, cmd, len_max);
			printf("Test2\n");
		}
		if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0 && buffer[data->i] == '$')
			cmd = ft_parsing_env_variable(data, cmd, buffer);
		// else if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0 && buffer[data->i] == '|')
		// {
		// 	pin = data->i;
		// 	printf("Test1\n");
		// 	while (buffer[data->i] == '|')
		// 		data->i++;
		// 	printf("Test2\n");
		// 	printf("%i %i\n", data->i, pin);
		// 	if (data->i - pin > 1 || CMD == NULL)
		// 	{
		// 		printf("Syntax error\n");
		// 		return (NULL);
		// 	}
		// 	printf("Test3\n");
		// 	cmd = ft_buffercmd_in_lst("|", cmd, data);
		// }
		else if ((data->s_quotes_switch == 0 && data->d_quotes_switch == 0) && (buffer[data->i] == '<' || buffer[data->i] == '>'))
		{
			printf("ici\n");
			cmd = ft_redirect_me_now(data, buffer, cmd);
		}
		else if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0)
			cmd = ft_parsing_others(data, cmd, buffer);
		if (buffer[data->i] != '|' && buffer[data->i] && buffer[data->i] != '>' && buffer[data->i] != '<')
			data->i++;
	}
	return (cmd);
}