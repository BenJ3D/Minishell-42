/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 02:43:41 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/20 18:30:24 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>

void	ft_free_all_minishell(t_data *data)
{
	ft_env_lstclear(&data->env);
	free(data->pgr_name);
	rl_clear_history();
}


int	ft_free_cmdtab_lst(int pipe, t_cmdtab *cmdtab)
{
	int	i;

	i = 0;
	while (i <= pipe)
		ft_lstclear(&cmdtab[i++].lst);
	free (cmdtab);
	return (0);
}

void	ft_free_tab_char(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free (tab);
}