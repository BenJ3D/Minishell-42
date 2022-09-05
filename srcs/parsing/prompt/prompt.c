/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:45:53 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/05 16:03:02 by bducrocq         ###   ########.fr       */
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
char *prompt_update(void)
{
	char *line;
	
	line = ft_strjoin_max("%s[ %s ]:%s%s%s>$ ",
		GREEN, getenv("LOGNAME"),
		CYAN, getenv("PWD"), NONE_COLOR);
	return (line);
}

void prompt_basic_test(char **av, char **env)
{
	char *buffer;
	char *line;
	pid_t	child;
	
	buffer = NULL;
	line = prompt_update();
	buffer = readline(line);
	while ((buffer))
	{ 
		if (!ft_strncmp(buffer, "ls", 3))
		{
			child = fork();
			if (child == 0)
				execve("/bin/ls", av, env);
			// if (child > 0)
			// 	printf("Child pid = %i\n", child);
			wait(0);
		}
		else if (!ft_strncmp(buffer, "testenv", 8))
		{
			setenv("LOGNAME", "BEN3D", 1); // setenv non autorisé
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
			unlink("adieu"); // supprim un fichier
		}
		else
			printf("%s: command not found\n", buffer);
		free(buffer);
		buffer = NULL;
		free(line);
		line = prompt_update();
		rl_on_new_line();
		buffer = readline(line);
	}
	if (line)
		free(line);
	free(buffer);
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