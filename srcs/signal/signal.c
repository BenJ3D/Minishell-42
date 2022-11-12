/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:26:11 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/12 19:10:38 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	signal_handler_not_blocking_heredoc(int signum)
{
	(void)signum;
	ft_putstr_fd("\n", 1);
	exit (1);
}

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
	if (signum == SIGQUIT && isatty(1))
		ft_putstr("Quit: 3\n");
	else if (signum == SIGINT)
		ft_putstr("\n");
}

/**
 * @brief ctrl + c (SIGINT)
 *		ctrl + \ (SIGQUIT)
 * 
 */
void	signal_recept_not_blocking(int mode)
{
	if (mode == 1)
	{
		signal(SIGINT, signal_handler_not_blocking_cmd);
		signal(SIGQUIT, SIG_IGN);
	}
	else
	{
		signal(SIGINT, signal_handler_not_blocking_heredoc);
		signal(SIGQUIT, SIG_IGN);
	}
}

/*
	Signal reception after a blocking command :
		ctrl + c (SIGINT)
		ctrl + \ (SIGQUIT)
*/
void	signal_recept_blocking_cmd(void)
{
	signal(SIGINT, signal_handler_blocking_cmd);
	signal(SIGQUIT, signal_handler_blocking_cmd);
}
