/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:50:37 by hmarconn          #+#    #+#             */
/*   Updated: 2022/09/06 23:57:37 by bducrocq         ###   ########.fr       */
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
void	ft_show_all_environnement_key(char **env);


/* FT ENV LIST */
char	**ft_create_tab_with_envlst(t_envlst *env);
void	ft_display_all_env_lst(t_envlst *envlst);
void	ft_env_init_lst(char **envp, t_data *data);
t_envlst	*ft_env_lstnew(char *key, char *value);
void	ft_env_lstadd_front(t_envlst **alst, t_envlst *new);
void	ft_env_lstadd_back(t_envlst **alst, t_envlst *new);
void	ft_env_lstdelone(t_envlst *lst);
void	ft_env_lstclear(t_envlst **lst);
t_envlst	*ft_env_lstlast(t_envlst *lst);
int		ft_env_lstsize(t_envlst *lst);


void	ft_free_all_array(char **env);

	/* FT AART */
void	handler_interative(int signum);
void	interactive_mode(void);

#endif