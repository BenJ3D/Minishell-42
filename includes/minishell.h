/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:50:37 by hmarconn          #+#    #+#             */
/*   Updated: 2022/09/11 00:15:00 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include "define_common.h"
# include "includes.h"
# include "struct.h"

/* FT TEST */
int			test_execve_ls_fork(char **av);
void		prompt_basic_test(char **av, t_data *data);
int			env_test_read(char **env, const char *key);


/* FT PARSING */


/* FT BUILTIN */
void		ft_builtin_env(t_envlst *envlst);
int			ft_builtin_export(t_envlst *env, char **cmd);
int			ft_builtin_unset(t_envlst *env, char **cmd);


/* FT ENV */
char		**ft_env_init(char **envp);
char		*ft_env_extract_key_name(char *str);
char		*ft_env_extract_value_content(char *str);
char		*ft_env_getstr_env_value(t_envlst *env, const char *key);
int			ft_env_check_if_key_is_valid(t_envlst *env, char *key);
t_envlst	*ft_env_getenv_lst_value(t_envlst *env, char *key);

/* FT ENV LIST */
void		ft_env_init_lst(char **envp, t_data *data);
t_envlst	*ft_env_lstnew(char *key, char *value);
void		ft_env_lstadd_front(t_envlst **alst, t_envlst *new);
void		ft_env_lstadd_back(t_envlst **alst, t_envlst *new);
void		ft_env_lstdelone(t_envlst *lst);
void		ft_env_lstclear(t_envlst **lst);
t_envlst	*ft_env_lstlast(t_envlst *lst);
int			ft_env_lstsize(t_envlst *lst);
char		**ft_env_convert_envlst_to_tab(t_envlst *env);
void		ft_env_lstclear_one(t_envlst **lst);

/* FT AART */
void		handler_interative(int signum);
void		interactive_mode(void);

#endif