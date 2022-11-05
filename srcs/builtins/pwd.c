/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/04 21:58:33 by bducrocq         ###   ########.fr       */
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
	ft_putstr(line);
	ft_putstr_fd(" BUILTIN WIP\n", 2);
	free(line);
	return (0);
}
