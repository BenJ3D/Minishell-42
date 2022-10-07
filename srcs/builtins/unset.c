/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/07 23:04:14 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

static int	ft_main_unset(t_data *data, char *key)
{
	t_envlst	*tmp;
	char		*ptr;

	if (key[0] == '\0')
		return (-1);
	tmp = data->env;
	if (ft_env_check_if_key_is_valid(tmp, key) == FALSE)
		return (0);
	if (ft_strequal(key, "PWD") == TRUE)
		return (ft_putstr_fd("failure: PWD is required\n", 2));
	if (ft_strequal(tmp->key, key))
	{
		ft_env_lstclear_one_first_element(&data->env);
		return (0);
	}
	while (tmp && tmp->next)
	{
		if (ft_strequal(tmp->next->key, key))
		{
			ft_env_lstclear_one(&tmp);
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

/**
 * @brief unset var env
 * /!\/!\ Ne check pas si cmd[1] est vide ! donc le faire avant /!\/!\
 * @param env 
 * @param cmd 
 * @return int 
 */
int	ft_builtin_unset(t_data *data, char **cmd)
{
	if (!cmd[1] || cmd[1][0] == '\0')
		return (1);
	else
		ft_main_unset(data, cmd[1]);
	return (0);
}