/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:11:17 by bducrocq          #+#    #+#             */
/*   Updated: 2021/11/23 15:39:35 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*sp1;
	const unsigned char	*sp2;

	sp1 = (const unsigned char *)s1;
	sp2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (sp1[i] != sp2[i])
			return ((int)sp1[i] - (int)sp2[i]);
		i++;
	}
	return (0);
}
