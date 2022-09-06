/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:21:26 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/06 22:17:22 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>

char	*ft_env_extract_key_name(char *str)
{
	int		i;
	int		len;
	char	*tmp;

	if (str[0] == '\0')
		return (NULL);
	len = 0;
	while (str[len] != '=')
		len++;
	len++;
	tmp = ft_calloc(len + 1, sizeof(tmp));
	i = 0;
	while (str[i] != '=')
	{
		tmp[i] =  str[i];
		i++;
	}
	tmp[i++] = '=';
	tmp[i] = '\0';
	return (tmp);
}

char	*ft_env_extract_value_content(char *str)
{
	int		i;
	int		y;
	char	*tmp;

	if (str[i] == '\0')
		return (NULL);
	i = 0;
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

	if (!envp)
		return ;
	tmp = NULL;
	tkey = NULL;
	tvalue = NULL;
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
	data->env = tmp;
}

/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
///////////////     WITH ENVP TO ENV **CHAR TAB    //////////////////
/////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////
//TODO: init env avec struc env pour key et value en chained ou tab**

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

int	ft_env_count_keys(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

/**
 * @brief init env if tab **env
 * 
 * @param envp 
 * @return char** 
 */
char	**ft_env_init(char **envp)
{
	char **env;
	int i;

	env = ft_calloc(sizeof(char **), ft_env_count_keys(envp) + 1);
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
	{	
		env[i] = ft_strdup(envp[i]);
		i++;
	}
	return (env);
}

void	ft_free_all_array(char **env)
{
	int	i;

	i = 0;
	while(env[i])
	{

		free (env[i]);
		i++;
		printf("free i = %i\n", i);
	}
	env = NULL;
	free (env);
}