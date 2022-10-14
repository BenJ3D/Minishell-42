/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmarconn <hmarconn@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 13:26:09 by hmarconn          #+#    #+#             */
/*   Updated: 2022/10/14 17:08:30 by hmarconn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/minishell.h"

int	ft_total_parsing(t_data	*data, char	*buffer)
{
	int	i;
	int	len;
	char	*str;
	char	*semi_final;
	int		pin;
	int		pan;

	i = 0;
	len = 0;
	semi_final = NULL;
	while (buffer[i])
	{
		ft_quotes_checker(data, buffer, i);
		len = 0;
		pin = 0;
		pan = 0;
		str = NULL;
		while (data->s_quotes_switch == 1 || data->d_quotes_switch == 1)
			{
				if (data->s_quotes_switch == 1)
				{
					pin = i;
					while (buffer[i] != '$')
					{
						len++;
					}
					if (len != 0)
					{
						str = malloc(sizeof(char) * len + 1);
						if (!str)
							exit(57);
						pan = 0;
						while (pin <= i)
						{
							semi_final[pan] = buffer[pin];
							pan++;
							pin++;
						}
						
					}
					else if (buffer[i] == '$')
					{
						i++;
						while (buffer[i] >= 'A' && buffer[i] <= 'Z' || buffer[i] == '_')
							len++;
					}
				}
				else
				{
					
				}
				i++;
				ft_quotes_checker(data, buffer, i);	
			}
		else if (buffer[i] == '$')
			;
		else if (buffer[i] == SPACES)
			;
		else if (buffer[i] == '|')
			;
		else
			;		
	}
}