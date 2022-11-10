/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 23:26:11 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/10 15:17:15 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_signal_handler_interative(int signum)
{
	if (signum == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
		return ;
}

void	ft_signal_interactive_mode(void)
{
	struct sigaction	sa;
	struct sigaction	sa1;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = &ft_signal_handler_interative;
	ft_bzero(&sa1, sizeof(struct sigaction));
	sa1.sa_handler = SIG_IGN;
}
