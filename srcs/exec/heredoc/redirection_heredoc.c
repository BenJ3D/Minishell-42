/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_heredoc.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 19:31:43 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/26 16:06:17 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_redi_in2(int hdc_fd, t_cmdtab *cmdtab, t_execarg *ex)
{
	if ((hdc_fd = open(cmdtab[ex->i].hdcpath, O_RDONLY)) < 0)
	{
		perror(cmdtab[ex->i].hdcpath);
		return (errno);
	}
	else
	{
		dup2(hdc_fd, STDIN_FILENO);
		close(hdc_fd);
	}
	return (0);
}

// int	ft_redi_in1v2(int hdc_fd)
// {
// 	if ((hdc_fd = open(PATH_HEREDOC, O_RDONLY)) < 0)
// 	{
// 		perror(PATH_HEREDOC);
// 		return (errno);
// 	}
// 	else
// 	{
// 		dup2(hdc_fd, STDIN_FILENO);
// 		close(hdc_fd);
// 	}
// 	return (0);
// }


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
	
	buf = NULL;
	prompt = ft_strjoin_max("heredoc %s%s%s> ", COLOR_RED, token, COLOR_NONE);
	father = fork();
	if(father == 0)
	{
		errno = 0;
		rl_on_new_line();
		rl_on_new_line();
		buf = readline(prompt);
		while (ft_strequal(buf, token) != 1)
		{
			ft_putstr_fd(buf, fd);
			ft_putstr_fd("\n", fd);
			free(buf);
			buf = readline(prompt);
		}
		free(buf);
		exit (errno);
	}
	free(buf);
	free(prompt);
	waitpid(father, NULL, 0);
	return (0);
}


int	ft_heredoc_openfd(t_cmdtab *cmdtab, int i)
{
	char	*pathtmp;
	char	*itoatmp;

	itoatmp = ft_itoa(i);
	pathtmp = ft_strjoin_max("%s%s", PATH_HEREDOC, itoatmp);
	free (itoatmp);
	if (cmdtab[i].hdcpath != NULL) // TODO:
		free (cmdtab[i].hdcpath);
	cmdtab[i].hdcpath = ft_strdup(pathtmp);
	free (pathtmp);
	if (cmdtab[i].hdcfd > 0) //si deja eu un autre heredocs
		close(cmdtab[i].hdcfd);
	if ((cmdtab[i].hdcfd = open(cmdtab[i].hdcpath, O_CREAT | O_TRUNC \
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
				// printf("cmdtabi = %i hdcfd = %i\n", i, cmdtab[i].hdcfd);
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


/**
 * @brief return 1 si heredocs detecte dans la commande
 * 
 * @param cmdtab 
 * @param ex 
 * @return int 
 */
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