/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:45:53 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/10 21:15:59 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

/**
 * @brief update data->line prompt
 *
 * @return
 */
char	*prompt_update(t_envlst *env, char *prgname)
{
	char	*line;
	char	*user;
	char	usertmp[USER_MAX_LEN];
	char	*status;

	status = ft_itoa(g_status % 255);
	if (ft_env_check_if_key_is_valid(env, "USER") == FALSE)
		line = ft_strjoin_max("%s[%s] %s%s>%s$ ", \
		COLOR_RED, status, COLOR_CYAN, prgname, COLOR_NONE);
	else
	{
		user = ft_env_getstr_env_value(env, "USER");
		if (ft_strlen(user) > (USER_MAX_LEN))
		{
			ft_strlcpy(usertmp, user, USER_MAX_LEN);
			free (user);
			user = ft_strdup(usertmp);
		}
		line = ft_strjoin_max("%s[%s] %s- %s -%s %s>%s$ ", \
		COLOR_RED, status, COLOR_GREEN, user, \
					COLOR_CYAN, prgname, COLOR_NONE);
		free (user);
	}
	free (status);
	return (line);
}

/**
 * @brief readline prompt
 * 
 * @param av 
 * @param data 
 * @return int 
 */
int	ft_prompting(char **av, t_data *data)
{
	signal_recept_not_blocking_cmd();
	data->line = prompt_update(data->env, data->pgr_name);
	data->buffer = readline(data->line);
	signal_recept_blocking_cmd();
	if (data->buffer)
		return (1);
	else
		return (0);
}

/**
 * @brief main tunction prompt minihell
 * 
 * @param av 
 * @param data 
 */
void	prompt_minishell(char **av, t_data *data)
{
	int		nbpipe;

	data->buffer = NULL;
	data->line = NULL;
	while (ft_prompting(av, data))
	{
		if (data->buffer[0] != '\0')
			add_history(data->buffer);
		nbpipe = ft_parsing_prompt(data, data->buffer);
		if (nbpipe != 0)
		{
			ft_run_execve(data->cmdtab, data);
			ft_free_cmdtab_lst(nbpipe, data->cmdtab);
		}
		free(data->buffer);
		free(data->line);
	}
	free(data->line);
	free(data->buffer);
	rl_replace_line("exit", 0);
	rl_on_new_line();
	rl_redisplay();
}
