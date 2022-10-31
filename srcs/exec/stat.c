/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:32:10 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/31 01:30:41 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"



char *ft_cmdtab_has_cmd(t_cmdtab *cmdtab, t_execarg *ex)
{
	t_list	*tmp;
	char	*cmd;

	cmd = NULL;
	tmp = cmdtab[ex->i].lst;
	while (tmp)
	{
		if (tmp->type == 0)
		{
			cmd = tmp->str;
			return (cmd);
		}
		tmp = tmp->next;
	}
	puts("auncune commande (dbg stat.c:27)\n");
	return (cmd);
}

int	ft_stat_check(t_cmdtab *cmdtab, t_execarg *ex, t_data *data, char *str)
{
	char	*line;
	char	*cmd;
	
	
	cmd = ft_cmdtab_has_cmd(cmdtab, ex);
	printf("dbg check stat | progpath = %s\n", ex->progpath);
	if (cmd == NULL)
		return (STAT_NONE);
	if (str == NULL)
		stat(cmd, &data->statbuf);
	else
	{
		puts("stats check return NULL\n");
		return (STAT_NONE);
	}
	// printf("stat = %i\n", data->statbuf.st_mode);
	if (S_ISDIR(data->statbuf.st_mode))
	{
		line = ft_strjoin_max("%s%s: %s%s: %sIs a directory%s\n",
							COLOR_CYAN, data->pgr_name, COLOR_PURPLE,
											cmd, COLOR_RED, COLOR_NONE);
		ft_putstr_fd(line, 2);
		free(line);
		return (STAT_ISDIR);
	}
	else if (S_ISREG(data->statbuf.st_mode))
	{
		
		// line = ft_strjoin_max("%s%s: %s%s: %sPermission denied%s\n",
		// 					COLOR_CYAN, data->pgr_name, COLOR_PURPLE,
		// 									cmd, COLOR_RED, COLOR_NONE);
		// ft_putstr_fd(line, 2);
		// free(line);
		return (STAT_ISFILE);
	}
	return (STAT_NONE);
}
