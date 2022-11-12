/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/12 20:53:42 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_exit_exit(t_data *data)
{
	ft_free_all_minishell(data);
	rl_replace_line("exit", 0);
	exit(g_status % 255);
}

void	ft_exit_arg(int exitarg, t_data *data)
{
	ft_free_all_minishell(data);
	rl_replace_line("exit", 0);
	exit(exitarg);
}

int	ft_check_if_has_no_digit(char *str)
{
	int	i;

	i = 0;
	if (!ft_isdigit(str[i]))
		return (1);
	return (0);
}

void	ft_exit_built(t_data *data, char **argv)
{
	if (argv[1] && ft_check_if_has_no_digit(argv[1]))
	{
		ft_err_display_line_error(data, "exit", "numeric argument required");
		g_status = 2;
	}
	else if (argv[0] && argv[1])
		ft_exit_arg(ft_atoi(argv[1]), data);
	else
		ft_exit_exit(data);
}

void	ft_exit(t_data *data, char **argv)
{
	if (argv[0] && argv[1])
		ft_exit_arg(ft_atoi(argv[1]), data);
	else
		ft_exit_exit(data);
}
