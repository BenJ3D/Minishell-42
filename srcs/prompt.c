/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:45:53 by bducrocq          #+#    #+#             */
/*   Updated: 2022/08/21 03:36:30 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>
// TODO: faire correspondre les "/path/" du dossier courant comme
// TODO: le vrai bash avec "~/" ==> voir getenv("HOME") et getcwd()
/**
 * @brief met a jour la phrase du pormpt
 *
 * @return char* alloue avec malloc()! ==>> penser a free()
 */
char *update_prompt(void)
{
	char *line;
	
	line = ft_strjoin_max("%s%s@%s:%s%s%s$ ",
		GREEN, getenv("LOGNAME"), getenv("NAME"),
		CYAN, getenv("PWD"), NONE_COLOR);
	return (line);
}

void basic_prompt(char **av, char **env)
{
	char *buffer;
	char *line;
	t_shell	shell;
	
	buffer = NULL;
	line = update_prompt();
	while ((buffer = readline(line)) > 0)
	{
		if (!ft_strncmp(buffer, "ls", 3))
			execve("/usr/bin/ls", av, env);
		else
			printf("cmd = %s\n", buffer);
		free(buffer);
		buffer = NULL;
		free(line);
		line = update_prompt();
	}
	if (line)
		free(line);
	printf("exit\n");
}

// void init_shell(t_shell *shell)
// {
// 	char *buf;
	
// 	buf = NULL;
// 	shell->name = getenv("NAME");
// 	shell->logname = getenv("LOGNAME");
// 	shell->pwd = getcwd(buf, PATH_MAX);
// 	free (buf);
// }