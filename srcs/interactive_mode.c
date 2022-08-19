/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactve_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:26:11 by aartiges          #+#    #+#             */
/*   Updated: 2022/08/19 12:09:18 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>
#include <readline/history.h>

void	handler_interative(int signum)
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

void	interactive_mode(void)
{
	struct sigaction	sa;
	struct sigaction	sa1;

	ft_bzero(&sa, sizeof(struct sigaction));
	sa.sa_handler = &handler_interative;
	ft_bzero(&sa1, sizeof(struct sigaction));
	sa1.sa_handler = SIG_IGN;
	if (sigaction(SIGINT, &sa, NULL) == -1
		|| sigaction(SIGQUIT, &sa1, NULL) == -1)
		ft_putstr_fd("Error sigaction\n", 2);
}
