/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:12:46 by bducrocq          #+#    #+#             */
/*   Updated: 2022/08/21 02:25:12 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

int	main(int ac, char **av, char **env)
{
	if (ac > 1)
	{
		ft_putstr_fd(av[0], 2);
		ft_putstr_fd(" to many arguments\n", 2);
		return (1);
	}
	//  test_execve_ls_fork(av);
	// ft_putstr_fd("test fonction readline\n", 1);
	// char *buffer = NULL;
	// buffer = readline("");
	// printf("%s\n", buffer);
	// free(buffer);

	//TEST RECUP ENV ARG
	// char *env_path = getenv("LOGNAME");
	// printf("LOGNAME =%s\n", env_path);
	// char buf[PATH_MAX];
	// printf("PWD =%s\n", getcwd(buf, PATH_MAX));
	
	// char *buf;
	// printf("pwd =%s\n", getcwd(buf, PATH_MAX));
	// free(buf);
	

	// interactive_mode();
	basic_prompt();

	char *nline = NULL;

	nline = ft_strjoin_max("-- %s -- %s", "NULL", "Hello");
	ft_putstr(nline);
	free(nline);

	return (0);
}