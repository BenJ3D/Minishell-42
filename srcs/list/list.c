/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 02:43:41 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/17 19:01:34 by bducrocq         ###   ########.fr       */
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

void	ft_lstdisplay(t_list *lst)
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

void	ft_lstdisplay_color(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while(tmp)
	{
		ft_putstr(tmp->str);
		ft_putstr(RED);
		ft_putstr(" -> ");
		ft_putstr(NONE_COLOR);
		tmp = tmp->next;
	}
		ft_putstr("(null)");
		ft_putstr("\n");
}

void	ft_lstdelone(t_list *lst)
{
	if (!lst)
		return ;
	ft_bzero(lst->str, ft_strlen(lst->str));
	free(lst->str);
	free(lst);
}

void	ft_lstclear(t_list **lst)
{
	t_list	*tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			ft_lstdelone(*lst);
			(*lst) = tmp;
		}
	}
}