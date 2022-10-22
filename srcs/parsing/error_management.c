/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:14:49 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/22 19:07:32 by hmarconn         ###   ########.fr       */
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
	printf("Syntax Error\n");
	free_the_birds(cmd);
}
