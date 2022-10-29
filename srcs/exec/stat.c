/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:32:10 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/30 00:17:24 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_stat_check(t_execarg *ex, t_data *data)
{
	char	*line;
	
	ex->isfile = FALSE;
	puts("coucou\n");
	stat(ex->argv[0], &data->statbuf);
	printf("stat = %i\n", data->statbuf.st_mode);
	if (S_ISDIR(data->statbuf.st_mode))
	{
		puts("coucou DIR\n");
		line = ft_strjoin_max("%s%s: %s%s: %sis a directory%s\n",
							COLOR_CYAN, data->pgr_name, COLOR_PURPLE,
											ex->argv[0], COLOR_RED, COLOR_NONE);
		ft_putstr_fd(line, 2);
		free(line);
		return (1);
	}
	else if (S_ISREG(data->statbuf.st_mode))
	{
		ex->isfile = TRUE;
		return (1);
	}
	return (0);
}

