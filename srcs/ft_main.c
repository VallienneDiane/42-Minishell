/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:36:32 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/18 17:31:44 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_parse_type(t_list *list, t_cmd *cmd, char **envp)
{		
	if (ft_strncmp("cmd", list->type, 3) == 0)
	{
		cmd->valid_path = ft_access_path(list, cmd);
		ft_process(list, cmd, envp);
	}
	// if (ft_strcmp("redir", list->type, 5) == 0)
	// 	ft_redir();
	// if (ft_strcmp("builtin", list->type, 7) == 0)
	// 	ft_builtin();
	// if (ft_strcmp("var_env", list->type, 7) == 0)
	// 	ft_builtin();
	(void)list;
	(void)cmd;
	(void)envp;
}

int	main(int ac, char **av, char **envp)
{
	t_list	*list;
	t_cmd	cmd;
	// char 	*line;
	(void)ac;
	(void)av;

	list = malloc(sizeof(t_list));
	list = NULL;
	ft_create_list(&list);
	cmd.line_path = ft_get_line_path(envp);
	cmd.tab_path = ft_split(cmd.line_path, ':');
	ft_parse_type(list, &cmd, envp);
	// while (1)
	// {
	// 	line = readline("better_bash > ");
	// 	printf("%s\n", line);
	// }
}
