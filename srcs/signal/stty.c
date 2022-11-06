/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stty.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 23:26:11 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/06 23:27:34 by bducrocq         ###   ########.fr       */
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
int	ft_stty_control(int b)
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
	return (0);
}
