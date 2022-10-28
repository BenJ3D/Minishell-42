/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/28 18:55:40 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"
static int	ft_check_if_null(char *str, t_data *data);
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
	tab = ft_calloc(ft_env_lstsize(env) + 1, sizeof(char **));
	i = 0;
	while(tmp)
	{
		tab[i] = ft_strjoin_max("%s=%s", tmp->key, tmp->value);
		tmp = tmp->next;
		i++;
	}
	return (tab);
}

char	**ft_env_return_envlst_sorted_in_tab(t_envlst *env) //FIXME: move to env file
{
	char	**tab;
	char	*tmp;
	int		i;

	i = 0;
	tab = ft_env_get_envtab(env);
	while(tab[i])
	{
		if (ft_strncmp(tab[i], tab[i + 1], ft_strlen(tab[i])) > 0)
		{
			tmp = ft_strdup(tab[i]);
			free (tab[i]);
			tab[i] = ft_strdup(tab[i + 1]);
			free (tab[i +1 ]);
			tab[i + 1] = ft_strdup(tmp);
			free (tmp);
			i = -1;
		}
		i++;
	}
	return (tab);
}
// void	ft_sort_envlst_by_allocation_number(t_envlst *env)
// {
// 	t_envlst	*tmp;
// 	char		*tocmp;
// 	char		*winner;
// 	int			sizecmp;
// 	int			sizelst;
// 	int			count;

// 	if (!env)
// 		return ;
// 	tmp = env;
// 	winner = NULL;
// 	sizelst = ft_env_lstsize(env);
// 	count = 0;
// 	while (tmp)
// 	{
// 		tmp->alphaorder = 0;
// 		tmp = tmp->next;
// 	}
// 	tmp = env;
// 	tocmp = ft_strdup(tmp->key); //prendre le premier element
// 	while (tmp)
// 	{
// 		if (!(tocmp == NULL))
// 			free (tocmp);
// 		sizecmp = ft_strlen(tocmp);
// 		if (ft_strncmp(tocmp, tmp->next->key, sizecmp) > 0)
// 		{
// 			winner = ft_strdup()
// 		}
// 		else
// 			tmp = tmp->next;
// 	}
// }

/**
 * @brief function print export
 * 
 * @param env 
 */
static void	ft_print_export(t_envlst *env)
{
	t_envlst	*tmp;
	char		**tab;

	tmp = env;
	tab = ft_env_return_envlst_sorted_in_tab(env);
	dbg_display_argv(tab);
	while (tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(tmp->key, 1);
		if (tmp->value && tmp->isenv == 1)
		{
			ft_putchar_fd('=', 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(tmp->value, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
}

// static void	ft_print_export(t_envlst *env)
// {
// 	t_envlst	*tmp;

// 	tmp = env;
// 	while (tmp)
// 	{
// 		ft_putstr_fd("declare -x ", 1);
// 		ft_putstr_fd(tmp->key, 1);
// 		if (tmp->value && tmp->isenv == 1)
// 		{
// 			ft_putchar_fd('=', 1);
// 			ft_putchar_fd('"', 1);
// 			ft_putstr_fd(tmp->value, 1);
// 			ft_putchar_fd('"', 1);
// 		}
// 		ft_putchar_fd('\n', 1);
// 		tmp = tmp->next;
// 	}
// }

/**
 * @brief vérifie si la key est NULL //TODO: doit tchecker le normage des key env
 * 
 * @param key 
 * @return int 
 */
static int	ft_check_if_key_is_valid(char *key, t_data *data)
{
	if (key == NULL)
	{
		ft_putstr_fd(data->pgr_name, 2);
		ft_putstr_fd(" : export : ", 2);
		ft_putstr_fd("not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

/**
 * @brief vérifie si la key est NULL
 * 
 * @param key 
 * @return int 
 */
static int	ft_check_if_null(char *key, t_data *data) //TODO: for parsing
{
	if (key == NULL)
	{
		ft_putstr_fd(data->pgr_name, 2);
		ft_putstr_fd(" : export : ", 2);
		ft_putstr_fd("not a valid identifier\n", 2);
		return (1);
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
static int	ft_main_export(t_envlst *env, char *str, t_data *data)//TODO: norm
{
	char		*key;
	char		*value;
	int			isenv;
	t_envlst	*node;
	
	isenv = TRUE;
	key = ft_env_extract_key_name(str, &isenv);
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

