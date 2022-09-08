/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/08 14:54:29 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>
static int	ft_check_if_null(char *str);
static int	ft_main_export(t_envlst *env, char *str);
static void	ft_print_export(t_envlst *env);

//TODO: faire le parsing avec rules ( doit commencer par une lettre ou _ et que des alphanumeric)
/**
 * @brief Fonction mère à appeler, TODO: parsing a faire
 * 
 * @param env 
 * @param cmd 
 * @return int 
 */
int	ft_builtin_export(t_envlst *env, char **cmd)
{
	if (!cmd[1] || cmd[1][0] == '\0')
		ft_print_export(env);
	else
		ft_main_export(env, cmd[1]);
	return (0);
}

/**
 * @brief add var to env with format key=value
 * 
 * @param env 
 * @param str
 * @return int 
 */
static int	ft_main_export(t_envlst *env, char *str)
{
	char	*key;
	char	*value;
	char	*line;
	
	key = ft_env_extract_key_name(str);
	if (ft_check_if_null(key) == 1)
		return (1);
	value = ft_env_extract_value_content(str);
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
static int	ft_check_if_null(char *key)
{
	if (key == NULL)
	{
		ft_putstr_fd("minishell : export : ", 2);
		ft_putstr_fd("not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}
