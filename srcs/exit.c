/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:34:05 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/19 15:25:29 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_exit(t_cmd *cmd)
{
	size_t i;

	printf("exit\n");
	ft_term_handler(1);
	if (cmd->tab_str[1])
	{
		i = 0;
		while (i < ft_strlen(cmd->tab_str[1]))
		{
			if (cmd->tab_str[1][i] < '0' || cmd->tab_str[1][i] > '9')
			{
				printf("minishell: exit: %s: numeric argument required\n", cmd->tab_str[1]);	
				exit(255);
			}
			i++;
		}
		exit(errno);
	}
	exit(0);
}