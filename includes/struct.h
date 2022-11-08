/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 19:13:38 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/08 16:07:27 by hmarconn         ###   ########.fr       */
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
	char			*str;
	struct s_list	*next;
}					t_list;

enum e_stat
{
	STAT_NONE,
	STAT_ISFILE,
	STAT_ISDIR
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

typedef struct s_cmdtab //pour creer un tab de command, un t_list par commande (jusqu'à trouver un pipe '|'))
{									//exemple si buffer = ls -all | cat -e
	int		isbuilt;				//si isbuilt > 0 : c'est une builtin
	int		pipein;
	int		pipeout;
	int		reditype;
	char	*rediarg;
	pid_t	pidredi;
	pid_t	*multiredi;
	int		redinbr;				//compte le nombre de redi pour while jusqu'a 0
	int		fdredipipe[2];
	int		fd[2];					//    cmdtab[0].lst = ls -> -all -> (pipe)
	int		fdsave[2];				//    cmdtab[0].lst = ls -> -all -> (pipe)
	int		fdredi;					//  file descriptor if redirection
	int		fdredierr;				//  1 if file (fdredi) not exist
	char	*heredoc;				//contient tout le heredocs
	int		hdcpipe[2];				//pipe pour un heredocs par cmd
	int		hdcfd;				//fd pour open un tmp pour heredocs par cmd
	char	*hdcpath;			//path du tmp file pour les heredocs par commandes
	pid_t	pid;
	t_list	*lst;
}				t_cmdtab;			//    cmdtab[1].lst = cat -> -e -> (null)

typedef struct s_data
{
	char		*pgr_name; 			//le nom de notre programe afficher dans notre prompt
	char		*line;				//*line pour le prompt
	char		*buffer;			//buffer pour readline
	t_envlst	*env;				//contient tout l'environnement sous forme de liste
	t_cmdtab	*cmdtab; 			//toutes les commandes sont stockées dans un tableau de list
	t_list		*cmdtoparse; 		//contient toute la ligne de commande split en mot
	int			nbpipes;
	int			fd[2];				//pour pipe
	int			savefd[2];				//pour pipe
	int			s_quotes_switch;
	int			d_quotes_switch;
	int			scroller;
	int			first_cmd;
	int			quotes_in_parsing;
	int 		ret;					//test pour heredocs
	char		*heredocpath;
	int			type_of_the_last_cmd;
	struct stat	statbuf;
}				t_data;

#endif
