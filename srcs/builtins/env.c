/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/04 12:11:57 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	ft_builtin_env(t_envlst *envlst)
{
	t_envlst	*tmp;

	g_status = 0;
	tmp = envlst;
	while (tmp)
	{
		if (tmp->isenv == 1)
		{
			ft_putstr(tmp->key);
			ft_putstr("=");
			ft_putstr(tmp->value);
			ft_putstr("\n");
		}
		tmp = tmp->next;
	}
}
