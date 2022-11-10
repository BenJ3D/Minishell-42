/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:03:51 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/09 17:05:41 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_strlen_next_word(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|')
		return (1);
	while (!ft_isspace(str[i]) && str[i] && str[i] != '|')
		i++;
	return (i);
}

int	ft_strlen_next_word_quotes(t_data	*data, char *str)
{
	int		i;

	i = 0;
	while (str[i])
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
