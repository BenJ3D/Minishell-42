/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 15:45:53 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/30 19:26:20 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>
// TODO: faire correspondre les "/path/" du dossier courant comme
// TODO: le vrai bash avec "~/" ==> voir getenv("HOME") et getcwd()
		//en faite cest le bash linux qui fait ça, pas sur mac donc optionnel

/**
 * @brief update data->line prompt
 *
 * @return char* alloue avec malloc()! ==>> penser a free()
 */
char	*prompt_update(t_envlst *env, char *prgname)
{
	char	*line;
	char	*user;
	char	usertmp[USER_MAX_LEN];
	
	if (!prgname)
		prgname = ft_strdup("minishell");
	if (ft_env_check_if_key_is_valid(env, "USER") < 0)
		line = ft_strjoin_max("%s%s>%s$ ",
				COLOR_CYAN, prgname, COLOR_NONE);
	else
	{
		user = ft_env_getstr_env_value(env, "USER");
		if (ft_strlen(user) > (USER_MAX_LEN))
		{
			ft_strlcpy(usertmp, user, USER_MAX_LEN);
			free (user);
			user = ft_strdup(usertmp);
		}
		line = ft_strjoin_max("%s- %s -%s %s>%s$ ",
					COLOR_GREEN, user,
					COLOR_CYAN, prgname, COLOR_NONE);
		free (user);
	}
	return (line);
}

void	prompt_minishell(char **av, t_data *data)
{
	int		nbpipe;
	
	data->buffer = NULL;
	data->line = prompt_update(data->env, data->pgr_name);
	data->buffer = readline(data->line);
	while ((data->buffer))
	{ 
		if (data->buffer[0] != '\0')
			add_history(data->buffer);
		nbpipe = ft_parsing_prompt(data, data->buffer);
		// dbg_display_cmdtab(data->cmdtab);
		dbg_lstdisplay_color_type(data->cmdtoparse);
		ft_run_execve(data->cmdtab, data);//TODO: ft execv et lst to argv for execved
		ft_free_cmdtab_lst(nbpipe, data->cmdtab);
		free(data->line);
		data->line = prompt_update(data->env, data->pgr_name);
		free(data->buffer);
		data->buffer = readline(data->line);
	}
	if (data->line)
		free(data->line);
	free(data->buffer);
	rl_on_new_line();
	write(1, "exit\n", 6);
}



/**
 * @brief prompt coder en dur pour tests execs
 * 
 * @param av 
 * @param env 
 */
