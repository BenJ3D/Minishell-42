/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 02:43:41 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/12 19:10:38 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_pipe(t_data	*data, char *buffer)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (buffer[i])
	{
		ft_quotes_checker(data, buffer, i);
		if (buffer[i++] == '|' && data->s_quotes_switch == 0 && \
			data->d_quotes_switch == 0)
			len++;
	}
	if (len == 0)
		len++;
	return (len);
}

/**
 * @brief 
 * 
 * @param lst 
 * @param nbrpipe 
 * @return t_cmdtab* 
 */
t_cmdtab	*ft_create_tab_per_cmd(t_list *lst, int nbrpipe)
{
	t_list		*tmp;
	t_cmdtab	*cmdtab;
	int			i;

	tmp = lst;
	cmdtab = ft_calloc(nbrpipe + 2, sizeof(t_cmdtab));
	if (!cmdtab)
		return (NULL);
	i = 0;
	cmdtab[i++].lst = lst;
	while (tmp)
	{
		if (tmp->str[0] == '|' && tmp->type == 2)
		{
			cmdtab[i].lst = tmp->next;
			tmp->next = NULL;
			tmp = cmdtab[i++].lst;
		}
		else
			tmp = tmp->next;
	}
	return (cmdtab);
}
