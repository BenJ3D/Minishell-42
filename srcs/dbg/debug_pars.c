/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 02:43:41 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/20 00:47:18 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>

void dbg_display_cmdtab(int pipe, t_cmdtab *cmdtab)
{
	int	i;

	i = 0;
	while (i <= pipe)
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
		ft_putstr(PURPLE);
		ft_putstr(argv[i]);
		ft_putstr(RED);
		ft_putstr(" . ");
		i++;
	}
	ft_putstr(NONE_COLOR);
	ft_putstr("\n");
}