void prompt_basic_test(char **av, t_data *data)
{
	pid_t	child;
	
	data->buffer = NULL;
	data->line = prompt_update(data->env, data->pgr_name);
	data->buffer = readline(data->line);

	char **args;
	args = ft_calloc(4, sizeof(char));
	args[0]= ft_strdup("ls");
	args[1]= ft_strdup("-all");
	// args[2]= ft_strdup("-all");
	
	while ((data->buffer))
	{ 
		if (data->buffer[0] != '\0')
			add_history(data->buffer);
		if (!ft_strncmp(data->buffer, "ls", 3))
		{
			child = fork();
			if (child == 0)
				execve("/bin/ls", args, NULL); //TODO:TODO:
			//if (child > 0)
			//	printf("Child pid = %i\n", child);
			wait(0);
		}
		else if (!ft_strncmp(data->buffer, "env", 4))
		{
			ft_builtin_env(data->env);
		}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////      EXPORT TEST     //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
		else if (!ft_strncmp(data->buffer, "export BEN", 11))
		{
			char **tabexport = ft_calloc(3, sizeof(tabexport));

			tabexport[0] = ft_strdup("export");
			tabexport[1] = ft_strdup("BEN=BENEBI");
			
			ft_builtin_export(data->env, tabexport);
			free (tabexport[0]);
			free (tabexport[1]);
			free (tabexport);
		}
		else if (!ft_strncmp(data->buffer, "export =BEN", 12))
		{
			char **tabexport = ft_calloc(3, sizeof(tabexport));

			tabexport[0] = ft_strdup("export");
			tabexport[1] = ft_strdup("=BENEBI");
			
			ft_builtin_export(data->env, tabexport);
			free (tabexport[0]);
			free (tabexport[1]);
			free (tabexport);}
		else if (!ft_strncmp(data->buffer, "export3", 8))
		{
			char **tabexport = ft_calloc(3, sizeof(tabexport));

			tabexport[0] = ft_strdup("export");
			tabexport[1] = ft_strdup("BENEBI");
			
			ft_builtin_export(data->env, tabexport);
			free (tabexport[0]);
			free (tabexport[1]);
			free (tabexport);}
		else if (!ft_strncmp(data->buffer, "export", 7))
		{
			char **tabexport = ft_calloc(3, sizeof(tabexport));

			tabexport[0] = ft_strdup("export");
			tabexport[1] = ft_strdup("");
			
			ft_builtin_export(data->env, tabexport);
			free (tabexport[0]);
			free (tabexport[1]);
			free (tabexport);
		}
		else if (!ft_strncmp(data->buffer, "export5", 8))
		{
			char **tabexport = ft_calloc(3, sizeof(tabexport));

			tabexport[0] = ft_strdup("export");
			tabexport[1] = NULL;
			
			ft_builtin_export(data->env, tabexport);
			free (tabexport[0]);
			free (tabexport[1]);
			free (tabexport);
		}
		else if (!ft_strncmp(data->buffer, "export USER", 12))
		{
			char **tabexport = ft_calloc(3, sizeof(tabexport));

			tabexport[0] = ft_strdup("export");
			tabexport[1] = ft_strdup("USER=benji42");
			
			ft_builtin_export(data->env, tabexport);
			free (tabexport[0]);
			free (tabexport[1]);
			free (tabexport);
			}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//////////////////////////      UNSET TEST    //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
		else if (!ft_strncmp(data->buffer, "unset", 6))
		{
			
		}
		else if (!ft_strncmp(data->buffer, "unset BEN", 10))
		{
			char **tabexport = ft_calloc(3, sizeof(tabexport));

			tabexport[0] = ft_strdup("unset");
			tabexport[1] = ft_strdup("BEN");
			
			ft_builtin_unset(data->env, tabexport);
			free (tabexport[0]);
			free (tabexport[1]);
			free (tabexport);
		}
		else if (!ft_strncmp(data->buffer, "unset USER", 11))
		{
			char **tabexport = ft_calloc(3, sizeof(tabexport));

			tabexport[0] = ft_strdup("unset");
			tabexport[1] = ft_strdup("USER");
			
			ft_builtin_unset(data->env, tabexport);
			free (tabexport[0]);
			free (tabexport[1]);
			free (tabexport);
		}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
/////////////////////////////      CD TEST    //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
		else if (!ft_strncmp(data->buffer, "testcd", 8))
		{
			setenv("PWD", "/home/ben/projet/", 1);
			printf("PWD = %s\n", getenv("PWD"));
			printf("OLDPWD = %s\n", getenv("OLDPWD"));
		}
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////      PWD TEST    //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
		else if (!ft_strncmp(data->buffer, "pwd", 8))
		{
			printf("%s\n", getenv("PWD"));
		}
		else if (!ft_strncmp(data->buffer, "rmm", 8))
		{
			unlink("adieu"); // supprime un fichier
		}
		else if (data->buffer[0] != '\0')
		{
			char *line2;
			
			line2 = ft_strjoin_max("%sMiniHell: %s%s: %scommand not found%s\n", 
				COLOR_CYAN, COLOR_PURPLE, data->buffer, COLOR_RED, COLOR_NONE);
			ft_putstr_fd(line2, 2);
			free (line2);
		}
		free(data->buffer);
		data->buffer = NULL;
		free(data->line);
		data->line = prompt_update(data->env, data->pgr_name);
		// rl_on_new_line();
		data->buffer = readline(data->line);
	}
	if (data->line)
		free(data->line);
	free(data->buffer);
	rl_on_new_line();
	write(1, "exit13\n", 8);
}
