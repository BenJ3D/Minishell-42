/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bducrocq <bducrocq@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:21:26 by bducrocq          #+#    #+#             */
/*   Updated: 2022/09/02 11:07:52 by bducrocq         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <./../includes/minishell.h>
//TODO: init env avec struc env pour key et value en chained ou tab**
/**
 * @brief fonction test pour debug le split env
 * 
 * @param env 
 * @param key 
 * @return int 
 */
int	env_test_read(char **env, const char *key)
{
	char *value;
	int i;
	int ret;

	ret = 0;
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], key, ft_strlen(key)))
			break ;
		i++;
	}
	value = ft_strdup(env[i]);
	printf("env %s : %s", key, value);
	free(value);
	return (i);
}

char	*ft_env_return_key(char **env, char *key)
{

	return (NULL);
}

int	ft_env_count_keys(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
		i++;
	return (i);
}

char	**ft_env_init(char **envp)
{
	char **env;
	int i;

	env = ft_calloc(sizeof(char **), ft_env_count_keys(envp) + 1);
	if (!env)
		return (NULL);
	i = 0;
	while (envp[i])
		env[i] = ft_strdup(envp[i++]);
	env_test_read(envp, "LOGNAME");
	printf("\nenv %s\n", env[12]);
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "LOGNAME", 8))
			break ;
		i++;
	}
	printf("\nenv %s\n", env[i]);
	
	
	return (env);
}

void	ft_free_all_array(char **env)
{
	int	i;

	i = 0;
	while(env[i])
	{

		free (env[i]);
		i++;
		printf("free i = %i\n", i);
	}
	// env = NULL;
	free (env);
}