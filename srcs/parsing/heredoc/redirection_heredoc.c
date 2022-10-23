/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:31:43 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/23 03:28:54 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_redi_in2(int hdc_fd)
{
	if ((hdc_fd = open(PATH_HEREDOC, O_RDONLY)) < 0)
	{
		perror(PATH_HEREDOC);
		return (errno);
	}
	else
	{
		dup2(hdc_fd, STDIN_FILENO);
		close(hdc_fd);
	}
	return (0);
}


// /**
//  * @brief lancer un readline pour faire le heredoc
//  * 
//  * @param token // delimiter
//  * @param pipe //pipe de la cmdtab[ex->i]
//  * @return int 
//  */
// int	ft_heredoc_create(char *token, int *pipe) // TODO: V3 
// {
// 	char	*buf;
// 	char	*heredoc;
// 	char	*prompt;
	
// 	close (pipe[0]);
// 	rl_on_new_line();
// 	prompt = ft_strjoin_max("heredoc %s%s%s> ", COLOR_RED, token, COLOR_NONE);
// 	rl_on_new_line();
// 	heredoc = ft_strdup("");
// 	buf = readline(prompt);
// 	while (ft_strequal(buf, token) != 1)
// 	{
// 		heredoc = ft_strjoin(heredoc, buf);
// 		heredoc = ft_strjoin(heredoc, "\n");
// 		free (buf);
// 		buf = readline(prompt);
// 	}
// 	ft_putstr_fd(heredoc, 1);
// 	ft_putstr_fd(heredoc, pipe[1]);
// 	free (buf);
// 	free (prompt);
// 	return (0);
// }

// int	ft_redi_in1v2(int fd3)
// {
// 	int	fd;
	
// 	if ((fd = open(PATH_HEREDOC, O_RDONLY)) < 0)
// 	{
// 		perror(PATH_HEREDOC);
// 		return (errno);
// 	}
// 	else
// 	{
// 		dup2(fd, STDIN_FILENO);
// 		close(fd);
// 	}
// 	return (0);
// }

int	ft_redi_in1v2(int hdc_fd)
{
	if ((hdc_fd = open(PATH_HEREDOC, O_RDONLY)) < 0)
	{
		perror(PATH_HEREDOC);
		return (errno);
	}
	else
	{
		dup2(hdc_fd, STDIN_FILENO);
		close(hdc_fd);
	}
	return (0);
}


/**
 * @brief lancer un readline pour faire le heredoc
 * 
 * @param token // delimiter
 * @param fd //fd de la cmdtab[ex->i]
 * @return int 
 */
int	ft_heredoc_create(char *token, int fd) // TODO: V4 tmp
{
	char	*buf;
	char	*prompt;
	pid_t	father;
	
	father = fork();
	if(father == 0)
	{
		errno = 0;
		rl_on_new_line();
		prompt = ft_strjoin_max("heredoc %s%s%s> ", COLOR_RED, token, COLOR_NONE);
		rl_on_new_line();
		buf = readline(prompt);
		while (ft_strequal(buf, token) != 1)
		{
			ft_putstr_fd(buf, fd);
			ft_putstr_fd("\n", fd);
			free(buf);
			buf = readline(prompt);
		}
		if (buf)
			free(buf);
		free(prompt);
		exit (errno);
	}
	waitpid(father, NULL, 0);
	return (0);
}


int	ft_heredoc_openfd(t_cmdtab *cmdtab, int i)
{
		if (cmdtab[i].hdcfd > 0) //si deja eu un autre heredocs
			close(cmdtab[i].hdcfd);
		if ((cmdtab[i].hdcfd = open(PATH_HEREDOC, O_CREAT | O_TRUNC \
												| O_WRONLY, 0644)) < 0)
		{
			perror("open");
			exit(errno);
		}
	return (0);
}


int	ft_heredoc_init(t_cmdtab *cmdtab, t_data *data)
{
	int	i;
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
				printf("cmdtabi = %i hdcfd = %i\n", i, cmdtab[i].hdcfd);
				ft_heredoc_create(tmp->next->str, cmdtab[i].hdcfd);
			}
			tmp = tmp->next;
		}
		i++;
	}
	return (0);
}

// int	ft_make_heredoc(t_data *data, t_cmdtab *cmdtab, t_execarg *ex)
// {
// 	t_list *tmp;
	
// 	cmdtab[ex->i].heredoc = ft_strdup("");
// 	tmp = cmdtab[ex->i].lst;
// 	while (tmp)
// 	{
// 		if (tmp->type == IN2) //TODO:
// 		{
// 			free (cmdtab[ex->i].heredoc);
// 			// cmdtab[ex->i].heredoc = ft_heredoc_create(cmdtab[ex->i].lst->next->str); //FIXME:
// 		}
// 		tmp = tmp->next;
// 	}

// 	return (0);
// }

// int	ft_pars_heredoc(t_data *data, t_cmdtab *cmdtab)
// {
// 	t_execarg ex;
	
// 	ex.i = 0;
// 	while(cmdtab[ex.i].lst)
// 	{
// 		if (ft_redi_cmdtab_has_heredoc(cmdtab, &ex)) //TODO:
// 			;
// 	}
	
// 	return (0);
// }

int	ft_redi_cmdtab_has_heredoc(t_cmdtab *cmdtab, t_execarg *ex)
{
	t_list *tmp;
	
	tmp = cmdtab[ex->i].lst;
	while (tmp)
	{
		if (tmp->type == IN2) //TODO:
			return (1);
		tmp = tmp->next;
	}
	return (0);
}