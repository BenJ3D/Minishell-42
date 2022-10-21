/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:31:43 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/21 02:13:52 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_redi_in2(t_cmdtab *cmdtab, t_execarg *ex, t_data	*data)
{
	int fdredipipe[2];
	pid_t	pid;
	pipe(fdredipipe);
	if ((pid = fork()) == -1)
	{
		perror("minishell: fork");
		exit(errno);
	}
	printf("pid = %i\n", pid);
	if (pid == 0)
	{
		// close(cmdtab[ex->i].fdredipipe[0]);
		ft_heredoc(data, cmdtab, ex, fdredipipe);
		exit(errno);
	}
	else
	{
		dup2(fdredipipe[0], STDIN_FILENO); //TODO:TODO:
		close(fdredipipe[1]);
		close(fdredipipe[0]);
		waitpid(pid, &g_status, 0);
		// if (WIFEXITED(g_status))
		// 	data->ret = WEXITSTATUS(g_status);
		// kill(pid, SIGTERM);
		// dup2(data->savefd[0], STDIN_FILENO); //TODO:TODO:
	}
	return (0);
}

int	ft_heredoc(t_data *data, t_cmdtab *cmdtab, t_execarg *ex, int *fdredipipe) // TODO: V2 with pipe
{
	char	*buf;
	char	*line;
	char	*intro;
	char	*prompt;
	
	rl_on_new_line();
	prompt = ft_strjoin_max("heredocs %s%s%s> ", \
								COLOR_RED, cmdtab[ex->i].rediarg, COLOR_NONE);
	rl_on_new_line();
	line = ft_strdup("");
	buf = readline(prompt);
	while (ft_strequal(buf, cmdtab[ex->i].rediarg) != 1)
	{
		line = ft_strjoin(line, buf);
		line = ft_strjoin(line, "\n");
		free (buf);
		buf = readline(prompt);
	}
	// write(cmdtab[ex->i].fdredipipe[1], line, ft_strlen(line));
	ft_putstr_fd(line, fdredipipe[1]);
	close (fdredipipe[1]);
	free (buf);
	free (line);
	free (prompt);
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