/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:50:37 by hmarconn          #+#    #+#             */
/*   Updated: 2022/09/06 20:04:44 by bducrocq         ###   ########.fr       */
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
char	*ft_env_extract_key_name(char *str);
char	*ft_env_extract_value_content(char *str);
int		ft_env_count_keys(char **envp);
void	ft_show_all_environnement_key(char **env);

/* FT ENV LIST */
void	ft_env_init_lst(char **envp, t_data *data);
t_env	*ft_env_lstnew(char *key, char *value);
void	ft_env_lstadd_front(t_env **alst, t_env *new);
void	ft_env_lstadd_back(t_env **alst, t_env *new);
void	ft_env_lstdelone(t_env *lst);
void	ft_env_lstclear(t_env **lst);
t_env	*ft_env_lstlast(t_env *lst);


void	ft_free_all_array(char **env);

	/* FT AART */
void	handler_interative(int signum);
void	interactive_mode(void);

#endif