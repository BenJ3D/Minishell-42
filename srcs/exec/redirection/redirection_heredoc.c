/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:31:43 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/21 19:21:08 by bducrocq         ###   ########.fr       */
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
		// ft_heredoc_create();
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

int	ft_heredoc_create(char *token, int *pipe) // TODO: V3 
{
	char	*buf;
	char	*heredoc;
	char	*prompt;
	
	close (pipe[0]);
	rl_on_new_line();
	prompt = ft_strjoin_max("heredoc %s%s%s> ", COLOR_RED, token, COLOR_NONE);
	rl_on_new_line();
	heredoc = ft_strdup("");
	buf = readline(prompt);
	while (ft_strequal(buf, token) != 1)
	{
		heredoc = ft_strjoin(heredoc, buf);
		heredoc = ft_strjoin(heredoc, "\n");
		free (buf);
		buf = readline(prompt);
	}
	ft_putstr_fd(heredoc, 1);
	ft_putstr_fd(heredoc, pipe[1]);
	free (buf);
	free (prompt);
	return (0);
}

// char	*ft_heredoc_create(char *token, int *pipe) // TODO: V3 
// {
// 	char	*buf;
// 	char	*heredoc;
// 	char	*prompt;
	
// 	rl_on_new_line();
// 	prompt = ft_strjoin_max("heredoc %s%s%s> ", COLOR_RED, token, COLOR_NONE);
// 	rl_on_new_line();
// 	heredoc = ft_strdup("");
// 	buf = readline(prompt);
// 	while (ft_strequal(buf, token) != 1)
// 	{
// 		// heredoc = ft_strjoin(heredoc, buf);
// 		// heredoc = ft_strjoin(heredoc, "\n");
// 		free (buf);
// 		ft_putstr_fd()
// 		buf = readline(prompt);
// 	}
// 	free (buf);
// 	free (prompt);
// 	return (heredoc);
// }
