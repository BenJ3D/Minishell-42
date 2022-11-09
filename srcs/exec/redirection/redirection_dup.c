/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_dup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 18:42:35 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/09 20:31:02 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_redi_doll_errorcheck(t_cmdtab *cmdtab, t_execarg *ex, t_data *data)
{
	if (cmdtab[ex->i].rediarg[0] == '$')
	{
		ft_err_display_line_error(data, "syntax error", "ambiguous redirect");
		return (1);
	}
	return (0);
}

int	ft_redi_out1(t_cmdtab *cmdtab, t_execarg *ex, t_data *data)
{
	char	*errline;

	if (ft_redi_doll_errorcheck(cmdtab, ex, data))
		return (1);
	cmdtab[ex->i].fdredi = open(cmdtab[ex->i].rediarg, \
											O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmdtab[ex->i].fdredi < 0)
	{
		g_status = errno;
		errline = ft_strjoin_max("%s%s: %s%s%s", COLOR_CYAN, \
			data->pgr_name, COLOR_PURPLE, cmdtab[ex->i].rediarg, COLOR_RED);
		perror(errline);
		ft_putstr_fd(COLOR_NONE, 2);
		free (errline);
		return (errno);
	}
	else
	{
		dup2(cmdtab[ex->i].fdredi, STDOUT_FILENO);
		close(cmdtab[ex->i].fdredi);
	}
	return (0);
}

int	ft_redi_out2(t_cmdtab *cmdtab, t_execarg *ex, t_data *data)
{
	char	*errline;

	if (ft_redi_doll_errorcheck(cmdtab, ex, data))
		return (1);
	cmdtab[ex->i].fdredi = open(cmdtab[ex->i].rediarg, \
										O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (cmdtab[ex->i].fdredi < 0)
	{
		g_status = errno;
		errline = ft_strjoin_max("%s%s: %s%s%s", COLOR_CYAN, \
				data->pgr_name, COLOR_PURPLE, cmdtab[ex->i].rediarg, COLOR_RED);
		perror(errline);
		ft_putstr_fd(COLOR_NONE, 2);
		free (errline);
		return (errno);
	}
	else
	{
		dup2(cmdtab[ex->i].fdredi, STDOUT_FILENO);
		close(cmdtab[ex->i].fdredi);
	}
	return (0);
}

int	ft_redi_in1(t_cmdtab *cmdtab, t_execarg *ex, t_data *data)
{
	char	*errline;

	if (ft_redi_doll_errorcheck(cmdtab, ex, data))
		return (1);
	cmdtab[ex->i].fdredi = open(cmdtab[ex->i].rediarg, O_RDONLY);
	if (cmdtab[ex->i].fdredi < 0)
	{
		g_status = errno;
		errline = ft_strjoin_max("%s%s: %s%s%s", COLOR_CYAN, \
				data->pgr_name, COLOR_PURPLE, cmdtab[ex->i].rediarg, COLOR_RED);
		perror(errline);
		ft_putstr_fd(COLOR_NONE, 2);
		free (errline);
		return (errno);
	}
	else
	{
		dup2(cmdtab[ex->i].fdredi, STDIN_FILENO);
		close(cmdtab[ex->i].fdredi);
	}
	return (0);
}

int	ft_redi_in2(int hdc_fd, t_cmdtab *cmdtab, t_execarg *ex, t_data *data)
{
	char	*errline;

	hdc_fd = open(cmdtab[ex->i].hdcpath, O_RDONLY);
	if (hdc_fd < 0)
	{
		g_status = errno;
		errline = ft_strjoin_max("%s%s: %s%s%s", COLOR_CYAN, \
				data->pgr_name, COLOR_PURPLE, cmdtab[ex->i].rediarg, COLOR_RED);
		perror(errline);
		ft_putstr_fd(COLOR_NONE, 2);
		free (errline);
		return (errno);
	}
	else
	{
		dup2(hdc_fd, STDIN_FILENO);
		close(hdc_fd);
	}
	return (0);
}
