/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:50:37 by hmarconn          #+#    #+#             */
/*   Updated: 2022/11/11 23:27:20 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libs/libft/libft.h"
# include "define_common.h"
# include "includes.h"
# include "struct.h"

int	g_status;

/* FT MINISHELL */
void		prompt_minishell(t_data *data);

/* FT PARSING */
int			ft_parsing_prompt(t_data *data, char *buffer);
char		**ft_lstcmd_to_cmdarg_for_execve(t_list	*cmd);
int			ft_count_pipe(t_data	*data, char *buffer);
void		ft_quotes_checker(t_data	*data, char	*str, int i);
int			ft_full_prompt_quote_check(t_data	*data, char	*buffer);
void		ft_reset_quotes_checker(t_data	*data);
int			ft_node_quote_checker(t_data	*data);
int			ft_total_parsing(t_data	*data, char	*buffer);
t_cmdtab	*ft_create_tab_per_cmd(t_list *lst, int nbrpipe);
int			ft_define_cmd_type(t_list *lst, t_data	*data);
t_list		*ft_cft_prime(t_list *tmp);
t_list		*ft_cmd_first_type(t_data	*data, t_list	*tmp);
/*PARSING TESTS*/
void		ft_buffercmd_in_lst(char *buffer, t_data *data, int heavy, \
																int is_empty);
void		ft_buffercmd_in_lst_quotes(char *buffer, t_data *data, int heavy, \
																int is_empty);
int			ft_pipes_spaces_check(char *buffer);
int			ft_redirect_me_now(t_data *data, char *buffer);
int			ft_parsing_for_a_pipe(t_data *data, char *buffer);
char		*ft_var_no_env(t_data	*data, char	*buffer);
void		free_the_birds(t_data	*data);
void		ft_dct_data_reload(t_data	*data);
/*PARSING_OTHERS*/
int			ft_pa_others(t_data	*data, char	*buffer);
char		*ft_pa_others_normal(t_data	*data, char	*buffer, int len);
char		*ft_pa_others_normal_env(t_data	*data, char	*buffer, \
	char	*semi_final);
char		*ft_parsing_others_not_normal_env(t_data	*data, char	*buffer, \
	char	*semi_final);
void		ft_parsing_others_final(t_data	*data, char	*final);
char		*ft_parsing_make_final(char	*semi_final, char	*final);
void		ft_parsing_others_set_quotes(t_data	*data, char	*buffer);
int			ft_pa_others_len(t_data	*data, char	*buffer);
char		*ft_pa_others_existing_quotes(t_data	*data, char	*buffer, \
	char	*semi_final);
void		ft_parsing_others_setings(t_data *data, char *buffer, int choice);
/*PARSING_QUOTES*/
char		*ft_quotes(t_data	*data, char	*buffer);
char		*ft_double_quotes_env(t_data *data, char *buffer, char *semi_final);
char		*ft_dq_specials(t_data	*data, char	*buffer, char	*semi_final, \
	char	*final);
char		*ft_dq_get_env(t_data	*data, char	*buffer, char	*semi_final, \
	char	*final);
char		*ft_pa_dq_env(t_data	*data, char	*buffer, char	*semi_final, \
	int len);
char		*ft_pa_fill_value(t_data	*data, char	*buffer, int len);
char		*ft_pq_dq_env_final(char	*semi_final, char	*value_env);
char		*ft_pa_dq_env_bis(t_data	*data, char	*value_env);
char		*ft_padq_env_digits(t_data	*data, char	*semi_final, \
	char	*buffer);
char		*ft_padq_env_code_error(t_data	*data, char	*semi_final);
/*PARSING_UTILS*/
char		*ft_strjoin_parsing(char	*s1, char *s2);
int			ft_define_cmd_type_during_parsing(t_list *lst, t_data *data);
int			ft_strlen_next_word_quotes(char *str);
int			ft_strlen_next_word(char *str);
int			ft_strlen_parsing(char	*str);
/*PARSING_SPECIALS*/
int			ft_redirection_files_check(char *buffer);
/*PARSING_ENV*/
char		*ft_parsing_env_variable(t_data	*data, char	*buffer);
char		*ft_pa_env_regular_prime(t_data	*data, char	*buffer, int len, \
	int pin);
char		*ft_pa_env_positive_len(t_data	*data, char	*buffer, int len, \
	int pin);
char		*ft_pa_env_regular_len(t_data	*data, char	*buffer, int len, \
	int pin);
char		*ft_pa_env_regular_bis(t_data	*data, char *value_env);
void		ft_pa_env_set(t_data	*data);

/* FT EXECVE */
int			ft_run_execve(t_cmdtab *cmdtab, t_data *data);
int			ft_run_execve2_norm(t_cmdtab *cmdtab, t_execarg *ex);
int			ft_command_not_found_message(char **argv, t_data *data);
int			ft_check_is_builtin(char **argv, t_cmdtab *cmdtab, t_execarg *ex);
int			ft_exec_is_builtin(t_data *data, char **argv,
				t_cmdtab *cmdtab, t_execarg *ex);
int			ft_redirection(t_data *data, t_cmdtab *cmdtab, t_execarg *ex);
int			ft_close_all_fdredi(t_cmdtab *cmdtab, t_execarg *ex);
int			ft_heredoc_init(t_cmdtab *cmdtab);
char		*ft_cmdtab_cmdstr_if_has_cmd(t_cmdtab *cmdtab, t_execarg *ex);
int			ft_forkexe(t_data *data, t_execarg *ex, t_cmdtab *cmdtab);
pid_t		ft_createfork(t_data *data, t_execarg *ex);
char		*ft_check_if_prog_exist_in_pathenv(char *prognam, t_envlst *envlst);
void		ft_execve_clear_hdcfd(t_execarg *ex, t_cmdtab *cmdtab);
int			ft_run_execve_init(t_cmdtab *cmdtab, t_execarg *ex);
int			ft_parent_waitpid(t_cmdtab *cmdtab);
int			ft_cmdtab_has_cmd(t_cmdtab *cmdtab, int i);
int			ft_run_execve_init_patchcmd(t_cmdtab *cmdtab);
void		ft_exit_exit(t_data *data);

