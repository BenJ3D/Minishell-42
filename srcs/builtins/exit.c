/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/29 22:52:42 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

static void	ft_exit_exit(void)
{
	// ft_putnbr_fd(errno, 2);
	rl_replace_line("exit", 0);
	// write(2, "exit\n", 6);
	exit(g_status % 255);
}

void	ft_exit(t_data *data)
{
	ft_free_all_minishell(data);
	ft_exit_exit();
}

/**
 * @brief ft qui free en plus des variable utiliser pour le prompt
 * 
 * @param data 
 */
void	ft_exit_child(t_data *data) // peut etre pas besoin avec exit
{
	//TODO:
	ft_free_all_minishell(data);
	exit(errno); //TODO: changer dans fork exec child ?
}

