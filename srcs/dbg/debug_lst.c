/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 02:43:41 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/12 15:59:39 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	dbg_lstdisplay_color(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while(tmp)
	{
		ft_putstr(tmp->str);
		// ft_putstr("(");
		// ft_putnbr(tmp->type);
		// ft_putstr(")");
		ft_putstr(COLOR_RED);
		ft_putstr(" -> ");
		ft_putstr(COLOR_NONE);
		tmp = tmp->next;
	}
		ft_putstr("(null)");
		ft_putstr("\n");
}

void	dbg_lstdisplay_color_type(t_list *lst)
{
	t_list	*tmp;

	if (!lst)
		return ;
	tmp = lst;
	while(tmp)
	{
		ft_putstr(tmp->str);
		ft_putstr(COLOR_PURPLE);
		ft_putstr("(");
		ft_putnbr(tmp->type);
		ft_putstr(")");
		ft_putstr(COLOR_RED);
		ft_putstr(" -> ");
		ft_putstr(COLOR_NONE);
		tmp = tmp->next;
	}
		ft_putstr("(null)");
		ft_putstr("\n");
}

void	dbg_lstdisplay(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while(tmp)
	{
		ft_putstr(tmp->str);
		ft_putstr("\n");
		tmp = tmp->next;
	}
}
