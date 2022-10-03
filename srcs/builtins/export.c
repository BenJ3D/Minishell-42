/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/04 00:56:51 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>
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
	t_envlst	*ret;
	
	key = ft_env_extract_key_name(str);
	if (ft_check_if_null(key, data) == 1)
		return (-1);
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
		ft_env_lstadd_back(&env, ft_env_lstnew(key, value));
	free (key);
	free (value);
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
		if (tmp->value)
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
static int	ft_check_if_null(char *key, t_data *data)
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
