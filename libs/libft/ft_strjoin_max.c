/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_max.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 22:20:33 by bducrocq          #+#    #+#             */
/*   Updated: 2022/08/21 01:26:19 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_concact(char *src, char *str)
{
	char	*tmpline;
	int		i;
	int		y;
	
	i = 0;
	if (!src)
		src = ft_strdup("");
	tmpline = ft_calloc((ft_strlen(src) + ft_strlen(str) + 1), sizeof(tmpline));
	while (src[i])
	{
		tmpline[y] = src[i];
		y++;
		i++;
	}
	while (*str)
	{
		tmpline[y] = *str;
		y++;
		*str++;
	}
	tmpline[y] = '\0';
	free (src);
	return (tmpline);
}

char *ft_strjoin_max_tmp(const char *fmt, ...)
{
	char *tmp;
	char *tmp2;
	va_list ap;

	va_start(ap, fmt);
	// while (*fmt)
	// {
	// 	ft_strlcat()
	// }

	return (tmp);
}

int main()
{
	char *tmp;
	char *nline = NULL;
	
	// nline = ft_strjoin_max_tmp(" -- %s%s%s --\n", "\033[0;31m", "ben", "\033[0;37m");

	// nline = ft_strdup("Coucou ");
	ft_putstr(nline);
	ft_putstr("\n");
	nline = ft_concact(nline, "Benjamin comment\n");
	ft_putstr(nline);
	ft_putstr("\n");
	// nline = ft_concact(nline, "tu vas\n");
	ft_putstr(nline);
	ft_putstr("Euh..\n");
	// nline = ft_concact(nline, " tu vas ?\n");
	// ft_putstr(nline);
	free (nline);
	return (0);
}
