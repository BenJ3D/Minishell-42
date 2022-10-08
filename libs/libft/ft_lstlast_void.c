/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_void.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:27:57 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/28 17:30:09 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_lst_void	*ft_lstlast_void(t_lst_void *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}
