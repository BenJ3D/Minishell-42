/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 14:34:55 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/17 18:05:35 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back_void(t_lst **alst, t_lst *new)
{
	t_lst	*lst1;

	if (*alst == NULL)
		*alst = new;
	else if (alst != NULL && new != NULL)
	{
		lst1 = ft_lstlast_void(*alst);
		lst1->next = new;
	}
}
