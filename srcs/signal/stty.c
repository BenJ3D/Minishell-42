/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stty.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:26:11 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/09 20:11:23 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

/**
 * @brief masquer le ^C ou de le restaurer
 * 
 * @param envp 
 * @param b  0 pour masquer / 1 ou != 0 pour restaurer
 * @return int 
 */
int	ft_stty_control(int b, t_data *data)
{
	pid_t	father;

	father = fork();
	if (father == 0)
	{
		if (b == 0)
		{
			execve("/bin/stty", (char *[]){"stty", "-ctlecho", NULL}, NULL);
			perror("stty");
		}
		else
		{
			execve("/bin/stty", (char *[]){"stty", "sane", NULL}, NULL);
			perror("stty");
		}
		exit (errno);
	}
	waitpid(father, &g_status, 0);
	return (0);
}

/**
 * @brief pour contrer un appel ./minishell | ./minishell
 * 
 * @return int 
 */
int	ft_issaty_control(void)
{
	pid_t	father;

	g_status = 0;
	father = fork();
	if (father == 0)
	{
		if (!isatty(1))
			exit(1);
		exit(0);
	}
	waitpid(father, &g_status, 0);
	if ((g_status % 255) != 0)
		exit (1);
	return (0);
}
