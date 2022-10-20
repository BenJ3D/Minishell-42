/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/21 01:15:22 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_builtin_echo(char **argv) //TODO: prendre en charge le flag n et les '/"
{
	int	i;

	i = 1;
	while(argv[i])
	{
		if (argv[i][0] == '$' && argv[i][1] == '?')
			ft_putnbr(errno);
		else
			ft_putstr(argv[i]);
		i++;
		ft_putchar(' ');
	}
	ft_putstr("(echo: WIP)");
	ft_putchar('\n');
	return (0);
}