/* FT EXECVE  STAT*/
int			ft_stat_check(t_cmdtab *cmdtab, t_execarg *ex,
				t_data *data, char *str);
void		ft_stat_error_is_dir(t_data *data, t_cmdtab *cmdtab, \
													t_execarg *ex, char *cmd);

/* FT EXECVE PIPES */
int			ft_forkexe_dup_if_pipes(t_cmdtab *cmdtab, t_execarg *ex);
int			ft_forkexe_father_close_pipes(t_cmdtab *cmdtab, t_execarg *ex);
int			ft_pipe_init_cmdtab_pipe_in_out(t_cmdtab *cmdtab);
int			ft_create_pipe(t_cmdtab *cmdtab, t_execarg *ex);
int			ft_close_pipe(t_cmdtab *cmdtab, t_execarg *ex);

/* FT EXECVE UTILS*/
int			ft_check_if_cmd_has_pipe(t_list *lst);
int			ft_check_if_cmd_has_redirection(t_list *lst);
int			ft_check_if_cmd_has_a_backslash(char *str);

/* FT REDIRECTIONS*/
int			ft_heredoc_create(char *token, int fd);
int			ft_dupredi(t_data *data, t_cmdtab *cmdtab, t_execarg *ex);
int			ft_redi_out1(t_cmdtab *cmdtab, t_execarg *ex, t_data *data);
int			ft_redi_out2(t_cmdtab *cmdtab, t_execarg *ex, t_data *data);
int			ft_redi_in1(t_cmdtab *cmdtab, t_execarg *ex, t_data *data);
int			ft_redi_in2(int hdc_fd, t_cmdtab *cmdtab, t_execarg *ex, \
																t_data *data);
int			ft_redi_cmdtab_has_heredoc(t_cmdtab *cmdtab, t_execarg *ex);
int			ft_check_redi_if_has_no_cmd(t_cmdtab *cmdtab,
				t_execarg *ex, t_data *data);

/* FT BUILTIN */
void		ft_builtin_env(t_envlst *envlst);
int			ft_builtin_export(t_envlst *env, char **cmd, t_data	*data);
int			ft_builtin_export_api(t_envlst *env, char *key, char *value);
int			ft_builtin_unset(t_data *data, char **cmd);
int			ft_builtin_cd(t_envlst *env, char **argv, t_data *data, int ret);
int			ft_builtin_pwd(t_data *data);
int			ft_builtin_echo(char **argv);
void		ft_exit(t_data *data, char **argv);
void		ft_exit_normal(t_data *data, char **argv);
int			ft_check_if_exportkey_is_valid(char *key);

/* FT ENV */
char		**ft_env_init(char **envp);
char		*ft_env_getstr_env_value(t_envlst *env, const char *key);
int			ft_env_check_if_key_is_valid(t_envlst *env, char *key);
t_envlst	*ft_env_getenv_lst_value(t_envlst *env, char *key);
char		**ft_env_convert_envlst_to_tab(t_envlst *env);
char		*ft_env_extract_key(char *str);
char		*ft_env_extract_key_name(char *str, int *isenv);
char		*ft_env_extract_value_content(char *str);
int			ft_shlvl_increment(t_envlst *env);

/* FT ENV LIST */
t_envlst	*ft_env_lstnew(char *key, char *value, int isenv);
t_envlst	*ft_env_lstlast(t_envlst *lst);
int			ft_env_lstsize(t_envlst *lst);
int			ft_env_lstsize_export(t_envlst *lst);
void		ft_env_init_lst(char **envp, t_data *data);
void		ft_env_lstadd_front(t_envlst **alst, t_envlst *new);
void		ft_env_lstadd_back(t_envlst **alst, t_envlst *new);
void		ft_env_lstdelone(t_envlst *lst);
void		ft_env_lstclear(t_envlst **lst);
void		ft_env_lstclear_one(t_envlst **lst);
void		ft_env_lstclear_one_first_element(t_envlst **lst);
char		**ft_env_return_envlst_sorted_in_tab(t_envlst *env, int i);
char		**ft_env_get_envtab(t_envlst *env);

/* FT LIST */
void		ft_lstadd_back(t_list **alst, t_list *new);
t_list		*ft_lstlast(t_list *lst);
int			ft_lstsize(t_list *lst);
void		ft_lstdelone(t_list *lst);
void		ft_lstclear(t_list **lst);
int			ft_lst_count_cmdarg(t_list *lst);

/* FT FREE */
int			ft_free_cmdtab_lst(int pipe, t_cmdtab *cmdtab);
void		ft_free_all_minishell(t_data *data);
void		ft_free_tab_char(char **tab);

/* FT ERROR MANAGEMENT */
void		ft_err_display_line_error(t_data *data, char *cmd, char *msg);
void		ft_err_display_line_export_error(t_data *dat, char *cmd, char *msg);

void		signal_recept_not_blocking(int mode);
void		signal_recept_blocking_cmd(void);
// void		signal_recept_not_blocking_heredoc(void);

/* FT SINAUX */
int			ft_stty_control(int b);
int			ft_issaty_control(void);

// avoid compilation crash
void		rl_replace_line(const char *text, int clear_undo);
void		rl_clear_history(void);

#endif