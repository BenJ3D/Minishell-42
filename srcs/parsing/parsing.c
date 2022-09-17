/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 02:43:41 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/18 00:32:24 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>

static int	ft_count_pipe(char *buffer) //ft pour test sans parsing
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while(buffer[i])
		if (buffer[i++] == '|')
			len++;
	return (len);
}

static int	ft_split_cmd_and_arg(t_cmdtable *cmdtable, char *buffer, t_data *data) //FIXME: virer t_data
{
	int	i;
	int	b;
	int	len;
	t_cmdtable tmpcmdtab;
	
	tmpcmdtab.progname = ft_strdup("echo");
	tmpcmdtab.arg = ft_calloc(2 + 1, sizeof(tmpcmdtab.arg));
	tmpcmdtab.arg[0] = ft_strdup("bonjour  ");
	tmpcmdtab.arg[1] = ft_strdup("benjamin");
	cmdtable = ft_calloc(ft_count_pipe(buffer) + 1, sizeof(cmdtable));
	// ft_lstadd_back(&data->cmdlst, ft_lstnew(&tmpcmdtab));
	i = 0;
	while (ft_isspace(buffer[i]) && buffer[i]) // passe les premier espace
		i++;
	b = 0;
	len = 0;
	ft_putnbr(i);
	ft_putstr("\n");
	if (buffer[i] == '\0')
		ft_putstr("IL EST NULL\n");
	while (buffer[i] && (!ft_isspace(buffer[i]) || buffer[i] != '|'))
	{
		i++;
		len++;
	}
	ft_putnbr(i);
	ft_putstr("\n");
	ft_putnbr(len);
	ft_putstr("\n");
	printf("%s\n",tmpcmdtab.progname);
	printf("%s %s\n",tmpcmdtab.arg[0], tmpcmdtab.arg[1]);
	// printf("%s\n", data->cmdlst->((t_cmdtable*)content)->progname);
	ft_putstr(buffer);
	ft_putstr("\n");
	ft_putstr(buffer + i);
	ft_putstr("\n");
	return (0);
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
 * @brief split tout le buffer en plusieurs cmd dans des lists 
 * (lst[0]->str = "ls -all |"
 * 	lst[1]->str = "cat -e")
 * 
 * @param lst 
 * @param buffer 
 * @return int 
 */
static t_list	*ft_split_buffercmd_in_lst(char **buffer)
{
	int		i;
	int		y;
	int		len;
	char	*str;
	t_list *cmd;
	
	y = 0;
	cmd = NULL;
	while (**buffer)
	{
		while(ft_isspace(**buffer) && **buffer)
			*(*buffer)++;
		if (*(*buffer) == '\0')
			return (cmd);
		len = ft_strlen_next_word(*buffer);
		str = ft_calloc(len + 1, sizeof(str));
		if (!str)
			return (NULL);
		i = 0;
		while(len-- > 0)
			str[i++] = *(*buffer)++;
		ft_lstadd_back(&cmd, ft_lstnew(str));
		free(str);
	}
	return (cmd);
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
	int	pipe;
	int	i;
	int	bufi;
	
	pipe = ft_count_pipe(buffer);
	data->cmdlst = ft_calloc(pipe + 1, sizeof(data->cmdlst));
	i = 0;
	// data->cmdlst = NULL;
	// data->cmdlst[0] = NULL;
	while (i < pipe + 1)
		data->cmdlst[i++] = NULL;
	// bufi = 0;
	t_list	*test;
	t_list	*test2;
	char	**ptr;
	char *bufcpy = ft_strdup(buffer);
	
	ptr = &buffer;
	test = ft_split_buffercmd_in_lst(&buffer);
	test2 = ft_split_buffercmd_in_lst(&bufcpy);

	ft_lstadd_back(&data->cmdlst[0], test);
	ft_lstadd_back(&data->cmdlst[1], test2);
	// printf("%s\n", buffer);
	printf("HOURA ??\n");
	ft_lstdisplay_color(data->cmdlst[0]);
	printf("HOURA 2??\n");
	ft_lstdisplay_color(data->cmdlst[1]);
	printf("BUF rip %s\n", *ptr);
	i = 0;
	// while (i < pipe + 1)
	// 	ft_lstclear(&data->cmdlst[i++]);
	// ft_split_cmd_and_arg(data->cmdtab, buffer, data);


	
	// cmd[0]->cmd = ft_split(buffer, ' ');
	// for(int i = 0;  cmd[i]; i++)
	// {
	// 	ft_putstr(cmd[i]);
	// 	ft_putstr(" --\n");
	// }
	
	return (0);
}

// /**
//  * @brief split tout le buffer en plusieurs cmd dans des lists 
//  * (lst[0]->str = "ls -all |"
//  * 	lst[1]->str = "cat -e")
//  * 
//  * @param lst 
//  * @param buffer 
//  * @return int 
//  */
// static int	ft_split_buffercmd_in_lst(t_list *cmd, char *buffer)
// {
// 	int		i;
// 	int		b;
// 	int		len;
// 	char	*tmp;
// 	i = 0;
// 	while (ft_isspace(buffer[i]) && buffer[i]) // passe les premier espace
// 		i++;
// 	len = 0;
// 	b = i;
// 	while (buffer[i] && (!ft_isspace(buffer[i++])))
// 		len++;
// 	tmp = ft_calloc(len + 1, sizeof(tmp));
// 	if (!tmp)
// 		return (1);
// 	i = b;
// 	b = 0;
// 	while(buffer[i] && (!ft_isspace(buffer[i])))
// 		tmp[b++] = buffer[i++];
// 	ft_lstadd_back(&cmd, ft_lstnew(tmp));
// 	printf("lst1 = %s\n", cmd->str);
// 	free(tmp);
// 	return (0);
// }
