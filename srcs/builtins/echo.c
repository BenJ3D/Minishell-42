/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/11 16:46:37 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_builtin_echo(char **argv) //TODO: prendre en charge le flag n et les '/"
{
	int	i;

	i = 1;
	while(argv[i])
	{
		ft_putstr(argv[i++]);
		ft_putchar(' ');
	}
	i = 1;
	while(argv[i])
	{
		ft_putstr(argv[i++]);
		ft_putchar(' ');
	}
	ft_putstr("(echo: WIP)");
	ft_putchar('\n');
	return (0);
}