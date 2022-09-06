/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:33:28 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/07 00:25:06 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>

t_envlst	*ft_env_lstlast(t_envlst *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

void	ft_display_all_env_lst(t_envlst *envlst)
{
	t_envlst	*tmp;

	tmp = envlst;
	while (tmp)
	{
		ft_putstr(tmp->key);
		ft_putstr(tmp->value);
		ft_putstr("\n");
		tmp = tmp->next;
	}
}

char	**ft_create_tab_with_envlst(t_envlst *env)
{
	char	**tab;
	int		lstlen;

	lstlen = ft_env_lstsize(env);
	
	return (tab);
}

int		ft_env_lstsize(t_envlst *lst)
{
	t_envlst	*tmp;
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