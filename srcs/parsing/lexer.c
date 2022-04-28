/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 10:56:24 by amarchal          #+#    #+#             */
/*   Updated: 2022/04/28 17:39:55 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
	p_info.error = 0;
	p_info.cmd = cmd;
	while (line[p_info.i])
	{
		while (line[p_info.i] && line[p_info.i] == ' ')
			p_info.i++;
		if (line[p_info.i])
			ft_lexer(list, line, &p_info);
	}
	if (p_info.error)
		cmd->parse_error = 1;
	else
		cmd->parse_error = 0;
}

int	ft_content_size(char *line, t_pars_info *p_info)
{
	int	size;

	size = 0;
	while (line[p_info->j] && line[p_info->j] != ' ' && line[p_info->j] != '<'
		&& line[p_info->j] != '>' && line[p_info->j] != '|')
	{
		if (line[p_info->j] == '$' && p_info->current_type != HEREDOC)
			size += ft_env_size(line, p_info);
		else if (line[p_info->j] == '\'')
			size += ft_s_quote_size(line, p_info);
		else if (line[p_info->j] == '\"')
			size += ft_d_quote_size(line, p_info);
		else
		{
			size++;
			p_info->j++;
		}
	}
	p_info->cur_cont_size = size;
	return (size);
}

char	*ft_fill_content(char *content, char *line,
	t_pars_info *p_info, t_list **list)
{
	p_info->j = 0;
	while (line[p_info->i] && line[p_info->i] != ' ' && line[p_info->i] != '<'
		&& line[p_info->i] != '>' && line[p_info->i] != '|')
	{
		if (line[p_info->i] == '$' && line[p_info->i + 1]
			&& line[p_info->i + 1] != ' ' && p_info->current_type != HEREDOC)
		{
			content = ft_join_env(line, content, list, p_info);
			if (content[ft_strlen(content) - 1] == ' ')
				return (content);
		}
		else if (line[p_info->i] == '\'')
			content = ft_join_s_quote(line, content, p_info);
		else if (line[p_info->i] == '\"')
			content = ft_join_d_quote(line, content, list, p_info);
		else
		{
			content[p_info->j++] = line[p_info->i];
			p_info->i += 1;
		}
	}
	content[p_info->j] = '\0';
	return (content);
}

int	ft_str(t_list **list, char *line, t_pars_info *p_info)
{
	int		k;
	char	*content;

	p_info->j = p_info->i;
	k = -1;
	content = ft_calloc(sizeof(char), ft_content_size(line, p_info) + 1);
	content = ft_fill_content(content, line, p_info, list);
	ft_lstadd_back(list, ft_lstnew(content,
			p_info->current_type, p_info->current_block));
	p_info->d_quote = 0;
	p_info->current_type = STR;
	return (p_info->i);
}
