/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:45:53 by bducrocq          #+#    #+#             */
/*   Updated: 2022/08/19 18:22:18 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

void basic_prompt()
{
	char *buffer;

	buffer = NULL;
	write(1, "miniHelle v0.1 $> ", 19);

	while ((buffer = readline("")) > 0)
	{
		printf("cmd = %s\n", buffer);
		write(1, "miniHelle v0.1 $> ", 19);
		free(buffer);
		buffer = NULL;
	}
	printf("Bye \n");
}