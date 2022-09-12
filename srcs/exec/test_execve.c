/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_execve.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 16:01:31 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/12 18:53:54 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>

/**
 * @brief utiliser la fonction execve pour lancer prog ls
 * 	particularitées :	Impossible de faire une boucle avec des ls dedans car
 * 			'ls' lance son propre processus et quitte tout quand il se termine 
 * 
 * Solution : Utiliser la fonction fork pour creer des processus enfant
 * 				et ~exécuter les commandes plusieurs fois~
 * 
 * @return id du processus ( Denrier enfant return 0, et parent return son id > 0)
 */
int		test_execve_ls_fork(char **av)
{
	pid_t	father;

	father = fork(); // duplique le processus actuel , return 0 pour le parent et un id superieur à 0 pour le/les enfant(s)
	if (father > 0)
	{
		wait(0); // permet de dire : ok j'attends que mes processus enfants aient terminées leur process avant de faire le printf
		printf("I'M YOUR FATHER || father = %i\n", father);
	}
	if (father == 0)
	{
		printf("I'M YOUR CHILD || father = %i\n", father);
		execve ("/bin/ls", av, NULL); // execute un ls a l'emplacement courant
		perror("minishell"); 
	}
	return (0);
}