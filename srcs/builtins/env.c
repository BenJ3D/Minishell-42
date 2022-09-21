/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/22 00:31:14 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>

void	ft_builtin_env(t_envlst *envlst)
{
	t_envlst	*tmp;

	tmp = envlst;
	while (tmp)
	{
		ft_putstr(tmp->key);
		ft_putstr("=");
		ft_putstr(tmp->value);
		ft_putstr("\n");
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