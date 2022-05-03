/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 14:34:05 by dvallien          #+#    #+#             */
/*   Updated: 2022/05/03 15:53:17 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_exit(t_cmd *cmd)
{
	printf("exit\n");
	if (cmd->tab_str[1])
	{
		ft_exit_one_arg(cmd);
		if (cmd->tab_str[2])
		{
			printf("miniHell: exit: too many arguments\n");
			g_status = 1;
			return (0);
		}
		exit(ft_atoi(cmd->tab_str[1]));
	}
	exit(0);
}

void	ft_exit_one_arg(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(cmd->tab_str[1]))
	{
		if ((cmd->tab_str[1][i] < '0' || cmd->tab_str[1][i] > '9') \
		|| ft_atoi(cmd->tab_str[1]) > INT_MAX)
		{
			printf("miniHell: exit: %s: numeric argument required\n", \
			cmd->tab_str[1]);
			exit(255);
		}
		i++;
	}
}
