/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_api.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/05 01:42:01 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

/**
 * @brief add var to env with format key=value
 * 
 * @param env 
 * @param key 
 * @param value 
 * @return int 
 */
int	ft_builtin_export_api(t_envlst *env, char *key, char *value)
{
	t_envlst	*node;

	if (ft_env_check_if_key_is_valid(env, key))
	{
		node = ft_env_getenv_lst_value(env, key);
		free (node->value);
		node->value = ft_strdup(value);
		node->isenv = 1;
	}
	else
		ft_env_lstadd_back(&env, ft_env_lstnew(key, value, 1));
	return (0);
}
