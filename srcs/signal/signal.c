/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:26:11 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/10 13:56:40 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	signal_handler_not_blocking_cmd(int signum)
{
	(void)signum;
	ft_putstr("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_status = 1;
}

/*
	A blocking command (eg. cat) was executed 
	before these signals:
		ctrl + c (SIGINT)
		ctrl + \ (SIGQUIT)
*/
void	signal_handler_blocking_cmd(int signum)
{
	if (signum == SIGQUIT)
	{
		ft_putstr("Quit: 3\n");
		g_status = 131;
		errno = 131;
	}
	else if (signum == SIGINT)
	{
		ft_putstr("\n");
		g_status = 130;
		errno = 130;
	}
}

/*
    Execution of signal() function allows reception of specific \
	signals (first param) at any time during the running \
	of the loop it is placed in.

	When a signal is received, the function handler \
	(second param) is executed.

	Signal reception after empty or non empty prompt \
	but not after a blocking command was executed:
		ctrl + c (SIGINT)
		ctrl + \ (SIGQUIT)
*/
void	signal_recept_not_blocking_cmd(void)
{
	signal(SIGINT, signal_handler_not_blocking_cmd);
	signal(SIGQUIT, SIG_IGN);
}

/*
	Signal reception after a blocking command was executed:
		ctrl + c (SIGINT)
		ctrl + \ (SIGQUIT)
*/
void	signal_recept_blocking_cmd(void)
{
	signal(SIGINT, signal_handler_blocking_cmd);
	signal(SIGQUIT, signal_handler_blocking_cmd);
}
