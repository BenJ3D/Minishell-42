/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pa_cmp_ft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:33:25 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/11 10:37:08 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

/**
 * @brief parsing de base pour decouper les cmd et args
 * 
 * @param data 
 * @param buffer 
 * @return int 
 */
int	ft_parsing_prompt(t_data *data, char *buffer)
{
	int		pipe;
	int		check;

	pipe = ft_count_pipe(data, buffer);
	if (!ft_full_prompt_quote_check(data, buffer))
	{
		ft_err_display_line_error(data, "syntax error", "invalid quotes");
		return (0);
	}
	check = ft_total_parsing(data, buffer);
	if (check != 1)
	{
		printf("Test\n");
		if (check == 0)
			ft_err_display_line_error(data, "syntax error", " ");
		free_the_birds(data);
		return (0);
	}
	if (!ft_define_cmd_type(data->cmdtoparse, data))
	{
		ft_err_display_line_error(data, "syntax error", "near unexpected '|'");
		free_the_birds(data);
		return (0);
	}
	dbg_lstdisplay_color_type(data->cmdtoparse);
	data->cmdtab = ft_create_tab_per_cmd(data->cmdtoparse, pipe);
	return (pipe);
}

char	**ft_lstcmd_to_cmdarg_for_execve_bis(t_list	*tmp, char	**argv)
{
	int	y;

	y = 1;
	while (tmp)
	{
		if (tmp->type == CMD)
		{
			if (tmp->is_empty == 1)
				argv[0] = ft_strdup("");
			else
				argv[0] = ft_strdup(tmp->str);
		}
		else if (tmp->type == ARG)
		{
			if (tmp->is_empty == 1)
				argv[y++] = ft_strdup("");
			else
				argv[y++] = ft_strdup(tmp->str);
		}
		tmp = tmp->next;
	}
	return (argv);
}

/**
 * @brief  return **argv pour execve (ex: "echo bonjour >> out.txt"  
 * 													==> return tab :
 * 													 tab[0]=echo /
 * 													 tab[1]=bonjour)
 * @param cmd 
 * @return char** 
 */
char	**ft_lstcmd_to_cmdarg_for_execve(t_list	*cmd)
{
	char	**argv;
	int		nbword;
	t_list	*tmp;

	nbword = ft_lstsize(cmd);
	argv = ft_calloc(nbword + 1, sizeof(char **));
	tmp = cmd;
	argv = ft_lstcmd_to_cmdarg_for_execve_bis(tmp, argv);
	if (argv[0] == NULL)
		argv[0] = ft_strdup("");
	return (argv);
}
