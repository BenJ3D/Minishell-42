/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:31:43 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/19 19:31:51 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_heredoc(t_data *data, t_cmdtab *cmdtab, t_execarg *ex)
{
	char	*buf;
	char	*line;
	char	*intro;
	
	close (cmdtab[ex->i].fdredipipe[0]);
	rl_on_new_line();
	intro = ft_strjoin_max("Enter \"%s%s%s\" to complete the heredoc\n", \
								COLOR_RED, cmdtab[ex->i].rediarg, COLOR_NONE);
	ft_putstr_fd(intro, 1);
	rl_on_new_line();
	line = ft_strdup("");
	buf = readline("heredoc> ");
	while (ft_strequal(buf, cmdtab[ex->i].rediarg) != 1)
	{
		line = ft_strjoin(line, buf);
		line = ft_strjoin(line, "\n");
		free (buf);
		buf = readline("heredoc> ");
	}
	write(cmdtab[ex->i].fdredipipe[1], line, ft_strlen(line));
	close (cmdtab[ex->i].fdredipipe[1]);
	free (buf);
	free (line);
	free (intro);
	return (0);
}