/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 14:00:34 by amarchal          #+#    #+#             */
/*   Updated: 2022/04/22 16:50:41 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_join_full_env(char *content, char *env_name, t_pars_info *p_info)
{
	ft_strjoin_content(content, ft_getenv(env_name, p_info->cmd));
	free(env_name);
	p_info->j += ft_strlen(ft_getenv(env_name, p_info->cmd));
	return (content);
}

char	*ft_join_split_env(char **sub_env, char *content,
	t_list **list, t_pars_info *p_info)
{
	int		k;
	char	*new_content;

	k = 1;
	ft_strjoin_content(content, sub_env[0]);
	ft_lstadd_back(list, ft_lstnew(content,
			p_info->current_type, p_info->current_block));
	while (sub_env[k + 1])
		ft_lstadd_back(list, ft_lstnew(sub_env[k++],
				p_info->current_type, p_info->current_block));
	new_content = ft_calloc(sizeof(char), p_info->cur_cont_size + 1);
	ft_strjoin_content(new_content, sub_env[k]);
	p_info->j = ft_strlen(new_content);
	free(sub_env);
	return (new_content);
}

char	*ft_errno_join(char *content, t_pars_info *p_info)
{
	char	*errno_str;

	errno_str = ft_itoa(WEXITSTATUS(g_status));
	ft_strjoin_content(content, errno_str);
	p_info->j += ft_strlen(errno_str);
	free(errno_str);
	return (content);
}

char	*ft_join_env(char *line, char *content,
	t_list **list, t_pars_info *p_info)
{
	char	*env_name;
	char	**sub_env;

	env_name = ft_env_name(line, p_info);
	if (ft_strcmp(env_name, "?") == 0)
		return (ft_errno_join(content, p_info));
	if (ft_getenv(env_name, p_info->cmd))
	{
		if (p_info->current_type != STR || p_info->d_quote)
			return (ft_join_full_env(content, env_name, p_info));
		sub_env = ft_split(ft_getenv(env_name, p_info->cmd), ' ');
		if (ft_strlen2d(sub_env) > 1)
		{
			free(env_name);
			return (ft_join_split_env(sub_env, content, list, p_info));
		}
		free(sub_env);
		ft_strjoin_content(content, ft_getenv(env_name, p_info->cmd));
		p_info->j += ft_strlen(ft_getenv(env_name, p_info->cmd));
	}
	free(env_name);
	return (content);
}
