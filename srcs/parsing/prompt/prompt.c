/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:45:53 by bducrocq          #+#    #+#             */
/*   Updated: 2022/08/24 13:56:41 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>
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
	pid_t	child;
	
	buffer = NULL;
	line = update_prompt();
	while ((buffer = readline(line)) > 0)
	{
		if (!ft_strncmp(buffer, "ls", 3))
		{
			child = fork();
			if (child == 0)
			{
				execve("/usr/bin/ls", av, env);
			}
			wait(0);
		}
		else if (!ft_strncmp(buffer, "testenv", 8))
		{
			setenv("LOGNAME", "BEN3D", 1);
			printf("LOGNAME = %s\n", getenv("LOGNAME"));
		}
		else if (!ft_strncmp(buffer, "testcd", 8))
		{
			setenv("PWD", "/home/ben/projet/", 1);
			printf("PWD = %s\n", getenv("PWD"));
			printf("OLDPWD = %s\n", getenv("OLDPWD"));
		}
		else if (!ft_strncmp(buffer, "pwd", 8))
		{
			printf("%s\n", getenv("PWD"));
		}
		else if (!ft_strncmp(buffer, "rmm", 8))
		{
			unlink("adieu");
		}
		else
			printf("%s: command not found\n", buffer);
		free(buffer);
		buffer = NULL;
		free(line);
		line = update_prompt();
		rl_on_new_line();
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