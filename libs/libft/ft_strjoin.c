/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 22:20:33 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/12 19:28:00 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1)
		return (0);
	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1), sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	free(s1);
	return (str);
}

/**
 * @brief /!\ s1 sera free
 * 
 * @param s1 
 * @param c 
 * @return char* 
 */
char	*ft_strcharjoin(char *s1, char c)
{
	char	*str;
	int		i;

	i = 0;
	if (!s1)
		return (NULL);
	str = ft_calloc(sizeof(char *), (ft_strlen(s1) + 2));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	free(s1);
	return (str);
}
