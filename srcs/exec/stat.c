/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:32:10 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/02 17:45:19 by bducrocq         ###   ########.fr       */
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
	// puts("auncune commande (dbg stat.c:27)\n");
	return (cmd);
}

int	ft_stat_check(t_cmdtab *cmdtab, t_execarg *ex, t_data *data, char *str)
{
	char	*line;
	char	*cmd;
	
	data->statbuf.st_mode = 0;
	cmd = ft_cmdtab_has_cmd(cmdtab, ex);
	if (cmd == NULL)
		return (STAT_NONE);
	if (str == NULL)
		stat(cmd, &data->statbuf);
	else
		stat(str, &data->statbuf);
	if (S_ISDIR(data->statbuf.st_mode) && str != NULL)
	{
		cmdtab[ex->i].pid = fork();
		if (cmdtab[ex->i].pid == 0)
		{
			line = ft_strjoin_max("%s%s: %s%s: %sIs a directory%s\n",
								  COLOR_CYAN, data->pgr_name, COLOR_PURPLE,
								  cmd, COLOR_RED, COLOR_NONE);
			ft_putstr_fd(line, 2);
			free(line);
			exit (0);
		}
		return (STAT_ISDIR);
	}
	else if (S_ISREG(data->statbuf.st_mode))
	{
		return (STAT_ISFILE);
	}
	return (STAT_NONE);
}
