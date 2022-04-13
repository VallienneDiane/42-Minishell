/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 12:56:42 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/13 12:56:59 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(t_cmd *cmd, char **envp)
{
	char	*pwd;
	char	*home;
	(void)envp;

	// si aucun argument apres cd ou un ~ il faut revenir au home
	if (!cmd->tab_str[1] || ft_strcmp("~", cmd->tab_str[1]))
	{
		// si chemin vers home /Users/dvallien n'existe pas
		if (!(home = getenv("HOME")))
			ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		// change pwd par pwd home
		pwd = getcwd(NULL, 0);
		if (!getenv("OLDPWD"))
		chdir(home);
		printf("%s\n", pwd);
	}
	// si arg existe et qu'on y accede on change le oldpwd par le nouveau 
	// et on se deplace dans le dossier arg 1
	else if (cmd->tab_str[1] && access(cmd->tab_str[1], F_OK) == 0)
	{
		// change pwd
		// change_oldpwd(cmd);
		// se deplace dans le dossier de l'arg 1
		chdir(cmd->tab_str[1]);
	}
	// si arg existe et qu'on n'y accede pas on return 1
	else if (cmd->tab_str[1] && access(cmd->tab_str[1], F_OK) != 0)
	{
		return (1);
	}
	pwd = getcwd(NULL, 0);
	// change_value();
	return (0);
}
