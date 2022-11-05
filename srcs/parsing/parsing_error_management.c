/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_management.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:14:49 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/03 18:26:24 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	free_the_birds(t_data	*data)
{
	while (data->cmdtoparse)
	{
		free(data->cmdtoparse->str);
		data->cmdtoparse = data->cmdtoparse->next;
	}
}

void	error_management(t_data	*data)
{
	printf("%d\n", data->scroller);
	ft_putstr_fd("Syntax Error\n", 2);
	free_the_birds(data);
}
