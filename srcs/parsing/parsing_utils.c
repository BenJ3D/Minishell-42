/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 13:48:54 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/05 19:43:56 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_redirection_files_check(t_data	*data, char	*buffer)
{
	int	pin;

	pin = 0;
	while (buffer[pin] && (buffer[pin] < 33 || buffer[pin] > 126) && buffer[pin] != '\0')
	{
		if (buffer[pin] == '|' || buffer[pin] == '<' || buffer[pin] == '>')
			return (0);
		pin++;
	}
	return (1);
}

static int	ft_define_cmd_type_during_parsing(t_list *lst, t_data *data)
{
	t_list	*tmp;

	if (!lst)
		return (-1);
	tmp = lst;
	if (data->quotes_in_parsing == 1)
		tmp->type = ARG;
	else if (data->first_cmd == 0)
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
	data->type_of_the_last_cmd = tmp->type;
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

static int	ft_strlen_next_word_quotes(t_data	*data, char *str)
{
	int		i;
	char	c;

	if (data->s_quotes_switch == 1)
		c = '\'';
	else
		c = '"';
	i = 0;
	while (str[i] && str[i] != c)
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

static t_list	*ft_lstnew_parsing(t_data	*data, char *str, int heavy)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (!tmp)
		return (NULL);
	tmp->str = ft_strdup(str);
	tmp->heavy = heavy;
	ft_define_cmd_type_during_parsing(tmp, data);
	tmp->next = NULL;
	return (tmp);
}

t_list	*ft_buffercmd_in_lst_quotes(char *buffer, t_data	*data, int	heavy)
{
	int		i;
	int		len;
	char	*str;
	int		bufi;

	bufi = 0;
	while (buffer[bufi])
	{
		if (buffer[bufi] == '\0')
			return (data->cmdtoparse);
		len = ft_strlen_next_word_quotes(data, buffer);
		str = ft_calloc(len + 1, sizeof(char));
		i = 0;
		while (len-- > 0)
			str[i++] = buffer[bufi++];
		ft_lstadd_back(&data->cmdtoparse, ft_lstnew_parsing(data, str, heavy));
		free(str);
	}
	return (data->cmdtoparse);
}

t_list	*ft_buffercmd_in_lst(char *buffer, t_data	*data, int	heavy)
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
			return (data->cmdtoparse);
		len = ft_strlen_next_word(buffer + bufi);
		str = ft_calloc(len + 1, sizeof(char));
		i = 0;
		while (len-- > 0)
			str[i++] = buffer[bufi++];
		ft_lstadd_back(&data->cmdtoparse, ft_lstnew_parsing(data, str, heavy));
		free(str);
	}
	return (data->cmdtoparse);
}
