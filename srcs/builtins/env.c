/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/05 17:29:24 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	ft_builtin_env(t_envlst *envlst)
{
	t_envlst	*tmp;

	tmp = envlst;
	while (tmp)
	{
		if (tmp->isenv == 1)
		{
		ft_putstr(tmp->key);
		ft_putstr("=");
		ft_putstr(tmp->value);
		ft_putstr("\n");
		}
		tmp = tmp->next;
	}
}


// void	ft_builtin_env(char **env)
// {
// 	int	i;

// 	i = 0;
// 	if (!env)
// 		return ;
// 	while (env[i])
// 	{
// 		ft_putstr(env[i++]);
// 		ft_putchar('\n');
// 	}
// }