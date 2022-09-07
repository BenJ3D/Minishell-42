/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:33:28 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/07 20:04:15 by bducrocq         ###   ########.fr       */
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

char	**ft_env_convert_envlst_to_tab(t_envlst *env)
{
	int			i;
	char		**tab;
	t_envlst	*tmp;
	
	tmp = env;
	tab = ft_calloc(ft_env_lstsize(tmp) + 1, sizeof(tmp));
	i = 0;
	while (tmp)
	{
		tab[i] = ft_strjoin_max("%s=%s", tmp->key, tmp->value);
		tmp = tmp->next;
		i++;
	}
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