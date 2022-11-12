/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:32:10 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/12 19:10:38 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/**
 * @brief return str cmd si CMD trouvé, sinon return NULL
 * 
 * @param cmdtab 
 * @param ex 
 * @return char* 
 */
char	*ft_cmdtab_cmdstr_if_has_cmd(t_cmdtab *cmdtab, t_execarg *ex)
{
	t_list	*tmp;
	char	*cmd;

	cmd = NULL;
	tmp = cmdtab[ex->i].lst;
	while (tmp)
	{
		if (tmp->type == 0)
		{
			if (tmp->is_empty == 1)
				cmd = ft_strdup("");
			else
				cmd = tmp->str;
			return (cmd);
		}
		tmp = tmp->next;
	}
	return (cmd);
}

/**
 * @brief vérifie si la str est un dossier ou fichier ou aucun des deux
 * 
 * @param cmdtab 
 * @param ex 
 * @param data 
 * @param str 
 * @return int STAT_ISDIR STAT_ISFILE STAT_NONE
 */
int	ft_stat_check(t_cmdtab *cmdtab, t_execarg *ex, t_data *data, char *str)
{
	char	*cmd;

	data->statbuf.st_mode = 0;
	cmd = ft_cmdtab_cmdstr_if_has_cmd(cmdtab, ex);
	if (cmd == NULL)
		return (STAT_NONE);
	if (*cmd == '\0')
		return (STAT_ISEMPTY);
	if (str == NULL)
		stat(cmd, &data->statbuf);
	else
		stat(str, &data->statbuf);
	if (S_ISDIR(data->statbuf.st_mode) && str != NULL)
	{
		ft_stat_error_is_dir(data, cmdtab, ex, cmd);
		return (STAT_ISDIR);
	}
	else if (S_ISREG(data->statbuf.st_mode))
		return (STAT_ISFILE);
	return (STAT_NONE);
}

/**
 * @brief display error message Is a directory and exit 126
 * 
 */
void	ft_stat_error_is_dir(t_data *data, t_cmdtab *cmdtab, \
													t_execarg *ex, char *cmd)
{
	char	*line;

	cmdtab[ex->i].pid = fork();
	if (cmdtab[ex->i].pid == 0)
	{
		if (cmd[0] == '.' && cmd[1] == '\0')
			line = ft_strjoin_max("%s%s: %s%s: \
%sfilename argument required%s\n", COLOR_CYAN, data->pgr_name, COLOR_PURPLE, \
													cmd, COLOR_RED, COLOR_NONE);
		else if (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '\0')
				line = ft_strjoin_max("%s%s: %s%s: %scommand not found%s\n", \
				COLOR_CYAN, data->pgr_name, COLOR_PURPLE, \
				cmd, COLOR_RED, COLOR_NONE);
		else
			line = ft_strjoin_max("%s%s: %s%s: %sis a directory%s\n", \
									COLOR_CYAN, data->pgr_name, COLOR_PURPLE, \
													cmd, COLOR_RED, COLOR_NONE);
		ft_putstr_fd(line, STDERR_FILENO);
		free(line);
		free(cmd);
		exit (126);
	}
}
