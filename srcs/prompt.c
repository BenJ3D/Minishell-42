/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:45:53 by bducrocq          #+#    #+#             */
/*   Updated: 2022/08/21 00:15:21 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

char *ft_add_cwd(char *line, const char *path)
{
	char *buf;
	char *new_line;

	new_line = ft_strjoin(line, path);
	free(line);
	return (new_line);
}

void init_shell(t_shell *shell)
{
	char *buf;
	
	buf = NULL;
	shell->name = getenv("NAME");
	shell->logname = getenv("LOGNAME");
	shell->pwd = getcwd(buf, PATH_MAX);
	free (buf);
}

//TODO: faire un join (ft_str_join_max  dans libft) plus evolué qui free line
char *update_prompt(t_shell *shell)
{
	char *line;
	char *tmp;
	
	init_shell(shell);
	tmp = ft_strjoin( GREEN, shell->logname);
	line = ft_strdup(tmp);
	free(tmp);
	tmp = ft_strjoin(shell->logname, "@");
	line = ft_strdup(tmp);
	free(tmp);
	tmp = ft_strjoin(line, shell->name);
	free(line);
	line = ft_strdup(tmp);
	free(tmp);
	tmp = ft_strjoin(line, ":");
	free(line);
	line = ft_strdup(tmp);
	free(tmp);
	line = ft_add_cwd(line, shell->pwd);
	return (line);
}

// char	*ft_create_prompt_rl(shell)
// {

// 	return (0);
// }

void basic_prompt()
{
	char *buffer;
	char *line;
	t_shell	shell;
	
	buffer = NULL;
	line = update_prompt(&shell);
	while ((buffer = readline(line)) > 0)
	{
		printf("cmd = %s\n", buffer);
		free(buffer);
		buffer = NULL;
	}
	printf("exit\n");
}