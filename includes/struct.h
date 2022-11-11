/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:13:38 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/12 00:02:07 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "includes.h"

typedef enum e_redirection
{
	OUT_1,
	OUT_2,
	IN_1,
	IN_2
}	t_redirection;

typedef struct s_envlst
{
	char			*key;
	char			*value;
	int				alphaorder;
	int				isenv;
	struct s_envlst	*next;
}			t_envlst;

typedef struct s_list
{
	int				type;
	int				heavy;
	int				is_empty;
	char			*str;
	struct s_list	*next;
}					t_list;

enum e_stat
{
	STAT_NONE,
	STAT_ISFILE,
	STAT_ISDIR,
	STAT_ISEMPTY
};

enum e_prtype
{
	PRNO,
	PRQ1,
	PRQ2
};
typedef struct s_execarg
{
	int			i;
	int			isfile;
	enum e_stat	stat;
	char		**argv;
	char		*progpath;
}				t_execarg;

typedef struct s_cmdtab
{
	int		isbuilt;
	int		isempty;
	int		pipein;
	int		pipeout;
	int		reditype;
	char	*rediarg;
	pid_t	pidredi;
	pid_t	*multiredi;
	int		redinbr;
	int		fdredipipe[2];
	int		fd[2];
	int		fdsave[2];
	int		fdredi;
	int		fdredierr;
	char	*heredoc;
	int		hdcpipe[2];
	int		hdcfd;
	char	*hdcpath;
	pid_t	pid;
	t_list	*lst;
}				t_cmdtab;

typedef struct s_data
{
	char		*pgr_name;
	char		*line;
	char		*buffer;
	t_envlst	*env;
	t_cmdtab	*cmdtab;
	t_list		*cmdtoparse;
	int			nbpipes;
	int			fd[2];
	int			savefd[2];
	int			s_quotes_switch;
	int			d_quotes_switch;
	int			scroller;
	int			first_cmd;
	int			first_arg;
	int			quotes_in_parsing;
	int			len_max;
	int			first_in_line;
	int			ret;
	char		*heredocpath;
	int			type_of_the_last_cmd;
	struct stat	statbuf;
	int			currentshlvl;
}				t_data;

#endif
