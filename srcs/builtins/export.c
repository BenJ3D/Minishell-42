/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/06 04:19:13 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

static int	ft_main_export(t_envlst *env, char *str, t_data *data);
static void	ft_print_export(t_envlst *env);

/**
 * @brief Fonction mère à appeler
 * 
 * @param env 
 * @param cmd 
 * @return int 
 */
int	ft_builtin_export(t_envlst *env, char **cmd, t_data *data)
{
	int	i;

	g_status = 0;
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

/**
 * @brief function print export
 * 
 * @param env 
 */
static void	ft_print_export(t_envlst *env)
{
	char		**tab;
	int			i;

	tab = ft_env_return_envlst_sorted_in_tab(env, 0);
	i = 0;
	while (tab[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putstr_fd(tab[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

/**
 * @brief vérifie si la key est NULL et son normage
 * 
 * @param key 
 * @return int 
 */
int	ft_check_if_exportkey_is_valid(char *key)
{
	int	i;

	if (key == NULL)
		return (1);
	i = 0;
	if (!ft_isalpha(key[i]) && key[i] != '_')
		return (1);
	i++;
	while (key[i])
	{
		if (!ft_isalnum(key[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_main_export_norm1(t_envlst *env, char *key, char *str, int isenv)
{
	t_envlst	*node;
	char		*value;

	if (ft_env_check_if_key_is_valid(env, key) == TRUE)
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
}

/**
 * @brief add var to env with format key=value
 * 
 * @param env 
 * @param str name of futur key
 * @return int 
 */
static int	ft_main_export(t_envlst *env, char *str, t_data *data)
{
	char		*key;
	int			isenv;

	isenv = TRUE;
	key = ft_env_extract_key_name(str, &isenv);
	if (ft_check_if_exportkey_is_valid(key))
	{
		ft_err_display_line_export_error(data, str, "not a valid identifier");
		g_status = 1;
		errno = 1;
		return (1);
	}
	ft_main_export_norm1(env, key, str, isenv);
	free (key);
	return (0);
}
