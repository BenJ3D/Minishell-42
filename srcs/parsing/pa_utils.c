/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:48:54 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/12 19:10:38 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_list	*ft_lstnew_parsing(t_data	*data, char *str, int heavy, \
	int is_empty)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (!tmp)
		return (NULL);
	tmp->str = ft_strdup(str);
	tmp->heavy = heavy;
	tmp->is_empty = is_empty;
	ft_define_cmd_type_during_parsing(tmp, data);
	tmp->next = NULL;
	return (tmp);
}

void	ft_buffercmd_in_lst_quotes(char *buffer, t_data	*data, int heavy, \
	int is_empty)
{
	int		i;
	int		len;
	char	*str;
	int		bufi;

	bufi = 0;
	while (buffer[bufi])
	{
		if (buffer[bufi] == '\0')
			return ;
		len = ft_strlen_parsing(buffer);
		str = ft_calloc(len + 1, sizeof(char));
		if (!str)
			return ;
		i = 0;
		while (len-- > 0)
			str[i++] = buffer[bufi++];
		ft_lstadd_back(&data->cmdtoparse, ft_lstnew_parsing(data, str, heavy, \
			is_empty));
		free(str);
	}
}

void	ft_buffercmd_in_lst(char *buffer, t_data	*data, int heavy, \
	int is_empty)
{
	int		i;
	int		len;
	char	*str;
	int		bufi;

	bufi = 0;
	while (buffer[bufi])
	{
		while (ft_isspace(buffer[bufi]) && buffer[bufi] && buffer[bufi] != '|')
			bufi = bufi + 1;
		if (buffer[bufi] == '\0')
			return ;
		len = ft_strlen_next_word(buffer + bufi);
		str = ft_calloc(len + 1, sizeof(char));
		if (!str)
			return ;
		i = 0;
		while (len-- > 0)
			str[i++] = buffer[bufi++];
		str[i] = '\0';
		ft_lstadd_back(&data->cmdtoparse, ft_lstnew_parsing(data, str, heavy, \
			is_empty));
		free(str);
	}
}
