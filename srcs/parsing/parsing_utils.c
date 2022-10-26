/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:48:54 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/26 17:37:43 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

static int	ft_define_cmd_type_during_parsing(t_list *lst, t_data *data) // TODO: a normer !!
{
	t_list	*tmp;

	if (!lst)
		return (-1);
	tmp = lst;
	if (data->first_cmd == 0)
	{
		if (tmp->str[0] == '>')
		{
			if (tmp->str[1] == '>')
				tmp->type = OUT2;
			else
				tmp->type = OUT1;
			tmp->next->type = OUTFILE; //? je ne comprends pas pourquoi on le met ici, et si jamais il n'y a pas de tmp->next?
			tmp = tmp->next;
		}
		else if (tmp->str[0] == '<')
		{
			if (tmp->str[1] == '<')
				tmp->type = IN2;
			else
				tmp->type = IN1;
		}
		else
			tmp->type = CMD;
		data->first_cmd = 1;
	}
	else
	{
		if (tmp->str[0] == '>')
		{
			if (tmp->str[1] == '>')
				tmp->type = OUT2;
			else
				tmp->type = OUT1;
		}
		else if (tmp->str[0] == '<')
		{
			if (tmp->str[1] == '<')
				tmp->type = IN2;
			else
				tmp->type = IN1;
		}
		else if (tmp->str[0] == '|')
			tmp->type = PIPE;
		else
			tmp->type = ARG;
	}
	return (0);
}

char	*ft_strjoin_parsing(char	*s1, char *s2)
{
	int		len;
	int		b;
	int		a;
	char	*s3;

	len = 0;
	b = 0;
	a = 0;
	len = ft_strlen((const char *)s1) + ft_strlen((const char *)s2);
	s3 = ft_calloc(sizeof(char), len + 1);
	if (!s3)
		return (NULL);
	while (s1 && s1[b] != '\0')
	{
			s3[b] = s1[b];
			b++;
	}
	while (s2 && s2[a] != '\0')
	{
			s3[b++] = s2[a];
			a++;
	}
	s3[b] = '\0';
	if (s1[0] != '\0')
		free(s1);
	return (s3);
}

static int	ft_strlen_next_word(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|')
		return (1);
	while (!ft_isspace(str[i]) && str[i] && str[i] != '|')
		i++;
	return (i);
}

int	ft_strlen_parsing(char	*str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);	
}

t_list	*ft_buffercmd_in_lst_quotes(char *buffer, t_list	*cmd, t_data	*data)
{
	int		i;
	int		len;
	char	*str;
	int		bufi;

	bufi = 0;
	while (buffer[bufi])
	{
		if (buffer[bufi] == '\0')
			return (cmd);
		len = ft_strlen_next_word(buffer);
		str = ft_calloc(len + 1, sizeof(char));
		if (!str)
			return (NULL);
		i = 0;
		while(len-- > 0)
			str[i++] = buffer[bufi++];
		ft_lstadd_back(&cmd, ft_lstnew(str));
		free(str);
	}
	ft_define_cmd_type_during_parsing(cmd, data);
	return (cmd);
}

t_list	*ft_buffercmd_in_lst(char *buffer, t_list	*cmd, t_data	*data)
{
	int		i;
	int		len;
	char	*str;
	int		bufi;

	bufi = 0;
	while (buffer[bufi])
	{
		while(ft_isspace(buffer[bufi]) && buffer[bufi] && buffer[bufi] != '|')
			bufi = bufi + 1;
		if (buffer[bufi] == '\0')
			return (cmd);
		len = ft_strlen_next_word(buffer + bufi);
		str = ft_calloc(len + 1, sizeof(char));
		if (!str)
			return (NULL);
		i = 0;
		while(len-- > 0)
			str[i++] = buffer[bufi++];
		ft_lstadd_back(&cmd, ft_lstnew(str));
		free(str);
	}
	ft_define_cmd_type_during_parsing(cmd, data);
	return (cmd);
}
