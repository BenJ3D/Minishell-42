/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_param.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 21:41:32 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/28 21:53:27 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_param(int argc, char **argv)
{
	int		i;
	char	*t;

	i = 0;
	while (argc - 1 > i)
	{
		if ((ft_strcmp(argv[i], argv[i + 1]) > 0))
		{
			t = argv[i];
			argv[i] = argv[i + 1];
			argv[i + 1] = t;
			i = 0;
		}
		else
			i++;
	}
}
