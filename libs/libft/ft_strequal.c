/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 18:17:06 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/07 18:24:30 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief return 1 if content s1 == s2
 * 
 * @param s1 
 * @param s2 
 * @param n 
 * @return int 
 */
int	ft_strequal(const char *s1, const char *s2)
{
	char			*str1;
	char			*str2;
	size_t			i;

	str1 = (char *)s1;
	str2 = (char *)s2;
	if (ft_strlen(str1) != ft_strlen(str2))
		return (0);
	i = 0;
	while ((str1[i] || str2[i]) && str1[i] == str2[i])
		i++;
	if (i == ft_strlen(str1))
		return(1);
	return (0);
}