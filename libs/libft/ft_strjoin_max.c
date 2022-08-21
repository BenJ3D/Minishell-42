/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_max.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 22:20:33 by bducrocq          #+#    #+#             */
/*   Updated: 2022/08/21 02:31:18 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief joint un nombre variadique d'arg str
 * le return doit être free apres usage
 * 
 * @param fmt formattage
 * @param ... arg : ne mettre que des str ex: "Hello" pas de char ex: 'c'
 * et aucun arg ne doit etre = NULL
 * @return char* avec malloc
 */
char	*ft_strjoin_max(const char *fmt, ...)
{
	char	*nline;
	va_list	ap;

	nline = NULL;
	va_start(ap, fmt);
	while (*fmt)
	{
		if (fmt[0] == '%' && fmt[1] == 's')
		{
			nline = ft_concat_str(nline, va_arg(ap, char *));
			fmt++;
			fmt++;
		}
		else
		{
			nline = ft_concat_char(nline, fmt[0]);
			fmt++;
		}
	}
	va_end(ap);
	return (nline);
}
