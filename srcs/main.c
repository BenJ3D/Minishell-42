/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:12:46 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/10 21:53:15 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

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
	interactive_mode(); //FIXME: pomper sur un autre minishell, a modifier 
														// ameliorer
	
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//////////////////////////      ZONE TEST     //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	
	// for(int i=0; envp[i]; i++)
	// {
	// 	printf("env[i]:%s\n", envp[i]);
	// }
	
	// char *str = getcwd(NULL, PATH_MAX);
	// printf("%s\n", str);
	
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

	ft_env_init_lst(envp, &data);
	// t_envlst **tmp;
	
	// tmp = ft_env_getenv_lst_value(data.env, "LOGNAME");
	// ft_env_check_if_key_is_valid(data.env, "USER");
	
	prompt_basic_test(av, &data);
	ft_env_lstclear(&data.env);
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

