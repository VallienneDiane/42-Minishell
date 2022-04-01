/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_diane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 13:36:32 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/01 14:55:45 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_parse_type(t_list *list, t_cmd *cmd, char **envp)
{	
	(void)cmd;
	(void)envp;
	int	i;
	int	current_block;

	i = 0;
	current_block = 1;
	while (list)
	{
		ft_start_exec(list, cmd, envp, current_block);
		cmd->valid_path = ft_access_path(list, cmd);
		while (list && list->block == current_block)
			list = list->next;
		if (list && list->block != current_block)
		{
			ft_exec_pipex(list, cmd, envp);
			current_block++;
		}
		else
		{
			ft_execution(cmd, envp);
			// free (cmd);
		}
	}
}

void	ft_execution(t_cmd *cmd, char **envp)
{
	if (cmd->redir_in || cmd->redir_out1 || cmd->redir_out2)
		ft_redir_dup(cmd, envp);
	else
		ft_execute(cmd, envp);
}

void	ft_execute(t_cmd *cmd, char **envp)
{
	if (execve(cmd->valid_path, cmd->tab_str, envp) < 0)
	{
		free(cmd->valid_path);
		free(cmd->tab_str);
		printf("Error : %s : failure execve\n", cmd->valid_path);
	}
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
	// while (1)
	// 	line = readline("minishell > ");
	ft_create_list(&list);
	cmd.line_path = ft_get_line_path(envp);
	cmd.tab_path = ft_split(cmd.line_path, ':');
	ft_parse_type(list, &cmd, envp);
}
