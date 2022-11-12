/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:32:10 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/12 19:10:38 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_check_if_cmd_has_a_backslash(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '/')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	ft_command_not_found_message(char **argv, t_data *data)
{
	if (argv[0] != NULL)
	{
		if (ft_check_if_cmd_has_a_backslash(argv[0]))
		{
			ft_err_display_line_error(data, argv[0], \
												"No such file or directory");
			g_status = 127;
		}
		else
		{
			ft_err_display_line_error(data, argv[0], "command not found");
			g_status = 127;
		}
	}
	else
		return (0);
	return (127);
}

int	ft_parent_waitpid(t_cmdtab *cmdtab)
{
	int	i;

	i = 0;
	while (cmdtab[i].lst)
	{
		if (cmdtab[i].pipeout == 1)
			close(cmdtab[i].fd[0]);
		waitpid(cmdtab[i].pid, &g_status, 0);
		if (WIFSIGNALED(g_status))
		{
			if (g_status == 2)
				g_status = 130;
			else
				g_status = 131;
		}
		i++;
	}
	return (0);
}
