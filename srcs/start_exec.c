/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:42:11 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/07 18:08:20 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_start_exec(t_list *list, t_cmd *cmd, char **envp)
{	
	int	i;
	int	current_block;

	i = 0;
	current_block = 1;
	cmd->valid_path = NULL;
	cmd->stdin_copy = dup(STDIN_FILENO);
	while (list)
	{
		ft_get_args(list, cmd, current_block);
		if ((ft_is_builtin(cmd->tab_str[0]) == 0) && cmd->tab_str[0])
			cmd->valid_path = ft_access_path(cmd);
		while (list && list->block == current_block)
			list = list->next;
		if (list && list->block != current_block)
		{
			ft_exec_pipex(cmd, envp);
			current_block++;
		}
		else
			ft_execution(cmd, envp);
		// free les tabs
	}
}

void	ft_execution(t_cmd *cmd, char **envp)
{
	if (cmd->tab_redir_in[0] || cmd->tab_redir_out1[0] \
	|| cmd->tab_redir_out2[0])
	{
		ft_redir_dup(cmd, envp);
	}
	else
		ft_execute(cmd, envp);
}

void	ft_execute(t_cmd *cmd, char **envp)
{
	if (ft_is_builtin(cmd->tab_str[0]) == 1)
		exit (ft_exec_builtin(cmd));
	if (cmd->valid_path != NULL && ft_is_builtin(cmd->tab_str[0]) == 0)
	{
		if (cmd->tab_str[0])
		{
			if (execve(cmd->valid_path, cmd->tab_str, envp) < 0)
			{
				free(cmd->valid_path);
				free(cmd->tab_str);
				printf("Error : %s : failure execve\n", cmd->valid_path);
			}
		}
	}
	exit(1);
}

int	main(int ac, char **av, char **envp)
{
	t_list	*list;
	t_cmd	cmd;

	(void)ac;
	(void)av;
	list = malloc(sizeof(t_list));
	list = NULL;
	ft_create_list(&list);
	cmd.line_path = ft_get_line_path(envp);
	cmd.tab_path = ft_split(cmd.line_path, ':');
	ft_start_exec(list, &cmd, envp);
}