/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:35:43 by bducrocq          #+#    #+#             */
/*   Updated: 2021/11/23 15:32:31 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dsts)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	i;
	size_t	dist;

	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	i = 0;
	while (i < dsts && dst[i])
		i++;
	dist = i;
	if (dsts < dst_len || dsts == 0)
		return (src_len + dsts);
	if (dst_len < dsts)
	{
		i = 0;
		while ((i < dsts - dst_len - 1) && src[i])
		{
			dst[dst_len + i] = src[i];
			i++;
		}
	}
	if (i > 0)
		dst[dst_len + i] = '\0';
	return (src_len + dist);
}
