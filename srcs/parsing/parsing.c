/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 02:43:41 by bducrocq          #+#    #+#             */
/*   Updated: 2022/10/28 10:34:15 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

void	ft_cmf_first_type(t_list	*tmp)
{
	if (tmp->str[0] == '>')
	{
		if (tmp->str[1] == '>')
			tmp->type = OUT2;
		else
			tmp->type = OUT1;
		tmp->next->type = OUTFILE; //? je ne comprends pas pourquoi on le met ici, et si jamais il n'y a pas de tmp->next?
		tmp = tmp->next;
	}
	else if (tmp->str[0] == '<')
	{
		if (tmp->str[1] == '<')
			tmp->type = IN2;
		else
			tmp->type = IN1;
	}
	else
		tmp->type = CMD;
}

int	ft_count_pipe(t_data	*data, char *buffer) //ft pour test sans parsing
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while(buffer[i])
	{
		ft_quotes_checker(data, buffer, i);
		if (buffer[i++] == '|' && data->s_quotes_switch == 0 && data->d_quotes_switch == 0)
			len++;
	}
	return (len);
}

/**
 * @brief retourne len du prochain mot
 * gère les pipes '|' (s'arrete si pipe trouvé)
 * 
 * @param str 
 * @return int 
 */
static int	ft_strlen_next_word(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '|')
		return (1);
	while (!ft_isspace(str[i]) && str[i] && str[i] != '|')
		i++;
	return (i);
}

/**
 * @brief donne un type a chaque commande, pour faciliter le parsing en execve
 * ATTENTION : les erreurs de syntax doivent deja etre gerer en amont, 
 * sinon risque de SEGV
 * @param lst la lst avec toutes les commandes du buffer pas encore split
 * @return int 
 */
static int	ft_define_cmd_type(t_list *lst) // TODO: a normer !!
{
	t_list	*tmp;

	if (!lst)
		return (-1);
	tmp = lst;
	ft_cmf_first_type(tmp);
	//tmp->type = CMD;
	tmp = tmp->next;
	while (tmp)
	{
		if (tmp->str[0] == '>')
		{
			if (tmp->str[1] == '>')
				tmp->type = OUT2;
			else
				tmp->type = OUT1;
			tmp->next->type = OUTFILE; //? je ne comprends pas pourquoi on le met ici, et si jamais il n'y a pas de tmp->next?
			tmp = tmp->next;
		}
		else if (tmp->str[0] == '<')
		{
			if (tmp->str[1] == '<')
				tmp->type = IN2;
			else
				tmp->type = IN1;
			if (tmp->next)
			{
				if (tmp->type == IN1)
					tmp->next->type = INFILE;
				else
					tmp->next->type = INQUOTE;
				tmp = tmp->next;
			}
		}
		else if (tmp->str[0] == '|')
		{
			tmp->type = PIPE;
			tmp = tmp->next;
			if (tmp)
				tmp->type = CMD;
		}
		else
			tmp->type = ARG;
		if (tmp)
			tmp = tmp->next;
	}
	return (0);
}

/**
 * @brief split tout le buffer en plusieurs cmd dans une liste chainé
 * 
 * @param lst 
 * @param buffer 
 * @return int 
 */
static t_list	*ft_split_buffercmd_in_lst(char *buffer, int bufi)
{
	int		i;
	int		len;
	char	*str;
	t_list *cmd;
	
	cmd = NULL;
	while (buffer[bufi])
	{
		while(ft_isspace(buffer[bufi]) && buffer[bufi] && buffer[bufi] != '|')
			bufi = bufi + 1;
		if (buffer[bufi] == '\0')
			return (cmd);
		len = ft_strlen_next_word(buffer + bufi);
		str = ft_calloc(len + 1, sizeof(char));
		if (!str)
			return (NULL);
		i = 0;
		while(len-- > 0)
			str[i++] = buffer[bufi++];
		ft_lstadd_back(&cmd, ft_lstnew(str));
		free(str);
	}
	return (cmd);
}

void	ft_init_cmdtab_value(t_cmdtab *cmdtab)
{
	// int	i;
	
	// while (cmdtab[i])
	// {
	// 	cmdtab->pipein = 0;
	// 	cmdtab->pipeout = 0;
	// 	cmdtab->redirection = 0;
	// 	cmdtab->rediarg = NULL;
	// }
	
}

/**
 * @brief 
 * 
 * @param lst 
 * @param nbrpipe 
 * @return t_cmdtab* 
 */
static t_cmdtab *ft_create_tab_per_cmd(t_list *lst, int nbrpipe)
{
	t_list		*tmp;
	t_cmdtab	*cmdtab;
	char		*str;
	int			i;
	
	tmp = lst;
	cmdtab = ft_calloc(nbrpipe + 2, sizeof(t_cmdtab));
	if (!cmdtab)
		return (NULL);
	i = 0;
	// ft_init_cmdtab_value(cmdtab);
	cmdtab[i++].lst = lst;
	// cmdtab[i++].lst->type = 0;
	while(tmp)
	{
		if (tmp->str[0] == '|')
		{
			cmdtab[i].lst = tmp->next;
			tmp->next = NULL;
			// if (cmdtab->lst)
			// 	cmdtab->lst->type = 0;
			tmp = cmdtab[i++].lst;
		}
		else
		{
			// if (cmdtab[i].lst)
			// 	cmdtab[i].lst->type = 0;
			tmp = tmp->next;
		}
	}
	return (cmdtab);
}

/**
 * @brief parsing de base pour decouper les cmd et args
 * 
 * @param data 
 * @param buffer 
 * @return int 
 */
int	ft_parsing_prompt(t_data *data, char *buffer)
{
	int		pipe;
	int		bufi;
	int		i;
	
	pipe = ft_count_pipe(data, buffer);
	if (pipe == 0)
		pipe++;
	i = 0;
	bufi = 0;
	if (!ft_full_prompt_quote_check(data, buffer))
	{
		exit(42);
		return (0);
	}
	data->cmdtoparse = ft_total_parsing(data, buffer);
	//TODO: gerer les erreurs de syntaxes //c'est quoi les erreurs de syntaxe ?
	ft_define_cmd_type(data->cmdtoparse);
	dbg_lstdisplay_color_type(data->cmdtoparse); //FIXME:
	data->cmdtab = ft_create_tab_per_cmd(data->cmdtoparse, pipe);
	return (pipe);
}


/**
 * @brief  return **argv pour execve (ex: "echo bonjour >> out.txt"  
 * 													==> return tab :
 * 													 tab[0]=echo /
 * 													 tab[1]=bonjour)
 * @param cmd 
 * @return char** 
 */
char	**ft_lstcmd_to_cmdarg_for_execve(t_list	*cmd)
{
	char	**argv;
	int		nbword;
	t_list	*lst;
	int		y;
	

	nbword = ft_lstsize(cmd); //FIXME: ft pour calculer le nombre de mot cmd+arg sans les redirections et pipe
	argv = ft_calloc(nbword + 1, sizeof(char **));
	// argv = (char **)malloc(nbword + 1 * sizeof(char *));
	if (!argv)
		return (NULL);
	lst = cmd;
	y = 0;
	while (lst)
	{
		// if (lst->type == PIPE) //TODO:
		if (lst->type == CMD || lst->type == ARG)
			argv[y] = ft_strdup(lst->str);
		y++;
		lst = lst->next;
	}
	return (argv);
}

// 							ls -all | grep @ | ls