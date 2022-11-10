/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 18:12:46 by bducrocq          #+#    #+#             */
/*   Updated: 2022/11/10 15:20:54 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <../includes/minishell.h>

static void	ft_init_minishell(t_data *data)
{
	data->pgr_name = ft_strdup("MiniHell");
	data->s_quotes_switch = 0;
	data->d_quotes_switch = 0;
	data->savefd[0] = dup(STDIN_FILENO);
	data->savefd[1] = dup(STDOUT_FILENO);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	ft_issaty_control();
	ft_stty_control(0, &data);
	ft_init_minishell(&data);
	ft_env_init_lst(envp, &data);
	prompt_minishell(av, &data);// supprimer av
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	ft_exit_normal(&data, av);
	return (0);
}
