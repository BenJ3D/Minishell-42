/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/08 00:38:08 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>
//TODO: faire le parsing avec rules ( doit commencer par une lettre ou _ et que des alphanumeric)
static int	check_if_null(char *str);

/**
 * @brief add var to env with format key=value
 * 
 * @param env 
 * @param str
 * @return int 
 */
static int	main_export(t_envlst *env, char *str)
{
	char	*key;
	char	*value;
	char	*line;
	
	if (check_if_null(key) == 1)
		return (1);
	key = ft_env_extract_key_name(str);
	value = ft_env_extract_value_content(str);
	ft_env_lstadd_back(&env, ft_env_lstnew(key, value));
	free (key);
	free (value);
	return (0);
}
/* function print export
 * @param1 t_env lst
 * @return (void)*/
static void	ft_print_exp(t_envlst *env)
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

static int	check_if_null(char *key)
{
	if (key == NULL)
	{
		ft_putstr_fd("minishell : export : ", 2);
		ft_putstr_fd("not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

int	ft_builtin_export(t_envlst *env, char **cmd)
{
	if (!cmd[1] || cmd[1][0] == '\0')
		ft_print_exp(env);
	else
		main_export(env, cmd[1]);
	return (0);
}

	// 	if (key[0] == '\0')
	// {
	// 	ft_putstr_fd("'minishell : export : ", 2);
	// 	ft_putstr_fd(" '", 2);
	// 	ft_putstr_fd(key, 2);
	// 	ft_putstr_fd("' ", 2);
	// 	ft_putstr_fd("not a valid identifier\n", 2);
	// 	return (1);
	// }