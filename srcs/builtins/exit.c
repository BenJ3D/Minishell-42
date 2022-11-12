/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/12 19:10:38 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit_exit(t_data *data)
{
	ft_free_all_minishell(data);
	rl_replace_line("exit", 0);
	exit(g_status % 255);
}

static void	ft_exit_arg(int exitarg, t_data *data)
{
	ft_free_all_minishell(data);
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

void	ft_exit_normal(t_data *data, char **argv)
{
	ft_stty_control(1);
	if (argv[0] && argv[1])
		ft_exit_arg(ft_atoi(argv[1]), data);
	else
		ft_exit_exit(data);
}
