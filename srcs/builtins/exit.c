/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/02 21:32:50 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

static void	ft_exit_exit(t_data *data)
{
	ft_free_all_minishell(data);
	rl_replace_line("exit", 0);
	// ft_putnbr_fd(g_status % 255, 2);
	// ft_putstr_fd(" is g_status  time to exit 1\n", 2);
	exit(g_status % 255);
}

static void	ft_exit_arg(int exitarg, t_data *data)
{
	ft_free_all_minishell(data);
	ft_putstr_fd("time to exit 2\n", 2);
	rl_replace_line("exit", 0);
	exit(exitarg);
}

void	ft_exit(t_data *data, char **argv)
{
	if (argv[0] && argv[1])
		ft_exit_arg(ft_atoi(argv[1]), data);
	else
		ft_exit_exit(data);
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

