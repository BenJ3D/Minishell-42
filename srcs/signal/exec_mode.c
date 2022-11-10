/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_mode.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:26:11 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/10 14:30:21 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_signal_exec_main(int signum)
{
	if (signum == SIGINT || signum == SIGQUIT)
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
}

void	ft_signal_exec_mode(void)
{
	struct sigaction	sa;
	struct sigaction	sa1;

	ft_bzero(&sa, sizeof(struct sigaction));
	ft_bzero(&sa1, sizeof(struct sigaction));
	sa.sa_handler = &ft_signal_exec_main;
	sa1.sa_handler = &ft_signal_exec_main;
}

void	ft_signal_exec_child_process(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = SIG_DFL;
}

void	ft_signal_ignore(void)
{
	struct sigaction	sa;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = SIG_IGN;
}
