/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 17:08:38 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/12 19:10:38 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_envlst	*ft_env_lstnew(char *key, char *value, int isenv)
{
	t_envlst	*tmp;

	tmp = (t_envlst *)ft_calloc(sizeof(t_envlst), 1);
	if (!tmp)
		return (NULL);
	tmp->key = ft_strdup(key);
	tmp->value = ft_strdup(value);
	tmp->isenv = isenv;
	tmp->next = NULL;
	return (tmp);
}

void	ft_env_lstadd_front(t_envlst **alst, t_envlst *new)
{
	new->next = *alst;
	*alst = new;
}

void	ft_env_lstadd_back(t_envlst **alst, t_envlst *new)
{
	t_envlst	*lst1;

	if (*alst == NULL)
		*alst = new;
	else if (alst != NULL && new != NULL)
	{
		lst1 = ft_env_lstlast(*alst);
		lst1->next = new;
	}
}

void	ft_env_lstdelone(t_envlst *lst)
{
	if (!lst)
		return ;
	ft_bzero(lst->key, ft_strlen(lst->key));
	ft_bzero(lst->value, ft_strlen(lst->value));
	free(lst->key);
	free(lst->value);
	free(lst);
}

void	ft_env_lstclear_one(t_envlst **lst)
{
	t_envlst	*tmp;
	t_envlst	*tmp2;

	if (lst)
	{
		tmp = (*lst);
		tmp2 = (*lst)->next->next;
		(*lst) = (*lst)->next;
		ft_env_lstdelone(*lst);
		(*lst) = tmp;
		(*lst)->next = tmp2;
	}
}
