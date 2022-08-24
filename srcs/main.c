/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:12:46 by bducrocq          #+#    #+#             */
/*   Updated: 2022/08/24 22:36:17 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>


int env_test_read(char **env, const char *key)
{
	char	*value;
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	while (ret = ft_strncmp(env[i], key, ft_strlen(key)))
	{
		printf("i %i ||  ret = %i || key = %s || val = %s------------\n", i, ret, key, env[i]);
		i++;
	}
	value = ft_strdup(env[i]);
	printf("env %s : %s", key, value);
	free (value);
	// env[i][3] = 'Q';
	return (i);
}

char	*ft_env_return_key(char **env, char *key)
{
	
	return (NULL);
}


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

	// char *nline = NULL;

	// nline = ft_strjoin_max("%s%s@%s:%s%s%s$ ", \
	// 	GREEN, getenv("LOGNAME"),getenv("NAME"), \
	// 	CYAN,	getenv("PWD"), NONE_COLOR);
	// ft_putstr(nline);
	// free(nline);

	env_test_read(env, "LOGNAME");
	prompt_basic_test(av, env);

	
	
	
	return (0);
}

