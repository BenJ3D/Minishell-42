/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/05 17:19:12 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_builtin_pwd(t_envlst *env, char **argv)
{
	char	*line;

	env = NULL;
	argv = NULL;
	g_status = 0;
	line = getcwd(NULL, PATH_MAX);
	ft_putstr_fd(line, STDOUT_FILENO);
	free(line);
	return (0);
}
