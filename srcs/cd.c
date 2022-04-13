/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 12:56:42 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/13 14:34:22 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(t_cmd *cmd, char **envp)
{
	char	*path;
	char	*pwd;
	(void)envp;

	path = getcwd(NULL, 0);
	pwd = getcwd(NULL, 0);
	if (cmd->tab_str[1])
	{
		if ((ft_strcmp("~", cmd->tab_str[1])) == 0)
		{
			printf("tilde %s\n", pwd);
			path = getenv("HOME");
			chdir(path);
			// CHANGER PWD AVEC LE PWD ACTUEL
			printf("tilde %s\n", pwd);
		}
		else if (access(cmd->tab_str[1], F_OK) == 0)
		{
			printf("dossier %s\n", path);
			chdir(cmd->tab_str[1]);
			// CHANGER PWD AVEC LE PWD ACTUEL
			printf("dossier %s\n", path);
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
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		printf("aucun arg %s\n", path);
		path = getenv("HOME");
		chdir(path);
		// CHANGER PWD AVEC LE PWD ACTUEL
		printf("aucun arg %s\n", path);
	}
	return (0);
}
