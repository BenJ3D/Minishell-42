/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:08:38 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/06 20:04:36 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>

t_env	*ft_env_lstnew(char *key, char *value)
{
	t_env	*tmp;

	tmp = (t_env *)malloc(sizeof(*tmp));
	if (!tmp)
		return (NULL);
	tmp->key = key;
	tmp->value = value;
	tmp->next = NULL;
	return (tmp);
}

void	ft_env_lstadd_front(t_env **alst, t_env *new)
{
	new->next = *alst;
	*alst = new;
}

void	ft_env_lstadd_back(t_env **alst, t_env *new)
{
	t_env	*lst1;

	if (*alst == NULL)
		*alst = new;
	else if (alst != NULL && new != NULL)
	{
		lst1 = ft_env_lstlast(*alst);
		lst1->next = new;
	}
}

void	ft_env_lstdelone(t_env *lst)
{
	if (!lst)
		return ;
	ft_bzero(lst->key, ft_strlen(lst->key));
	ft_bzero(lst->value, ft_strlen(lst->value));
	free(lst->key);
	free(lst->value);
	free(lst);
}

void	ft_env_lstclear(t_env **lst)
{
	t_env	*tmp;

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

//TODO: max 5 ft
t_env	*ft_env_lstlast(t_env *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}