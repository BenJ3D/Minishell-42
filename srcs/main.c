/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:12:46 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/28 20:58:11 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

static void	ft_init_minishell(t_data *data)
{
	data->pgr_name = ft_strdup("MiniHell");
	data->s_quotes_switch = 0;
	data->d_quotes_switch = 0;
	data->savefd[0] = dup(STDIN_FILENO);
	data->savefd[1] = dup(STDOUT_FILENO);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	// if (ac > 1)
	// {
		// ft_putstr_fd(av[0], 2);
		// ft_putstr_fd(" to many arguments\n", 2);
		// return (1);
	// }

	interactive_mode (); //FIXME: pompe sur un autre minishell, a modifier 
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


///////////////////////////////  PIPE TEST /////////////////////////////////////
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

///////////////////////////////  HEREDOCS TEST /////////////////////////////////
	// int		p[2];
	// int		hdc_fd;
	// char	buffer[BUFFER_SIZE];
	// // char hdc_path[] = PATH_HEREDOC;
	// char buf[1];
	// pid_t fat;
	
	// hdc_fd = open(PATH_HEREDOC, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	// fat = fork();
	// if (fat == 0)
	// {
	// 	ft_heredoc_create("EOL", hdc_fd);
	// 	exit (0);
	// }
	// waitpid(fat, NULL, 0);
	// close(hdc_fd);
	// hdc_fd = open(PATH_HEREDOC, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	// fat = fork();
	// if (fat == 0)
	// {
	// 	ft_heredoc_create("out", hdc_fd);
	// 	exit (0);
	// }
	// waitpid(fat, NULL, 0);
	// close(hdc_fd);
	// hdc_fd = open(PATH_HEREDOC, O_CREAT | O_RDONLY);

	// fat = fork();
	// if (fat == 0)
	// {
	
	// 	ft_redi_in1v2(hdc_fd);
	// 	ft_putstr_fd("Start cat -e\n", 2);
	// 	execlp("/bin/cat", "cat", "-e", NULL);
	// 	exit(0);
	// }
	
	// waitpid(fat, NULL, 0);
	// ft_putstr("TEST heredocs pipe\n");
	// unlink(PATH_HEREDOC);

	

	// execve("./srcs", NULL, envp); //TODO:
	// perror("minishell");

	// char *test;

	// test = NULL;
	// free (test);

////////////////////////////////  ERRNO TEST  //////////////////////////////////
	// errno = 0;
	// g_status = errno;
	// ft_putnbr(g_status);
	// puts("\n");
	// pid_t pid = fork();
	// if (pid == 0)
	// {
	// 	errno = 42;
	// 	ft_putnbr(errno);
	// 	puts("\nend of child\n");
	// 	exit(39);
	// }
	// waitpid(pid, &g_status, 0);
	// ft_putnbr(g_status % 255);
	// puts("\n");

///////////////////////////////  HEREDOCS TEST /////////////////////////////////
	// int p[2];
	// int	b;
	// pid_t fat[4];

	// b = 0;
	// pipe(p);
	// fat[0] = fork();
	// if (fat[0] == 0) // = child process
	// {
	// 	close(p[0]);
	// 	ft_putstr_fd("Bien le bonjour\n", p[1]);
	// 	close(p[1]);
	// 	exit(0);
	// }
	// fat[1] = fork();
	// if (fat[1] == 0) // = child process
	// {
	// 	close(p[1]);
	// 	dup2(p[0], STDIN_FILENO);
	// 	execlp("/bin/cat", "cat", "-e", NULL);
	// 	perror("minishell");
	// 	exit(errno);
	// }
	
	// close(p[0]);
	// close(p[1]);
	// waitpid(fat[0], NULL, 0);
	// aitpid(fat[1], NULL, 0);
	// rintf("toute chose a une fin\n");

	char *tocmp = ft_strdup("PWD22"); 
	char *tocmp2 = ft_strdup("PWD2");
	int sizecmp = ft_strlen(tocmp);
	int ret;
	ret = ft_strncmp(tocmp, tocmp2, sizecmp); // si ret > 0 == tocmp > tocmp2 
	printf("ret = %i\n", ret);
	
		


	// exit(0);
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
	// puts("start minishell ");
	// dbg_display_errno();

	
	ft_init_minishell(&data);
	ft_env_init_lst(envp, &data);
	prompt_minishell(av, &data);
	ft_exit(&data);
	return (0);
}
