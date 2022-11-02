/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/02 20:26:56 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

static int	ft_main_unset(t_data *data, char *key)
{
	t_envlst	*tmp;
	char		*ptr;
	char		*errline;

	if (key[0] == '\0')
		return (-1);
	if (ft_check_if_exportkey_is_valid(key, data))
	{
		errline = ft_strjoin_max("%s%s: %s`%s': %snot a valid identifier%s\n",
				COLOR_CYAN, data->pgr_name, COLOR_PURPLE, 
				key, COLOR_RED, COLOR_NONE);
		ft_putstr_fd(errline, 2);
		g_status = 1;
		errno = 1;
		free (errline);
		return (1);
	}
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
	int	i;
	
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
