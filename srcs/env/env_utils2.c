/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:33:28 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/12 19:10:38 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_env_get_envtab(t_envlst *env)
{
	char		**tab;
	t_envlst	*tmp;
	int			i;

	if (!env)
		return (NULL);
	tmp = env;
	tab = ft_calloc(ft_env_lstsize_export(env) + 1, sizeof(char **));
	i = 0;
	while (tmp)
	{
		if (tmp->isenv == 1)
			tab[i] = ft_strjoin_max("%s=\"%s\"", tmp->key, tmp->value);
		else
			tab[i] = ft_strdup(tmp->key);
		tmp = tmp->next;
		i++;
	}
	return (tab);
}

char	**ft_env_return_envlst_sorted_in_tab(t_envlst *env, int i)
{
	char	**tab;
	char	*tmp;
	char	*cmp1;
	char	*cmp2;
	int		tabsize;

	tab = ft_env_get_envtab(env);
	tabsize = ft_env_lstsize(env);
	while (tab[i + 1])
	{
		cmp1 = ft_env_extract_key(tab[i]);
		cmp2 = ft_env_extract_key(tab[i + 1]);
		if (ft_strcmp(cmp1, cmp2) > 0)
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			tmp = NULL;
			i = -1;
		}
		free(cmp1);
		free(cmp2);
		i++;
	}
	return (tab);
}

/**
 * @brief returne la taille de la liste env
 * 
 * @param lst 
 * @return int 
 */
int	ft_env_lstsize_export(t_envlst *lst)
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

/**
 * @brief returne la taille de la liste env
 * 
 * @param lst 
 * @return int 
 */
int	ft_env_lstsize(t_envlst *lst)
{
	t_envlst	*tmp;
	int			i;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		if (tmp->isenv == 1)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
