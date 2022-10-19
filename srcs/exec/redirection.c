/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:42:35 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/18 17:58:56 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"
int	ft_dupredi(t_data *data, t_cmdtab *cmdtab, t_execarg *ex);

int	ft_redirection(t_data *data, t_cmdtab *cmdtab, t_execarg *ex) //TODO:TODO:TODO:
{
	t_list	*tmp;

	tmp = cmdtab[ex->i].lst;
	if ((cmdtab[ex->i].redirection = \
							ft_check_if_cmd_has_redirection(cmdtab[ex->i].lst)))
	{
		//TODO: faire une while poru faire toutes les redi
		while (tmp)
		{
			if (tmp->type >= 7 && tmp->type <= 9)
			{
				cmdtab[ex->i].rediarg = ft_strdup(tmp->str);
				break ;
			}
			tmp = tmp->next;
		}
	}
	return (ft_dupredi(data, cmdtab, ex));
}

int	ft_dupredi(t_data *data, t_cmdtab *cmdtab, t_execarg *ex)
{
	if (cmdtab[ex->i].redirection == OUT1)
		{
			if ((cmdtab[ex->i].fdredi = open(cmdtab[ex->i].rediarg,\
									O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
			{
				perror(cmdtab[ex->i].rediarg);
				return (errno);
			}
			else
			{
				dup2(cmdtab[ex->i].fdredi, STDOUT_FILENO);
				close(cmdtab[ex->i].fdredi);
			}
		}
		else if (cmdtab[ex->i].redirection == OUT2)
		{
			if ((cmdtab[ex->i].fdredi = open(cmdtab[ex->i].rediarg,\
									O_WRONLY | O_CREAT | O_APPEND, 0644)) < 0)
			{
				perror(cmdtab[ex->i].rediarg);
				return (errno);
			}
			else
			{
				dup2(cmdtab[ex->i].fdredi, STDOUT_FILENO);
				close(cmdtab[ex->i].fdredi);
			}
		}
		else if (cmdtab[ex->i].redirection == IN1)
		{
			if ((cmdtab[ex->i].fdredi = open(cmdtab[ex->i].rediarg,\
																O_RDONLY)) < 0)
			{
				perror(cmdtab[ex->i].rediarg);
				return (errno);
			}
		}
		else if (cmdtab[ex->i].redirection == IN2)
		{
			pipe (cmdtab[ex->i].fdredipipe);
			if ((cmdtab[ex->i].pidredi = fork()) == -1)
			{
				perror("minishell: fork");
				exit(errno);
			}
			if (cmdtab[ex->i].pidredi == 0)
			{
				ft_heredoc(data, cmdtab, ex);
				exit(0);
			}
			else
				close (cmdtab[ex->i].fdredipipe[1]);
		}
	return (0);
}

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
