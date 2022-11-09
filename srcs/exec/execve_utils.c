/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 00:32:10 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/09 19:43:59 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

/**
 * @brief return 1 si pipe detecté dans la commande
 * 
 * @param lst 
 * @return int 
 */
int	ft_check_if_cmd_has_pipe(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->type == PIPE)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

/**
 * @brief return type redirection si detecté dans la commande
 * 
 * @param lst 
 * @return int 0 si pas de redirection
 */
int	ft_check_if_cmd_has_redirection(t_list *lst)
{
	t_list	*tmp;

	tmp = lst;
	while (tmp)
	{
		if (tmp->type >= IN1 && tmp->type <= OUT2)
			return (tmp->type);
		tmp = tmp->next;
	}
	return (0);
}

/**
 * @brief check parmit une liste si il y a une builtin
 * 
 * @return int 
 */
int	ft_exec_is_builtin(t_data *data, char **argv, \
												t_cmdtab *cmdtab, t_execarg *ex)
{
	if (*argv == NULL)
		return (-1);
	else if (cmdtab[ex->i].isbuilt == BUILT_CD)
		ft_builtin_cd(data->env, argv, data, 0);
	else if (cmdtab[ex->i].isbuilt == BUILT_ECHO)
		ft_builtin_echo(argv);
	else if (cmdtab[ex->i].isbuilt == BUILT_ENV)
		ft_builtin_env(data->env);
	else if (cmdtab[ex->i].isbuilt == BUILT_EXIT)
		ft_exit(data, argv);
	else if (cmdtab[ex->i].isbuilt == BUILT_EXPORT)
		ft_builtin_export(data->env, argv, data);
	else if (cmdtab[ex->i].isbuilt == BUILT_PWD)
		ft_builtin_pwd(data);
	else if (cmdtab[ex->i].isbuilt == BUILT_UNSET)
		ft_builtin_unset(data, argv);
	return (0);
}

/**
 * @brief		check si argv[0] est une builtin
 * 
 * @return int return 0 if not built-in; else return 1 to 7 builtin type
 */
int	ft_check_is_builtin(t_data *data, char **argv, \
												t_cmdtab *cmdtab, t_execarg *ex)
{	
	if (*argv == NULL)
		return (-1);
	if (!ft_strncmp(argv[0], "cd", 3))
		cmdtab[ex->i].isbuilt = BUILT_CD;
	else if (!ft_strncmp(argv[0], "echo", 5))
		cmdtab[ex->i].isbuilt = BUILT_ECHO;
	else if (!ft_strncmp(argv[0], "env", 4))
		cmdtab[ex->i].isbuilt = BUILT_ENV;
	else if (!ft_strncmp(argv[0], "export", 7))
		cmdtab[ex->i].isbuilt = BUILT_EXPORT;
	else if (!ft_strncmp(argv[0], "unset", 6))
		cmdtab[ex->i].isbuilt = BUILT_UNSET;
	else if (!ft_strncmp(argv[0], "pwd", 4))
		cmdtab[ex->i].isbuilt = BUILT_PWD;
	else if (!ft_strncmp(argv[0], "exit", 5))
		cmdtab[ex->i].isbuilt = BUILT_EXIT;
	else
		cmdtab[ex->i].isbuilt = NO_BUILTIN;
	return (cmdtab[ex->i].isbuilt);
}

pid_t	ft_createfork(t_data *data, t_execarg *ex, char **envp)
{
	pid_t	father;
	char	*errline;

	father = fork();
	if (father == -1)
	{
		errline = ft_strjoin_max("%s%s: %s%s%s", COLOR_CYAN, \
			data->pgr_name, COLOR_PURPLE, "fork", COLOR_RED);
		perror(errline);
		free (errline);
		free(ex->progpath);
		ft_free_tab_char(ex->argv);
		ft_free_tab_char(envp);
		exit(errno);
	}
	return (father);
}
