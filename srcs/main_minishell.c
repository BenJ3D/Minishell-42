/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/06/20 18:01:19 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

int	main(int ac, char **av, char **env)
{
	printf("Hello World!\n");
	test_execve_ls_fork(av);

	return (0);
}
