/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:12:46 by bducrocq          #+#    #+#             */
/*   Updated: 2022/06/21 18:14:12 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <../includes/minishell.h>

int	main(int ac, char **av, char **env)
{
	printf("Hello World!\n");
	test_execve_ls_fork(av);
	ft_putstr("Test libft !\n");
	return (0);
}
