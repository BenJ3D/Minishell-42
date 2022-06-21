/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunnbr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 10:35:51 by vvaltone          #+#    #+#             */
/*   Updated: 2022/03/12 13:39:11 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief 
 * 
 * @param n 
 * @return intlen
 */
int	ft_putunnbr(unsigned int n)
{
	char	c;
	int		intlen;

	intlen = ft_intlen((long long)n);
	if (n < 10)
	{
		c = n + '0';
		write(1, &c, 1);
	}
	else
	{
		ft_putunnbr((n / 10));
		ft_putunnbr((n % 10));
	}
	return (intlen);
}
