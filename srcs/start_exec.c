/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 11:42:11 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/22 17:40:18 by amarchal         ###   ########.fr       */
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
				if (pid < 0)
				{
					perror("");
					exit(EXIT_FAILURE);
				}
				if (pid == 0)
					ft_execution(cmd);
				else
				{
					if (ft_atoi(ft_getenv("SHLVL", cmd)) != 2)
					{
						ft_term_handler(1);
						signal(SIGINT, SIG_IGN);
						waitpid(pid, &g_status, 0);
					}
					printf("g_status avt : %d\n", g_status);
					int test = WEXITSTATUS(g_status);
					printf("test apr : %d\n", test);
					waitpid(pid, &g_status, 0);
					printf("g_status apr : %d\n", g_status);
					test = WEXITSTATUS(g_status);
					printf("test apr : %d\n", test);
					signal(SIGINT, ft_signal_handler);
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
	printf("CHOUETTE\n");
	if (cmd->valid_path)
		exit (126);
	else
		exit (127);
}
