/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:42:11 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/22 13:09:56 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_start_exec(t_list *list, t_cmd *cmd)
{	
	int	i;
	int	current_block;
	pid_t pid;

	i = 0;
	current_block = 1;
	cmd->valid_path = NULL;
	while (list)
	{
		ft_get_args(list, cmd, current_block);
		if ((ft_is_builtin(cmd->tab_str[0]) == 0) && cmd->tab_str[0])
			cmd->valid_path = ft_access_path(cmd);
		while (list && list->block == current_block)
			list = list->next;
		if (list && list->block != current_block)
		{
			ft_exec_pipex(cmd);
			current_block++;
		}
		else
		{

			if (ft_is_builtin(cmd->tab_str[0]) == 0)
			{
				signal(SIGINT, ft_signal_exec_handler);
				pid = fork();
				g_pid = pid;
				if (pid < 0)
				{
					perror("");
					exit(EXIT_FAILURE);
				}
				if (pid == 0)
				{
					// if (ft_atoi(ft_getenv("SHLVL", cmd)) != 2)
					// 	signal(SIGINT, SIG_IGN);
					ft_execution(cmd);
				}
				else
				{
					if (ft_atoi(ft_getenv("SHLVL", cmd)) != 2)
					{
						// printf("ICI 1");
						ft_term_handler(1);
						signal(SIGINT, SIG_IGN);
						waitpid(pid, &errno, 0);
						
					}
					// else
					// {
						// printf("ICI 2");
						// signal(SIGINT, SIG_IGN);
						waitpid(pid, &errno, 0);
						signal(SIGINT, ft_signal_handler);
						
					// }
				}
			}
			else
				ft_exec_builtin(cmd);
		}
		// free les tabs
	}
}

void	ft_execution(t_cmd *cmd)
{
	if (cmd->tab_redir_in[0] || cmd->tab_redir_out1[0] \
	|| cmd->tab_redir_out2[0])
	{
		ft_redir_dup(cmd);
	}
	else
		ft_execute(cmd);
}

void	ft_execute(t_cmd *cmd)
{
	char	**env_tab;
	
	if (ft_is_builtin(cmd->tab_str[0]))
		ft_exec_builtin(cmd);
	if (cmd->valid_path != NULL && ft_is_builtin(cmd->tab_str[0]) == 0)
	{
		if (cmd->tab_str[0])
		{
			env_tab = ft_env_to_tab(cmd);
			execve(cmd->valid_path, cmd->tab_str, env_tab);
		}
	}
	exit(1);
}
