/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:26:09 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/19 19:13:55 by hmarconn         ###   ########.fr       */
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
		while (data->s_quotes_switch == 1 || data->d_quotes_switch == 1)
			cmd = ft_quotes(data, buffer, cmd, len_max);
		if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0 && buffer[data->i] == '$')
			cmd = ft_parsing_env_variable(data, cmd, buffer);
		// else if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0 && buffer[data->i] == '|')
		// {
			
		// }
		// else if ((data->s_quotes_switch == 0 && data->d_quotes_switch == 0) && (buffer[data->i] == '<' || buffer[data->i] == '>'))
		// {
			
		// }
		else if (data->s_quotes_switch == 0 && data->d_quotes_switch == 0)
			cmd = ft_parsing_others(data, cmd, buffer);
		data->i++;	
	}
	return (cmd);
}