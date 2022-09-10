/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/10 22:03:40 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>
//TODO:SEGV if unset dont exist
/**
 * @brief unset var env
 * /!\/!\ Ne check pas si cmd[1] est vide ! donc le faire avant /!\/!\
 * @param env 
 * @param key 
 * @return int 
 */
static int	ft_main_unset(t_envlst *env, char *str)
{
	t_envlst	*tmp;
	char		*ptr;
	
	if (str[0] == '\0')
		return (-1);
	if (ft_env_getenv_lst_value(env, str) == NULL)
		return (0);
	tmp = env;
	while (tmp)
	{
		if (ft_strequal(tmp->next->key, str))
		{
			ft_env_lstclear_one(&tmp);
			return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}
// static int	ft_main_unset(t_envlst *env, char *str)
// {
// 	t_envlst	*tmp;
// 	char		*ptr;
	
// 	tmp = env;
// 	if (str[0] == '\0')
// 		return (-1);
// 	while (tmp)
// 	{
// 		if (ft_strequal(tmp->next->key, str))
// 		{
// 			ft_env_lstclear_one(&tmp);
// 			return (0);
// 		}
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }


int	ft_builtin_unset(t_envlst *env, char **cmd)
{
	if (!cmd[1] || cmd[1][0] == '\0')
		return (1);
	else
		ft_main_unset(env, cmd[1]);
	return (0);
}