/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:50:37 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/18 14:51:47 by hmarconn         ###   ########.fr       */
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

/* FT MINISHELL */
void		prompt_minishell(char **av, t_data *data);

/* FT PARSING */
int			ft_parsing_prompt(t_data *data, char *buffer);
char		**ft_lstcmd_to_cmdarg_for_execve(t_list	*cmd);
int			ft_count_pipe(t_data	*data, char *buffer);
void		ft_quotes_checker(t_data	*data, char	*str, int i);
int			ft_full_prompt_quote_check(t_data	*data, char	*buffer);
void		ft_reset_quotes_checker(t_data	*data);
int			ft_node_quote_checker(t_data	*data);
t_list		*ft_total_parsing(t_data	*data, char	*buffer);
/*PARSING TESTS*/
char		*ft_strjoin_parsing(char	*s1, char *s2);
int			ft_strlen_parsing(char	*str);
t_list		*ft_buffercmd_in_lst(char *buffer, t_list	*cmd, t_data	*data);
t_list		*ft_buffercmd_in_lst_quotes(char *buffer, t_list	*cmd, t_data	*data);

/* FT EXECVE */
int			ft_run_execve(t_cmdtab *cmdtab, t_data *data);
int			ft_command_not_found_message(char **argv, t_data *data);
int			ft_check_is_builtin(t_data	*data, char **argv,t_cmdtab *cmdtab, t_execarg *ex);
int			ft_exec_is_builtin(t_data	*data, char **argv,t_cmdtab *cmdtab, t_execarg *ex);

/* FT EXECVE UTILS*/
int			ft_check_if_cmd_has_pipe(t_list *lst);

/* FT BUILTIN */
void		ft_builtin_env(t_envlst *envlst);
int			ft_builtin_export(t_envlst *env, char **cmd, t_data	*data);
int			ft_builtin_unset(t_data *data, char **cmd);
int			ft_builtin_cd(t_envlst *env, char **argv);
int			ft_builtin_pwd(t_envlst *env, char **argv);
int			ft_builtin_echo(char **argv);
void		ft_exit(t_data *data);
void		ft_exit_child(t_data *data);



/* FT ENV */
char		**ft_env_init(char **envp);
char		*ft_env_getstr_env_value(t_envlst *env, const char *key);
int			ft_env_check_if_key_is_valid(t_envlst *env, char *key);
t_envlst	*ft_env_getenv_lst_value(t_envlst *env, char *key);
int			ft_env_check_if_key_exist(t_envlst *env, char *key);
char		**ft_env_convert_envlst_to_tab(t_envlst *env);
char		*ft_env_extract_key_name(char *str, int *isenv);
char		*ft_env_extract_value_content(char *str);
int			ft_shlvl_increment(t_envlst *env);

/* FT ENV LIST */
t_envlst	*ft_env_lstnew(char *key, char *value, int isenv);
t_envlst	*ft_env_lstlast(t_envlst *lst);
int			ft_env_lstsize(t_envlst *lst);
void		ft_env_init_lst(char **envp, t_data *data);
void		ft_env_lstadd_front(t_envlst **alst, t_envlst *new);
void		ft_env_lstadd_back(t_envlst **alst, t_envlst *new);
void		ft_env_lstdelone(t_envlst *lst);
void		ft_env_lstclear(t_envlst **lst);
void		ft_env_lstclear_one(t_envlst **lst);
void		ft_env_lstclear_one_first_element(t_envlst **lst);

/* FT LIST */
void		ft_lstadd_back(t_list **alst, t_list *new);
t_list		*ft_lstnew(char *str);
t_list		*ft_lstlast(t_list *lst);
int			ft_lstsize(t_list *lst);
void		ft_lstdelone(t_list *lst);
void		ft_lstclear(t_list **lst);

/* FT FREE */
int			ft_free_cmdtab_lst(int pipe, t_cmdtab *cmdtab);
void		ft_free_all_minishell(t_data *data);
void		ft_free_tab_char(char **tab);

/* FT DEBUG BEN */
void		dbg_lstdisplay(t_list *lst);
void		dbg_lstdisplay_color(t_list *lst);
void		dbg_lstdisplay_color_type(t_list *lst);
void		dbg_display_cmdtab(t_cmdtab *cmdtab);
void		dbg_display_argv(char **argv);

/* FT DEBUG BEN A VIRER */
void		dbg_fork_display_pid(const char *str); //TODO: FIXME:

/* FT AART */
void		handler_interative(int signum);
void		interactive_mode(void);

#endif