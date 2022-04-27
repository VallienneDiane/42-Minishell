/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 12:56:42 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/25 13:38:35 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(t_cmd *cmd)
{
	char	*path;
	char	*pwd;
	char	*cwd;

	cwd = NULL;
	path = NULL;
	pwd = getcwd(NULL, 0);
	if (cmd->tab_str[1])
	{
		if ((ft_strcmp("~", cmd->tab_str[1])) == 0)
		{
			path = ft_getenv("HOME", cmd);
			chdir(path);
			pwd = getcwd(cwd, sizeof(cwd));
		}
		else if (access(cmd->tab_str[1], F_OK) == 0)
		{
			path = cmd->tab_str[1];
			chdir(cmd->tab_str[1]);
			pwd = getcwd(cwd, sizeof(cwd));
			if (pwd)
				cmd->mem_pwd = pwd;
			if ((access(pwd, F_OK) != 0))
			{
				printf("cd: error retrieving current directory: getcwd: ");
				printf("cannot access parent directories: No such file or directory\n");
			}
		}
		else if (access(cmd->tab_str[1], F_OK) != 0)
		{
			printf("cd: no such file or directory: %s\n",cmd->tab_str[1]);
			g_status = 256;
			return (1);
		}
	}
	else if (!cmd->tab_str[1])
	{
		if (ft_strlen(ft_getenv("HOME", cmd)) == 0)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			g_status = 256;
		}
		path = ft_getenv("HOME", cmd);
		chdir(path);
		pwd = getcwd(cwd, sizeof(cwd));
	}
	g_status = 0;
	return (0);
}

