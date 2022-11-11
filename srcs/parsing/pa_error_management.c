/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_error_management.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 18:14:49 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/11 20:14:07 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	free_the_birds(t_data	*data)
{
	t_list	*tmp;

	tmp = data->cmdtoparse;
	while (tmp)
	{
		free(tmp->str);
		tmp = tmp->next;
	}
	free(data->cmdtoparse);
}
