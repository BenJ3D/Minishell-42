/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:32:10 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/12 13:34:05 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void dbg_fork_display_pid(const char *str) //TODO: getpid interdit, a virer avant push project
{
	printf("%spid = %i\n", str, getpid());
}


void dbg_display_errno(void)
{
	printf("pid = %i || debug errno = %i\n", getpid(), errno);
}