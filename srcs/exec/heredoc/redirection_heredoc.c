/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:31:43 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/12 19:11:28 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	ft_heredoc_create_child(char *token, int fd)
{
	char	*buf;
	char	*prompt;

	buf = NULL;
	prompt = ft_strjoin_max("heredoc %s%s%s> ", COLOR_RED, token, COLOR_NONE);
	errno = 0;
	rl_on_new_line();
	buf = readline(prompt);
	while (ft_strequal(buf, token) != 1 && buf)
	{
		ft_putstr_fd(buf, fd);
		ft_putstr_fd("\n", fd);
		free(buf);
		buf = readline(prompt);
	}
	free(buf);
	free(prompt);
	exit (errno);
}

/**
 * @brief lancer un readline pour faire le heredoc
 * 
 * @param token // delimiter
 * @param fd //fd de la cmdtab[ex->i]
 * @return int 
 */
int	ft_heredoc_create(char *token, int fd)
{
	pid_t	father;

	father = fork();
	if (father == 0)
	{
		signal_recept_not_blocking(0);
		ft_heredoc_create_child(token, fd);
		exit (0);
	}
	waitpid(father, &g_status, 0);
	return (0);
}

int	ft_heredoc_openfd(t_cmdtab *cmdtab, int i)
{
	char	*pathtmp;
	char	*itoatmp;

	itoatmp = ft_itoa(i);
	pathtmp = ft_strjoin_max("%s%s", PATH_HEREDOC, itoatmp);
	free (itoatmp);
	if (cmdtab[i].hdcpath != NULL)
		free (cmdtab[i].hdcpath);
	cmdtab[i].hdcpath = ft_strdup(pathtmp);
	free (pathtmp);
	if (cmdtab[i].hdcfd > 0)
		close(cmdtab[i].hdcfd);
	cmdtab[i].hdcfd = open(cmdtab[i].hdcpath, O_CREAT | O_TRUNC \
															| O_WRONLY, 0644);
	if (cmdtab[i].hdcfd < 0)
	{
		perror("open");
		exit(errno);
	}
	return (0);
}

int	ft_heredoc_init(t_cmdtab *cmdtab)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (cmdtab[i].lst)
	{
		cmdtab[i].hdcfd = 0;
		tmp = cmdtab[i].lst;
		while (tmp)
		{
			if (tmp->type == IN2)
			{
				ft_heredoc_openfd(cmdtab, i);
				ft_heredoc_create(tmp->next->str, cmdtab[i].hdcfd);
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}

/**
 * @brief return 1 si heredocs detecte dans la commande
 * 
 * @param cmdtab 
 * @param ex 
 * @return int 
 */
int	ft_redi_cmdtab_has_heredoc(t_cmdtab *cmdtab, t_execarg *ex)
{
	t_list	*tmp;

	tmp = cmdtab[ex->i].lst;
	while (tmp)
	{
		if (tmp->type == IN2)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
