/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:50:37 by hmarconn          #+#    #+#             */
/*   Updated: 2022/08/19 17:35:06 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes.h"
# include "define_common.h"

typedef struct s_data
{
}t_data;

/* BASICS */



/* FT TEST */
int		test_execve_ls_fork(char **av);
void basic_prompt();

	/* FT AARTIGES */
	void handler_interative(int signum);
void	interactive_mode(void);

#endif