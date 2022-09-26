/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:12:46 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/27 01:33:33 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

static void	ft_init_minishell(t_data *data)
{
	data->pgr_name = ft_strdup("~MiniHell~");
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

	// int		fd[2];
	// pipe(fd);
	// int pid1 = fork();
	
	// if (pid1 == 0)
	// {
	// 	dup2(fd[1], STDOUT_FILENO);
	// 	close(fd[1]);
	// 	close(fd[0]);
	// 	execlp("ls", "ls", "-all", NULL);
	// 	exit(0);
	// }

	
	// waitpid(pid1, NULL, 0);
	// int pid2 = fork();
	
	// if (pid2 == 0)
	// {
	// 	dup2(fd[0], STDIN_FILENO);
	// 	close(fd[1]);
	// 	close(fd[0]);
	// 	execlp("cat", "cat", "-e", NULL);
	// 	exit(0);
	// }

	// close(fd[0]);
	// close(fd[1]);
	
	// waitpid(pid2, NULL, 0);

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



