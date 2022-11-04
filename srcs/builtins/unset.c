/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/04 12:12:18 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

static int	ft_main_unset_norm1(t_data *data, char *key, t_envlst *tmp)
{
	if (ft_check_if_exportkey_is_valid(key, data))
	{
		ft_err_display_line_error(data, key, "not a valid identifier");
		g_status = 1;
		return ((errno = 1));
	}
	if (ft_env_check_if_key_is_valid(tmp, key) == FALSE)
		return (-1);
	if (ft_strequal(key, "PWD") == TRUE)
	{
		ft_err_display_line_error(data, "unset PWD", "Operation not permitted");
		return ((g_status = 1));
	}
	if (ft_strequal(tmp->key, key))
	{
		ft_env_lstclear_one_first_element(&data->env);
		return (-1);
	}
	return (0);
}

static int	ft_main_unset(t_data *data, char *key)
{
	t_envlst	*tmp;
	char		*ptr;
	int			ret;

	if (key[0] == '\0')
		return (-1);
	tmp = data->env;
	ret = ft_main_unset_norm1(data, key, tmp);
	if (ret == -1)
		return (0);
	else if (ret == 1)
		return (1);
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
	int	i;

	g_status = 0;
	if (!cmd[1] || cmd[1][0] == '\0')
		return (1);
	else
	{
		i = 1;
		while (cmd[i])
			ft_main_unset(data, cmd[i++]);
	}
	return (0);
}
