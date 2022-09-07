/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:45:53 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/08 00:40:21 by bducrocq         ###   ########.fr       */
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
char *prompt_update(t_envlst *env)
{
	char *line;
	
	line = ft_strjoin_max("%s- %s -%s ~MiniHell~>%s$ ",
		GREEN, ft_env_getenv(env ,"USER"),
		CYAN, NONE_COLOR);
	// line = ft_strjoin_max("%s%s:%sMiniHell%s$> ",
	// 	GREEN, getenv("USER"),
	// 	CYAN, NONE_COLOR);
	return (line);
}

/**
 * @brief ft coder en dur pour tests prog
 * 
 * @param av 
 * @param env 
 */
void prompt_basic_test(char **av, t_data *data)
{
	char *buffer;
	char *line;
	pid_t	child;
	
	buffer = NULL;
	line = prompt_update(data->env);
	buffer = readline(line);
	while ((buffer))
	{ 
		if (!ft_strncmp(buffer, "ls", 3))
		{
			child = fork();
			if (child == 0)
				execve("/bin/ls", av, NULL); //TODO:TODO:
			//if (child > 0)
			//	printf("Child pid = %i\n", child);
			wait(0);
		}
		else if (!ft_strncmp(buffer, "env", 4))
		{
			ft_builtin_env(data->env);
		}
		else if (!ft_strncmp(buffer, "export", 7))
		{
			char **tabexport = ft_calloc(3, sizeof(tabexport));

			tabexport[0] = ft_strdup("export");
			tabexport[1] = ft_strdup("=export");
			
			ft_builtin_export(data->env, tabexport);
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
			unlink("adieu"); // supprime un fichier
		}
		else
			printf("%s: command not found\n", buffer);
		free(buffer);
		buffer = NULL;
		free(line);
		line = prompt_update(data->env);
		rl_on_new_line();
		buffer = readline(line);
	}
	if (line)
		free(line);
	free(buffer);
	rl_on_new_line();
	write(2, "exit\n", 6);
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