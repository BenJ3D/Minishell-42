/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:12:46 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/09 00:50:09 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

static void	ft_init_minishell(t_data *data)
{
	data->pgr_name = ft_strdup("MiniHell");
}


int	main(int ac, char **av, char **envp)
{
	t_data	data;

	if (ac > 1)
	{
		ft_putstr_fd(av[0], 2);
		ft_putstr_fd(" to many arguments\n", 2);
		return (1);
	}
	interactive_mode (); //FIXME: pomper sur un autre minishell, a modifier 
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


////////////////////PIPE TEST /////////////////////
	// printf("%sPIPE TEST : ls -all | cat -e | cat -e %s\n", COLOR_RED, COLOR_CYAN);
	// int		fd1[2];
	// int		fd2[2];
	// int		fd3[2];
	
	// pipe(fd1);
	// pipe(fd2);
	
	// int pid1 = fork();
	
	// if (pid1 == 0)
	// {
	// 	// close(fd2[0]);
	// 	// close(fd2[1]);
	// 	dup2(fd1[1],1); 
	// 	close(fd1[1]);
	// 	execlp("ls", "ls", "-all", NULL);
	// 	exit(0);
	// }
	// 	close(fd1[1]);

	// int pid2 = fork();
	
	// if (pid2 == 0)
	// {
	// 	dup2(fd1[0], 0); // in
	// 	close(fd1[0]);
	// 	dup2(fd2[1], 1); //out
	// 	execlp("cat", "cat", "-e", NULL);
	// 	exit(0);
	// }
	
	// 	close(fd2[1]);
	
	// int pid3 = fork();
	
	// if (pid3 == 0)
	// {
	// 	dup2(fd2[0], 0);
	// 	close(fd2[0]);
	// 	execlp("cat", "cat", "-e", NULL);
	// 	exit(0);
	// }

	// close(fd1[0]);
	// close(fd1[1]);
	// close(fd2[0]);
	// close(fd2[1]);
	
	// waitpid(pid1, NULL, 0);
	// waitpid(pid2, NULL, 0);
	// waitpid(pid3, NULL, 0);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
	ft_init_minishell(&data);
	ft_env_init_lst(envp, &data);
	prompt_minishell(av, &data);
	//  prompt_basic_test(av, &data);
	ft_exit(&data);
	return (0);
}



