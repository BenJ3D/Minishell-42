/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:21:26 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/28 22:11:23 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

/**
 * @brief return name key without '='
 * 
 * @param str 
 * @return char* 
 */
char	*ft_env_extract_key_name(char *str, int *isenv) //TODO: norme
{
	int		i;
	int		len;
	char	*tmp;
 
	i = 1;
	len = 0;
	while (str[i])
		if (str[i++] == '=')
			len++;
	if (len == 0)
	{
		*isenv = FALSE;
		tmp = ft_strdup(str);
		return (tmp);
	}
	len = 0;
	while (str[len] != '=' && str[len])
		len++;
	len++;//TODO: verifier si np si str[len]=='\0'
	tmp = ft_calloc(len, sizeof(char));
	i = 0;
	while (str[i] != '=' && str[i])
	{
		tmp[i] =  str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

/**
 * @brief pour triage export (ne set pas isenv comme ft_env_extract_key_name)
 * 
 * @param str 
 * @return char* 
 */
char	*ft_env_extract_key(char *str)
{
	int		i;
	int		len;
	char	*tmp;
 
	i = 1;
	len = 0;
	while (str[i])
		if (str[i++] == '=')
			len++;
	if (len == 0)
	{
		tmp = ft_strdup(str);
		return (tmp);
	}
	len = 0;
	while (str[len] != '=' && str[len])
		len++;
	len++;
	tmp = ft_calloc(len, sizeof(char));
	i = 0;
	while (str[i] != '=' && str[i])
	{
		tmp[i] =  str[i];
		i++;
	}
	tmp[i] = '\0';
	return (tmp);
}

/**
 * @brief return content value after '=' key env
 * 
 * @param str 
 * @return char* 
 */
char	*ft_env_extract_value_content(char *str)
{
	int		i;
	int		y;
	char	*tmp;

	i = 0;
	if (str[i] == '\0')
		return (NULL);
	while (str[i] != '=' && str[i])
		i++;
	if (str[i] == '\0')
		return (ft_strdup(""));
	i++;
	tmp = ft_calloc((ft_strlen(str) - i) + 1, sizeof(char));
	y = 0;
	while (str[i])
	{
		tmp[y] =  str[i];
		i++;
		y++;
	}
	tmp[y] = '\0';
	return (tmp);
}

/**
 * @brief create copy of envp in list chained 
 * 
 * @param envp src env
 */
void	ft_env_init_lst(char **envp, t_data *data)
{
	int		i;
	char	*tkey;
	char	*tvalue;	
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
	}
	else
	{
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
	}
	data->env = tmp;
	ft_shlvl_increment(data->env);
}

//FIXME: verifier si return NULL pose pas de soucis, sinon ft_strdup("");
/**
 * @brief retourne la valeur d'env en *str correspondant a "key"
 * return null if don't exist
 * @param env 
 * @param key 
 * @return char* 
 */
char	*ft_env_getstr_env_value(t_envlst *env, const char *key)
{
	char 		*ret;
	t_envlst	*tmp;
	int			keylen;

	if (ft_strlen(key) < 2)
	{
		ret = ft_strdup("");
		if (!ret)
			return (NULL);
		return (ret);
	}
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
