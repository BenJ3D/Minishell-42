/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/22 14:41:45 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>

void	ft_exit(t_data *data)
{
	ft_free_all_minishell(data);
}

void	ft_exit_child(t_data *data)
{
	ft_free_all_minishell(data);
	exit(0);
}
void	ft_exit_exit(t_data *data)
{
	ft_free_all_minishell(data);
	exit(0);
}
