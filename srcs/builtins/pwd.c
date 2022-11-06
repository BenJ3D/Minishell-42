/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/06 00:35:18 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_builtin_pwd(t_data *data)
{
	char	line[PATH_MAX];

	errno = 0;
	ft_bzero(line, PATH_MAX * sizeof(char));
	if (getcwd(line, PATH_MAX))
	{
		ft_putstr_fd(line, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		return (0);
	}
	g_status = errno;
	ft_err_display_line_error(data, "pwd", "No such file or directory");
	return (1);
}
