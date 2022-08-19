/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:12:46 by bducrocq          #+#    #+#             */
/*   Updated: 2022/08/19 17:48:05 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

//TODO: use readline to prompt
int	main(int ac, char **av, char **env)
{
	if (ac > 1)
	{
		ft_putstr_fd(av[0], 2);
		ft_putstr_fd(" to many arguments\n", 2);
		return (1);
	}
	// test_execve_ls_fork(av);
	// interactive_mode();
	ft_putstr_fd("test fonction readline\n", 1);
	char *buffer = NULL;
	readline(buffer);
	printf("%s\n", buffer);
	// basic_prompt();

	return (0);
}