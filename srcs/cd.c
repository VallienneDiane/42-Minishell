/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 12:56:42 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/21 17:29:09 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(t_cmd *cmd, char **envp)
{
	char	*path;
	char	*pwd;
	char	*cwd;
	(void)envp;

	cwd = NULL;
	path = NULL;
	pwd = getcwd(NULL, 0);
	if (cmd->tab_str[1])
	{
		if ((ft_strcmp("~", cmd->tab_str[1])) == 0)
		{
			path = getenv("HOME");
			chdir(path);
			pwd = getcwd(cwd, sizeof(cwd));
			printf("PATH %s, PWD %s\n", path, pwd);
		}
		else if (access(cmd->tab_str[1], F_OK) == 0)
		{
			path = cmd->tab_str[1];
			chdir(cmd->tab_str[1]);
			pwd = getcwd(cwd, sizeof(cwd));
			printf("PATH %s, PWD %s\n", path, pwd);
			if ((access(pwd, F_OK) != 0))
			{
				// pwd = getcwd(pwd, sizeof(pwd));
				printf("cd: error retrieving current directory: getcwd: \
				cannot access parent directories: No such file or directory\n");
			}
		}
		else if (access(cmd->tab_str[1], F_OK) != 0)
		{
			printf("cd: no such file or directory: %s\n",cmd->tab_str[1]);
			return (1);
		}
	}
	else if (!cmd->tab_str[1])
	{
		if (!getenv("HOME"))
			ft_putstr_fd("miniHell: cd: HOME not set\n", 2);
		path = getenv("HOME");
		chdir(path);
		pwd = getcwd(cwd, sizeof(cwd));
		printf("PATH %s, PWD %s\n", path, pwd);
	}
	return (0);
}

