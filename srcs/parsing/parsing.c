/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 02:43:41 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/10 12:29:35 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

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
 * @brief split tout le buffer en plusieurs cmd dans une liste chainé
 * 
 * @param lst 
 * @param buffer 
 * @return int 
 */
t_list	*ft_split_buffercmd_in_lst(char *buffer, int bufi)
{
	int		i;
	int		len;
	char	*str;
	t_list	*cmd;

	cmd = NULL;
	while (buffer[bufi])
	{
		while (ft_isspace(buffer[bufi]) && buffer[bufi] && buffer[bufi] != '|')
			bufi = bufi + 1;
		if (buffer[bufi] == '\0')
			return (cmd);
		len = ft_strlen_next_word(buffer + bufi);
		str = ft_calloc(len + 1, sizeof(char));
		if (!str)
			return (NULL);
		i = 0;
		while (len-- > 0)
			str[i++] = buffer[bufi++];
		ft_lstadd_back(&cmd, ft_lstnew(str));
		free(str);
	}
	return (cmd);
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
	char		*str;
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

// 							ls -all | grep @ | ls