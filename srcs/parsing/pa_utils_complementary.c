/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_utils_complementary.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:56:29 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/11 15:07:41 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_redirection_files_check(char *buffer)
{
	int	pin;

	pin = 0;
	while (buffer[pin] && (buffer[pin] < 33 || buffer[pin] > 126) && \
		buffer[pin] != '\0')
	{
		if (buffer[pin] == '|' || buffer[pin] == '<' || buffer[pin] == '>')
			return (0);
		pin++;
	}
	return (1);
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
			s3[b++] = s2[a++];
	s3[b] = '\0';
	printf("'%s', s1\n", __func__);
	if (s1[0] != '\0')
		free(s1);
	return (s3);
}

static int	ft_pa_deftype_first_cmd(t_list	*tmp, t_data *data)
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
	return (tmp->type);
}

static int	ft_pa_deftype(t_list *tmp)
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
	return (tmp->type);
}

int	ft_define_cmd_type_during_parsing(t_list *lst, t_data *data)
{
	t_list	*tmp;

	if (!lst)
		return (-1);
	tmp = lst;
	if (data->quotes_in_parsing == 1)
	{
		tmp->type = ARG;
		data->type_of_the_last_cmd = 1;
		data->quotes_in_parsing = 0;
	}
	else if (data->first_cmd == 0)
		data->type_of_the_last_cmd = ft_pa_deftype_first_cmd(tmp, data);
	else
		data->type_of_the_last_cmd = ft_pa_deftype(tmp);
	return (0);
}
