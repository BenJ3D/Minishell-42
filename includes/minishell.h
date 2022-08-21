/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:50:37 by hmarconn          #+#    #+#             */
/*   Updated: 2022/08/20 23:48:59 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include "define_common.h"
# include "includes.h"
# include "struct.h"


/* FT TEST */
int		test_execve_ls_fork(char **av);
void	basic_prompt();

	/* FT AART */
void	handler_interative(int signum);
void	interactive_mode(void);

#endif