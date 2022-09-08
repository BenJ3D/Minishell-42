/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:12:46 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/08 11:28:36 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

//TODO: faire le split env

int	main(int ac, char **av, char **envp)
{
	char **env;
	t_data	data;
	
	if (ac > 1)
	{
		ft_putstr_fd(av[0], 2);
		ft_putstr_fd(" to many arguments\n", 2);
		return (1);
	}
	interactive_mode(); //FIXME: ft pomper, la modifier / ameliorer
	
	ft_env_init_lst(envp, &data);

	// ft_builtin_env(data.env);
	
	// env = ft_env_init(envp);
	// env_test_read(envp, "USER");
	// env = ft_env_convert_envlst_to_tab(data.env);
	// env_test_read(env, "USER");

	// for (int n = 0; env[n]; n++)
	// {
	// 	printf("%i/%i\n", n + 1, ft_env_lstsize(data.env));
	// }

	
	// ft_builtin_env(env);
			// char **tabexport = ft_calloc(3, sizeof(tabexport));

			// tabexport[0] = ft_strdup("export");
			// tabexport[1] = ft_strdup("45=export");
			
			// ft_builtin_export(data.env, tabexport);
	
	prompt_basic_test(av, &data);
	return (0);
}


// int	main(int ac, char **av, char **envp)
// {
// 	if (ac > 1)
// 	{
// 		ft_putstr_fd(av[0], 2);
// 		ft_putstr_fd(" to many arguments\n", 2);
// 		return (1);
// 	}
// 	//  test_execve_ls_fork(av);
// 	// ft_putstr_fd("test fonction readline\n", 1);
// 	// char *buffer = NULL;
// 	// buffer = readline("");
// 	// printf("%s\n", buffer);
// 	// free(buffer);

// 	//TEST RECUP ENV ARG
// 	// char *env_path = getenv("LOGNAME");
// 	// printf("LOGNAME =%s\n", env_path);
// 	// char buf[PATH_MAX];
// 	// printf("PWD =%s\n", getcwd(buf, PATH_MAX));
	
// 	// char *buf;
// 	// printf("pwd =%s\n", getcwd(buf, PATH_MAX));
// 	// free(buf);
	

// 	// interactive_mode();

// 	// char *nline = NULL;

// 	// nline = ft_strjoin_max("%s%s@%s:%s%s%s$ ", \
// 	// 	GREEN, getenv("LOGNAME"),getenv("NAME"), \
// 	// 	CYAN,	getenv("PWD"), NONE_COLOR);
// 	// ft_putstr(nline);
// 	// free(nline);

// 	// env_test_read(env, "LOGNAME");
// 	char **env;
// 	int	i;

// 	i = 0;
// 	env = ft_env_init(envp);
// 	env_test_read(env, "USER");
// 	// while(envp[i])
// 	// {
// 	// 	printf("%s\n", envp[i++]);
// 	// }
// 	// printf("%s\n", envp[8]);
// 	prompt_basic_test(av, envp);
// 	// env_test_read(env, "PATH");

// 	// ft_free_all_array(env);
// 	return (0);
// }

