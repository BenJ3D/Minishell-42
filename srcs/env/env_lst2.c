/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:08:38 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/12 19:10:38 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env_lstclear_one_first_element(t_envlst **lst)
{
	t_envlst	*tmp;

	if (lst && *lst)
	{
		tmp = (*lst)->next;
		ft_env_lstdelone(*lst);
		(*lst) = tmp;
	}
}

void	ft_env_lstclear(t_envlst **lst)
{
	t_envlst	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			ft_env_lstdelone(*lst);
			(*lst) = tmp;
		}
	}
}
