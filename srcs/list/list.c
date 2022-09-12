/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 02:43:41 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/12 23:44:09 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*lst1;

	if (*alst == NULL)
		*alst = new;
	else if (alst != NULL && new != NULL)
	{
		lst1 = ft_lstlast(*alst);
		lst1->next = new;
	}
}

t_list	*ft_lstnew(char *str)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (!tmp)
		return (NULL);
	tmp->str = ft_strdup(str);
	tmp->next = NULL;
	return (tmp);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

int		ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	int			i;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}