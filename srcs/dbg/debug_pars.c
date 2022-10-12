/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 02:43:41 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/12 16:14:31 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void dbg_display_cmdtab(t_cmdtab *cmdtab)
{
	int	i;

	i = 0;
	while (cmdtab[i].lst)
	{
		ft_putstr("cmdtab[");
		ft_putnbr(i);
		ft_putstr("] = ");
		dbg_lstdisplay_color_type(cmdtab[i].lst);
		i++;
	}
}

void dbg_display_argv(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		ft_putstr(COLOR_PURPLE);
		ft_putstr(argv[i]);
		ft_putstr(COLOR_RED);
		ft_putstr(" . ");
		i++;
	}
	ft_putstr(COLOR_NONE);
	ft_putstr("\n");
}
