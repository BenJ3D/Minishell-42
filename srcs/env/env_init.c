/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:21:26 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/12 19:14:44 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>

/**
 * @brief return name key without '='
 * 
 * @param str 
 * @return char* 
 */
char	*ft_env_extract_key_name(char *str)
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
		return (NULL);
	len = 0;
	while (str[len] != '=')
		len++;
	len++;
	tmp = ft_calloc(len, sizeof(tmp));
	i = 0;
	while (str[i] != '=')
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
	while (str[i] != '=')
		i++;
	i++;
	tmp = ft_calloc((ft_strlen(str) - i) + 1, sizeof(tmp));
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
 * @brief verifie sur USER existe, et sinon creer la variable USER=guest
 * //FIXME: ===>>> depend du comportement voulu pour notre minishell :
 * soit on ne met plus de login soit on le remplace par guest a voir
 * @param data 
 * @param tmp 
 * @param tkey 
 * @param tvalue 
 */
// static void	ft_env_init_lst_if_empty_env(t_data *data, t_envlst *tmp,
// 	char *tkey, char *tvalue)
// {
// 	tkey = ft_strdup("USER");
// 	tvalue = ft_strdup("guest");
// 	ft_env_lstadd_back(&tmp, ft_env_lstnew(tkey, tvalue));
// 	data->env = tmp;
// 	free(tkey);
// 	free(tvalue);
// }

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
		ft_env_lstadd_back(&tmp, ft_env_lstnew(tkey, tvalue));
		free(tkey);
		free(tvalue);
	}
	else
	{
		i = 0;
		while (envp[i])
		{
			tkey = ft_env_extract_key_name(envp[i]);
			tvalue = ft_env_extract_value_content(envp[i]);
			ft_env_lstadd_back(&tmp, ft_env_lstnew(tkey, tvalue));
			free(tkey);
			free(tvalue);
			i++;
		}
	}
	data->env = tmp;
}

//FIXME: verifier si return NULL pose pas de soucis, sinon ft_strdup("");
/**
 * @brief retourne la valeur d'env correspondant a key
 * 
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





////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////     ENV TEST     //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/**
 * @brief fonction test pour debug le split env
 * 
 * @param env
 * @param key
 * @return int
 */
int	env_test_read(char **env, const char *key)
{
	char *value;
	int i;
	int ret;

	ret = 0;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, ft_strlen(key)))
			break ;
		i++;
	}
	if (!env[i])
	{
		perror("Aucune variable environnement de ce nom");
		return (2);
	}
	value = ft_strdup(env[i]);
	i = 1;
	while(value[i - 1] != '=')
		i++;
	printf("env %s : %s\n", key, value + i);
	free(value);
	return (i);
}

