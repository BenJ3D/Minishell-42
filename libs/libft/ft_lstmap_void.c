/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_void.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 16:16:33 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/28 17:30:09 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst_void	*ft_lstmap_void(t_lst_void *lst, void *(*f)(void *), void (*del)(void *))
{
	t_lst_void	*tmp1;
	t_lst_void	*tmp2;
	t_lst_void	*tmp3;

	if (!lst || !f)
		return (NULL);
	tmp1 = lst;
	tmp2 = ft_lstnew_void(f(lst->content));
	while (tmp1->next)
	{
		tmp3 = ft_lstnew_void(f(tmp1->next->content));
		if (!tmp2)
		{
			ft_lstclear_void(&tmp2, del);
			return (NULL);
		}
		ft_lstadd_back_void(&tmp2, tmp3);
		tmp1 = tmp1->next;
	}
	return (tmp2);
}
