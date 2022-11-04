/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:21:26 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/04 15:35:40 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	ft_env_init_lst_norm(char **envp, t_data *data)
{
	int			i;
	char		*tkey;
	char		*tvalue;	
	t_envlst	*tmp;

	tmp = NULL;
	tkey = NULL;
	tvalue = NULL;
	i = 0;
	while (envp[i])
	{
		tkey = ft_env_extract_key_name(envp[i], (int *)1);
		tvalue = ft_env_extract_value_content(envp[i]);
		ft_env_lstadd_back(&tmp, ft_env_lstnew(tkey, tvalue, 1));
		free(tkey);
		free(tvalue);
		i++;
	}
	data->env = tmp;
}

/**
 * @brief create copy of envp in list chained 
 * 
 * @param envp src env
 */
void	ft_env_init_lst(char **envp, t_data *data)
{
	int			i;
	char		*tkey;
	char		*tvalue;	
	t_envlst	*tmp;

	tmp = NULL;
	tkey = NULL;
	tvalue = NULL;
	if (!envp[0])
	{
		tkey = ft_strdup("PWD");
		tvalue = getcwd(NULL, PATH_MAX);
		ft_env_lstadd_back(&tmp, ft_env_lstnew(tkey, tvalue, 1));
		free(tkey);
		free(tvalue);
		data->env = tmp;
	}
	else
		ft_env_init_lst_norm(envp, data);
	ft_shlvl_increment(data->env);
}

/**
 * @brief retourne la valeur d'env en *str correspondant a "key"
 * return null if don't exist
 * @param env 
 * @param key 
 * @return char* 
 */
char	*ft_env_getstr_env_value(t_envlst *env, const char *key)
{
	char		*ret;
	t_envlst	*tmp;
	int			keylen;

	printf("key = %s\n", key);
	if (ft_strlen(key) < 2)
	{
		ret = ft_strdup("");
		if (!ret)
			return (NULL);
		return (ret);
	}
	// if (ft_strequal(tmp->key, key))
	tmp = env;
	while (tmp)
	{
		if (ft_strequal(tmp->key, key))
		{
			ret = ft_strdup(tmp->value);
			return (ret);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
