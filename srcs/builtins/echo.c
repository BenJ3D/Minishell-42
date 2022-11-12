/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/12 19:10:38 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_builtin_echo_check_option(char *str)
{
	int	iter;

	iter = 0;
	if (!str)
		return (0);
	if (str[iter] == '-' && str[iter + 1] == 'n')
	{
		iter += 1;
		while (!ft_isspace(str[iter]) && str[iter])
		{
			if (str[iter] != 'n')
				return (0);
			iter += 1;
		}
		return (1);
	}
	return (0);
}

static int	ft_builtin_echo_norm(char **argv, int i, int previsop, int option)
{
	while (argv[i])
	{
		if (!ft_builtin_echo_check_option(argv[i]))
		{
			ft_putstr_fd(argv[i], STDOUT_FILENO);
			previsop = 0;
			if (argv[i + 1])
				ft_putchar(' ');
		}
		else if (ft_builtin_echo_check_option(argv[i]) && previsop == 0)
		{
			ft_putstr_fd(argv[i], STDOUT_FILENO);
			if (argv[i + 1])
				ft_putchar(' ');
		}
		else
			previsop = 1;
		i++;
	}
	if (option == 0)
		ft_putchar('\n');
	return (0);
}

int	ft_builtin_echo(char **argv)
{
	int	i;
	int	option;
	int	previsop;

	i = 1;
	option = ft_builtin_echo_check_option(argv[i]);
	if (option == 0)
	{
		previsop = 0;
		i = 1;
	}
	else
	{
		previsop = 1;
		i = 2;
	}
	g_status = 0;
	ft_builtin_echo_norm(argv, i, previsop, option);
	return (0);
}
