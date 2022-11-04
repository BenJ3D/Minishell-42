/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 17:00:07 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/25 18:40:39 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <errno.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = NULL;
	ptr = malloc(count * size);
	if (ptr == NULL)
	{
		perror("malloc");
		exit (errno);
	}
	ft_bzero(ptr, size * count);
	return (ptr);
}
