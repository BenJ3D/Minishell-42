/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 13:33:28 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/28 20:31:16 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

/**
 * @brief Recupere le maillot de t_envlst correspondant a key
 * return NULL si la key n'existe pas
 * @param env 
 * @param key 
 * @return t_envlst* 
 */
t_envlst	*ft_env_getenv_lst_value(t_envlst *env, char *key)
{
	t_envlst	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strequal(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}


/**
 * @brief Verifie si une clef (key) est deja presente ou non dans l'env
 * @param env 
 * @return int 
 */
int	ft_env_check_if_key_is_valid(t_envlst *env, char *key)
{
	t_envlst	*tmp;
	int			i;
	
	tmp = env;
	i = 0;
	while (tmp)
	{
		if (ft_strequal(tmp->key, key))
			return (TRUE);
		tmp = tmp->next;
		i++;
	}
	return (FALSE);
}

/**
 * @brief fait avancer la liste à son dernier maillon
 * 
 * @param lst 
 * @return t_envlst* 
 */
t_envlst	*ft_env_lstlast(t_envlst *lst)
{
	if (lst)
		while (lst->next)
			lst = lst->next;
	return (lst);
}

/**
 * @brief incremente la var env SHLVL a +1
 * 
 * @param env 
 * @return int 
 */
int	ft_shlvl_increment(t_envlst *env)
{
	t_envlst	*tmp;
	int			save;
	
	tmp = env;
	while (tmp)
	{
		if (ft_strequal(tmp->key, "SHLVL") == TRUE)
		{
			save = ft_atoi(tmp->value);
			free (tmp->value);
			tmp->value = ft_itoa(save + 1);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

/**
 * @brief retourne toutes les key=env sous forme tab**
 * Usage pour execve qui demande un **env param 
 * 
 * @param env 
 * @return char** 
 */
char	**ft_env_convert_envlst_to_tab(t_envlst *env)
{
	int			i;
	char		**tab;
	t_envlst	*tmp;
	
	tmp = env;
	tab = ft_calloc(ft_env_lstsize(tmp) + 1, sizeof(t_envlst));
	i = 0;
	while (tmp)
	{
		if (tmp->isenv == 1)
			tab[i] = ft_strjoin_max("%s=%s", tmp->key, tmp->value);
		tmp = tmp->next;
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
int		ft_env_lstsize(t_envlst *lst)
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

/**
 * @brief returne la taille de la liste env
 * 
 * @param lst 
 * @return int 
 */
int		ft_env_lstsize_export(t_envlst *lst)
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