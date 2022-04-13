/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:45:02 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/13 17:29:02 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_pipe(char *line, t_pars_info *p_info)
{
	int	j;

	j = p_info->i + 1;
	while (line[j] == ' ')
		j++;
	if (!line[j] || line[j] == '|')
	{
		printf("Pipe error\n");
		exit(EXIT_FAILURE); ///////
	}
	p_info->current_block++;
	p_info->i += 1;
}

void	ft_lexer(t_list **list, char *line, t_pars_info *p_info)
{
	if (line[p_info->i] == '<')
		ft_redir_in(line, p_info);
	else if (line[p_info->i] == '>')
		ft_redir_out(line, p_info);
	else if (line[p_info->i] == '|')
		ft_pipe(line, p_info);
	else
		p_info->i = ft_str(list, line, p_info);
}

void	ft_parsing(t_list **list, char *line, t_cmd *cmd)
{
	t_pars_info	p_info;

	p_info.i = 0;
	p_info.current_type = STR;
	p_info.current_block = 1;
	p_info.d_quote = 0;
	p_info.cmd = cmd;
	while (line[p_info.i])
	{
		while (line[p_info.i] && line[p_info.i] == ' ')
			p_info.i++;
		if (line[p_info.i])
			ft_lexer(list, line, &p_info);
	}
}

char	**ft_cpy_env(char **env)
{
	char	**env_cpy;
	size_t	i;

	i = 0;
	env_cpy = malloc(sizeof(char *) * (ft_strlen2d(env) + 1));
	if (!env_cpy)
		exit(EXIT_FAILURE);
	while (env[i])
	{
		env_cpy[i] = ft_strdup(env[i]);
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

int	main(int ac, char **av, char **env)
{
	char 	*line;
	pid_t	pid;
	t_list	*list;
	t_cmd	cmd;
	
	errno = 0;
	cmd.env_cpy = ft_cpy_env(env);
	while (1)
	{
		list = malloc(sizeof(t_list));
		list = NULL;
		line = readline("minishell$ ");
		if (line[0])
			add_history(line);
		ft_parsing(&list, line, &cmd);
		free(line);
		// ft_print_list(list);
		cmd.line_path = ft_get_line_path(env);
		cmd.tab_path = ft_split(cmd.line_path, ':');
		pid = fork();
		if (pid < 0)
		{
			perror("");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			ft_start_exec(list, &cmd, env);
		else
			waitpid(pid, NULL, 0);
		free(list);
	}
	(void)ac;
	(void)av;
	(void)env;
}
