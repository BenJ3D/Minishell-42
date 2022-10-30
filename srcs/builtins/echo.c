/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/30 22:52:53 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_builtin_echo(char **argv) //TODO: prendre en charge le flag n et ?? les '/" ??
{
	int	i;

	i = 1;
	while(argv[i])
	{
		// if (argv[i][0] == '$' && argv[i][1] == '?')
		// {
		// 	ft_putstr_fd("errno = ", 1);
		// 	ft_putnbr_fd((g_status % 255), 1);
		// 	ft_putstr_fd("\n", 1);
		// }
		// else
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putchar(' ');
		i++;
	}
	ft_putstr("(echo: WIP)"); //FIXME:
	ft_putchar('\n');
	return (0);
}