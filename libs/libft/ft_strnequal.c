/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:54:18 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/07 18:15:44 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief return 1 if content s1 == s2 (to n size)
 * 
 * @param s1 
 * @param s2 
 * @param n 
 * @return int 
 */
int	ft_strnequal(const char *s1, const char *s2, size_t n)
{
	char			*str1;
	char			*str2;
	size_t			i;

	i = 0;
	str1 = (char *)s1;
	str2 = (char *)s2;
	if (n == 0)
		return (0);
	while ((str1[i] == str2[i]) && (str1[i] || str2[i]) && i < n - 1)
		i++;
	if (i == n - 1)
		return (1);
	return (0);
}