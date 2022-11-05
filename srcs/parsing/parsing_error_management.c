/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error_management.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:14:49 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/05 17:20:19 by bducrocq         ###   ########.fr       */
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
	ft_putstr_fd("Syntax Error\n", STDERR_FILENO);
	free_the_birds(data);
}
