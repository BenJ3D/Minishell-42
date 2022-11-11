/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_error_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:14:49 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/11 19:56:35 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	free_the_birds(t_data	*data)
{
	while (data->cmdtoparse)
	{
		printf("%s\n", data->cmdtoparse->str);
		free(data->cmdtoparse->str);
		data->cmdtoparse = data->cmdtoparse->next;
	}
}
