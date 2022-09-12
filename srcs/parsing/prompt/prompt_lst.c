// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   prompt_lst.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/09/12 22:03:38 by bducrocq          #+#    #+#             */
// /*   Updated: 2022/09/12 23:34:41 by bducrocq         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include <./../includes/minishell.h>

// t_cmdlst	*ft_env_lstnew(char *key, char *value)
// {
// 	t_cmdlst	*tmp;

// 	tmp = (t_cmdlst *)malloc(sizeof(*tmp));
// 	if (!tmp)
// 		return (NULL);
// 	tmp->next = NULL;
// 	return (tmp);
// }

// void	ft_env_lstadd_front(t_cmdlst **alst, t_cmdlst *new)
// {
// 	new->next = *alst;
// 	*alst = new;
// }

// void	ft_env_lstadd_back(t_cmdlst **alst, t_cmdlst *new)
// {
// 	t_cmdlst	*lst1;

// 	if (*alst == NULL)
// 		*alst = new;
// 	else if (alst != NULL && new != NULL)
// 	{
// 		lst1 = ft_env_lstlast(*alst);
// 		lst1->next = new;
// 	}
// }

// void	ft_env_lstdelone(t_cmdlst *lst)
// {
// 	if (!lst)
// 		return ;
// 	ft_bzero(lst->key, ft_strlen(lst->key));
// 	ft_bzero(lst->value, ft_strlen(lst->value));
// 	free(lst->key);
// 	free(lst->value);
// 	free(lst);
// }

// void	ft_env_lstclear_one(t_cmdlst **lst)
// {
// 	t_cmdlst	*tmp;
// 	t_cmdlst	*tmp2;

// 	if (lst)
// 	{
	
// 		tmp = (*lst);
// 		tmp2 = (*lst)->next->next;
// 		(*lst) = (*lst)->next;
// 		ft_env_lstdelone(*lst);
// 		(*lst) = tmp;
// 		(*lst)->next = tmp2;
// 	}
// }

// void	ft_env_lstclear(t_cmdlst **lst)
// {
// 	t_cmdlst	*tmp;

// 	if (lst)
// 	{
// 		while (*lst)
// 		{
// 			tmp = (*lst)->next;
// 			ft_env_lstdelone(*lst);
// 			(*lst) = tmp;
// 		}
// 	}
// }
