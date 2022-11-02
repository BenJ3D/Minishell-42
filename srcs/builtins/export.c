/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/02 20:27:06 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"
static int	ft_check_if_key_is_valid(char *str, t_data *data);
static int	ft_main_export(t_envlst *env, char *str, t_data *data);
static void	ft_print_export(t_envlst *env);

//TODO: faire le parsing avec rules ( doit commencer par une lettre ou _ et 
														 //que des alphanumeric)
/**
 * @brief Fonction mère à appeler, TODO: parsing a faire
 * 
 * @param env 
 * @param cmd 
 * @return int 
 */
int	ft_builtin_export(t_envlst *env, char **cmd, t_data *data)
{
	int	i;
	
	if (!cmd[1] || cmd[1][0] == '\0')
		ft_print_export(env);
	else
	{
		i = 1;
		while (cmd[i])
			ft_main_export(env, cmd[i++], data);
	}
	return (0);
}


char	**ft_env_get_envtab(t_envlst *env) //FIXME: move to env file
{
	char		**tab;
	t_envlst	*tmp;
	int			i;
	
	if (!env)
		return (NULL);
	tmp = env;
	tab = ft_calloc(ft_env_lstsize_export(env) + 1, sizeof(char **));
	i = 0;
	while(tmp)
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

char	**ft_env_return_envlst_sorted_in_tab(t_envlst *env) //FIXME: move to env file
{
	char	**tab;
	char	*tmp;
	char	*cmp1;
	char	*cmp2;
	int		i;
	int		tabsize;

	i = 0;
	tab = ft_env_get_envtab(env);
	tabsize = ft_env_lstsize(env);
	while(tab[i + 1])
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
 * @brief function print export
 * 
 * @param env 
 */
static void	ft_print_export(t_envlst *env) //V2 sorted
{
	char		**tab;
	int			i;
	
	tab = ft_env_return_envlst_sorted_in_tab(env);
	i = 0;
	while (tab[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tab[i], 1);
		ft_putchar_fd('\n', 1);
		i++;
	}
}

/**
 * @brief vérifie si la key est NULL //TODO: doit tchecker le normage des key env
 * 
 * @param key 
 * @return int 
 */
int	ft_check_if_exportkey_is_valid(char *key, t_data *data)
{
	int	i;
	
	if (key == NULL)
		return (1);
	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (1);
	i++;
	while(key[i])
	{
		if (!ft_isalnum(key[i]))
			return (1);
		i++;
	}
	return (0);
}


/**
 * @brief add var to env with format key=value
 * 
 * @param env 
 * @param str name of futur key
 * @return int 
 */
static int	ft_main_export(t_envlst *env, char *str, t_data *data)//TODO: norm errno doit renvoyer 1
{
	char		*key;
	char		*value;
	int			isenv;
	t_envlst	*node;
	char		*errline;
	
	isenv = TRUE;
	key = ft_env_extract_key_name(str, &isenv);
	if (ft_check_if_exportkey_is_valid(key, data))
	{
		errline = ft_strjoin_max("%s%s: %s`%s': %snot a valid identifier%s\n",
				COLOR_CYAN, data->pgr_name, COLOR_PURPLE, 
				str, COLOR_RED, COLOR_NONE);
		ft_putstr_fd(errline, 2);
		g_status = 1;
		errno = 1;
		free (errline);
		return (1);
	}
	if (ft_env_check_if_key_is_valid(env, key) == TRUE)  //tcheck si une clef existe deja
	{
		node = ft_env_getenv_lst_value(env, key);
		if (isenv == TRUE)
		{
			free(node->value);
			value = ft_env_extract_value_content(str);
			node->value = ft_strdup(value);
			node->isenv = isenv;
			free (value);
		}
	}
	else
	{
		if (isenv == TRUE)
			value = ft_env_extract_value_content(str);
		else
			value = ft_strdup("");
		ft_env_lstadd_back(&env, ft_env_lstnew(key, value, isenv));
		free (value);
	}
	free (key);
	return (0);
}

