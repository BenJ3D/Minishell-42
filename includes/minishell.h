/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:50:37 by hmarconn          #+#    #+#             */
/*   Updated: 2022/08/30 15:31:52 by bducrocq         ###   ########.fr       */
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
void	prompt_basic_test(char **av, char **env);
int		env_test_read(char **env, const char *key);

/* FT ENV */
char	**ft_env_init(char **envp);
char	*ft_env_return_key(char **env, char *key);
int		ft_env_count_keys(char **envp);
void	ft_free_all_array(char **env);

	/* FT AART */
void	handler_interative(int signum);
void	interactive_mode(void);

#endif