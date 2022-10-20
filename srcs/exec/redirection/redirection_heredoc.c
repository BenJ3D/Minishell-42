/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:31:43 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/20 18:48:54 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"




int	ft_redi_in2(t_cmdtab *cmdtab, t_execarg *ex, t_data	*data)
{
	pipe(cmdtab[ex->i].fdredipipe);
	if ((cmdtab[ex->i].pidredi = fork()) == -1)
	{
		perror("minishell: fork");
		exit(errno);
	}
	if (cmdtab[ex->i].pidredi == 0)
	{
		// close(cmdtab[ex->i].fdredipipe[0]);
		ft_heredoc(data, cmdtab, ex);
		exit(errno);
	}
	else
	{
		dup2(cmdtab[ex->i].fdredipipe[0], STDIN_FILENO); //TODO:TODO:
		close(cmdtab[ex->i].fdredipipe[1]);
		close(cmdtab[ex->i].fdredipipe[0]);
		waitpid(cmdtab[ex->i].pidredi, NULL, 0);
		// dup2(data->savefd[0], STDIN_FILENO); //TODO:TODO:
	}
	return (0);
}

int	ft_heredoc(t_data *data, t_cmdtab *cmdtab, t_execarg *ex) // TODO: V2 with pipe
{
	char	*buf;
	char	*line;
	char	*intro;
	
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
	ft_putstr_fd("SORTIE HEREDOCS\n", 2);
	write(cmdtab[ex->i].fdredipipe[1], line, ft_strlen(line));
	// ft_putstr_fd(line, cmdtab[ex->i].fdredipipe[1]);
	close (cmdtab[ex->i].fdredipipe[1]);
	free (buf);
	free (line);
	free (intro);
	return (0);
}

// int	ft_heredoc(t_data *data, t_cmdtab *cmdtab, t_execarg *ex)
// {
// 	char	*buf;
// 	char	*line;
// 	char	*intro;
	
// 	close (cmdtab[ex->i].fdredipipe[0]);
// 	rl_on_new_line();
// 	intro = ft_strjoin_max("Enter \"%s%s%s\" to complete the heredoc\n", \
// 								COLOR_RED, cmdtab[ex->i].rediarg, COLOR_NONE);
// 	ft_putstr_fd(intro, 1);
// 	rl_on_new_line();
// 	line = ft_strdup("");
// 	buf = readline("heredoc> ");
// 	while (ft_strequal(buf, cmdtab[ex->i].rediarg) != 1)
// 	{
// 		line = ft_strjoin(line, buf);
// 		line = ft_strjoin(line, "\n");
// 		free (buf);
// 		buf = readline("heredoc> ");
// 	}
// 	write(cmdtab[ex->i].fdredipipe[1], line, ft_strlen(line));
// 	close (cmdtab[ex->i].fdredipipe[1]);
// 	free (buf);
// 	free (line);
// 	free (intro);
// 	return (0);
// }