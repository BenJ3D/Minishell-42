/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 02:43:41 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/11 03:20:48 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>

int	ft_parsing_prompt(t_data data, char *buffer)
{
	char **cmd;
	
	cmd = ft_split(buffer, ' ');
	for(int i = 0;  cmd[i]; i++)
	{
		ft_putstr(cmd[i]);
		ft_putstr(" --\n");
	}
	
	return (0);
}

