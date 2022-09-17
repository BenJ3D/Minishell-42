/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:09:35 by falonso           #+#    #+#             */
/*   Updated: 2022/09/17 18:05:02 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter_void(t_lst *lst, void (*f)(void *))
{
	t_lst	*lst1;

	if (!lst || !f)
		return ;
	lst1 = lst;
	while (lst1)
	{
		f(lst1->content);
		lst1 = lst1->next;
	}
}
