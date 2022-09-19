/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 02:43:41 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/19 22:00:47 by bducrocq         ###   ########.fr       */
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
		ft_lstdisplay_color(cmdtab[i].lst);
		i++;
	}
}
