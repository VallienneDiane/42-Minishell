/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 12:56:42 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/28 14:58:15 by dvallien         ###   ########.fr       */
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
			ft_cd_folder(cmd, path, pwd, cwd);
		else if (access(cmd->tab_str[1], F_OK) != 0)
			ft_cd_no_access(cmd);
	}
	else if (!cmd->tab_str[1])
		ft_cd_without_args(cmd, path, pwd, cwd);
	return (0);
}

void	ft_cd_folder(t_cmd *cmd, char *path, char *pwd, char *cwd)
{
	path = cmd->tab_str[1];
	chdir(cmd->tab_str[1]);
	pwd = getcwd(cwd, sizeof(cwd));
	if (pwd)
		cmd->mem_pwd = pwd;
	if ((access(pwd, F_OK) != 0))
	{
		printf("cd: error retrieving current directory: getcwd: ");
		printf("cannot access parent directories: ");
		printf("No such file or directory\n");
	}
}

void	ft_cd_without_args(t_cmd *cmd, char *path, char *pwd, char *cwd)
{
	if (ft_strlen(ft_getenv("HOME", cmd)) == 0)
	{
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		g_status = 1;
	}
	path = ft_getenv("HOME", cmd);
	chdir(path);
	pwd = getcwd(cwd, sizeof(cwd));
}

int	ft_cd_no_access(t_cmd *cmd)
{
	printf("cd: no such file or directory: %s\n", cmd->tab_str[1]);
	g_status = 1;
	return (1);
}
