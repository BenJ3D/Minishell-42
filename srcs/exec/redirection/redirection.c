/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:42:35 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/09 18:41:58 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_redirection(t_data *data, t_cmdtab *cmdtab, t_execarg *ex)
{
	t_list	*tmp;
	int		ret;

	tmp = cmdtab[ex->i].lst;
	while (tmp)
	{
		if (tmp->type >= IN1 && tmp->type <= OUT2)
		{
			if (cmdtab[ex->i].rediarg != NULL)
				free (cmdtab[ex->i].rediarg);
			cmdtab[ex->i].reditype = tmp->type;
			cmdtab[ex->i].rediarg = ft_strdup(tmp->next->str);
			ret = ft_dupredi(data, cmdtab, ex);
			if (ret)
				return (ret);
		}
		tmp = tmp->next;
	}	
	return (0);
}

int	ft_dupredi(t_data *data, t_cmdtab *cmdtab, t_execarg *ex)
{
	int	ret;

	if (cmdtab[ex->i].reditype == OUT1)
		ret = ft_redi_out1(cmdtab, ex, data);
	else if (cmdtab[ex->i].reditype == OUT2)
		ret = ft_redi_out2(cmdtab, ex, data);
	else if (cmdtab[ex->i].reditype == IN1)
		ret = ft_redi_in1(cmdtab, ex, data);
	else if (cmdtab[ex->i].reditype == IN2)
		ret = ft_redi_in2(cmdtab[ex->i].hdcfd, cmdtab, ex, data);
	return (ret);
}

/**
 * @brief fixe si 0 cmd detecter pour check les files redi quand meme
 * 	les creer s'ils n'existent pas
 * @param cmdtab 
 * @param data 
 * @return int 
 */
int	ft_check_redi_if_has_no_cmd(t_cmdtab *cmdtab, t_execarg *ex, t_data *data)
{
	pid_t	father;

	father = fork();
	if (father == 0)
		exit(ft_redirection(data, cmdtab, ex));
	waitpid(father, &g_status, 0);
	return (0);
}
