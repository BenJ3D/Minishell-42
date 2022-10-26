/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:14:49 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/26 11:47:01 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	free_the_birds(t_list	*cmd)
{
	while (cmd)
	{
		free(cmd->str);
		cmd = cmd->next;
	}
}

void	error_management(t_data	*data, char *buffer, t_list	*cmd)
{
	ft_putstr_fd("Syntax Error\n", 2);
	free_the_birds(cmd);
}
