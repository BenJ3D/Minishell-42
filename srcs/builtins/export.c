/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/06 12:16:50 by bducrocq         ###   ########.fr       */
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
	if (!cmd[1] || cmd[1][0] == '\0')
		ft_print_export(env);
	else
		ft_main_export(env, cmd[1], data);
	return (0);
}



/**
 * @brief function print export
 * 
 * @param env 
 */
static void	ft_print_export(t_envlst *env)
{
	t_envlst	*tmp;

	tmp = env;
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

/**
 * @brief vérifie si la key est NULL
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
static int	ft_check_if_null(char *key, t_data *data) //TODO: 
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
static int	ft_main_export(t_envlst *env, char *str, t_data *data)
{
	char		*key;
	char		*value;
	int			isenv;
	t_envlst	*ret;
	
	isenv = 1;
	key = ft_env_extract_key_name(str);
	if (key == NULL)
	{
		key = ft_strdup(str);
		value = ft_strdup("");
		isenv = 0;
	}
	else
		value = ft_env_extract_value_content(str);
	ret = ft_env_getenv_lst_value(env, key);
	if (ret)
	{
		if (!ft_strequal(env->value, value))
		{
			free(ret->value);
			ret->value = ft_strdup(value);
		}
	}
	else
		ft_env_lstadd_back(&env, ft_env_lstnew(key, value, isenv));
	free (key);
	free (value);
	return (0);
}

int	ft_shlvl_increment(t_envlst *env, char *value)//TODO:TODO:
{
	char		key[6] = "SHLVL";
	int			isenv;
	t_envlst	*ret;

	value = ft_env_extract_value_content(value);
	ret = ft_env_getenv_lst_value(env, key);
	if (ret)
	{
		if (!ft_strequal(env->value, value))
		{
			free(ret->value);
			ret->value = ft_strdup(value);
		}
	}
	else
		ft_env_lstadd_back(&env, ft_env_lstnew(key, value, isenv));
	free (key);
	free (value);
	return (0);
}