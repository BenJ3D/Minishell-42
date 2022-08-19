/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:45:53 by bducrocq          #+#    #+#             */
/*   Updated: 2022/08/19 17:45:12 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void basic_prompt()
{
	char *buffer = NULL;
	size_t buf_size = 2048;

	write(1, "$> ", 3);

	while (readline(buffer) > 0)
	{
		printf("cmd = %s\n", buffer);
		write(1, "$> ", 3);
	}
	// while (getline(&buffer, &buf_size, stdin) > 0)
	// {
	// 	printf("cmd = %s\n", buffer);
	// 	write(1, "$> ", 3);
	// }

	printf("Bye \n");
	free(buffer);
}