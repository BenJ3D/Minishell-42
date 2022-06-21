/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/02 18:01:57 by bducrocq          #+#    #+#             */
/*   Updated: 2022/01/03 17:22:53 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intlen(long long nb)
{
	long long	i;
	long long	res;
	int			sign;

	sign = 0;
	i = 0;
	if (nb < 0)
	{
		nb = -nb;
		sign++;
	}
	res = nb;
	if (res > 9)
	{
		res = nb / 10;
		i = ft_intlen(res);
	}
	i += 1 + sign;
	return (i);
}
