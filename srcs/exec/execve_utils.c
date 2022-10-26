/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:32:10 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/19 19:03:02 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

/**
 * @brief return 1 si pipe detecté dans la commande
 * 
 * @param lst 
 * @return int 
 */
int	ft_check_if_cmd_has_pipe(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

/**
 * @brief return type redirection si detecté dans la commande
 * 
 * @param lst 
 * @return int 0 si pas de redirection
 */
int	ft_check_if_cmd_has_redirection(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->type >= IN1 && tmp->type <= OUT2)
			return (tmp->type);
		tmp = tmp->next;
	}
	return (0);
}


int	ft_redi_init_all_redirections(t_cmdtab *cmdtab, t_execarg *ex, t_data *data) //TODO:
{
	
	return (0);
}
