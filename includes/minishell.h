/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchal <amarchal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 16:36:19 by dvallien          #+#    #+#             */
/*   Updated: 2022/04/05 15:39:05 by amarchal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"

# define STR 0
# define REDIR_IN 1
# define HEREDOC 2
# define REDIR_OUT 3
# define REDIR_CONC 4

int	errno;

typedef struct s_list
{
	char			*content;
	char			*str;
	int				type;
	int				block;
	struct s_list	*previous;
	struct s_list	*next;
}	t_list;

typedef struct s_pars_info
{
	int		i;
	int		j;
	int		current_type;
	int		current_block;
	int		d_quote;
	int		bracket;
	int		cur_cont_size;
}	t_pars_info;

typedef struct s_cmd
{
	char		*line_path;
	char		**tab_path;
	char		*valid_path;
	int			fd1;
	int			fd2;
}	t_cmd;

// Execution Diane //
// Principal
int		main(int ac, char **av, char **env);

// Chained list
void	ft_create_list(t_list **list);
t_list	*ft_lstnew(char *content, int type, int block);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_print_list(t_list *list);

// Utils
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_strjoin_content(char *s1, char *s2);
char	*ft_strjoin(char *s1, char *s2);
char	**ft_split(char const *s, char c);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);

// Parse type
void	ft_parse_type(t_list *list, t_cmd *cmd, char **envp);

// Access path
char	*ft_access_path(t_list *list, t_cmd *cmd);
char	*ft_get_line_path(char **envp);
void	ft_process(t_list *list, t_cmd *cmd, char **envp);

//Parsing Alexi //
int		ft_simple_quote(t_list **list, char *line, int *i);
int		ft_double_quote(t_list **list, char *line, int *i);
int		ft_var_env(t_list **list, char *line, int *i);
int		ft_str(t_list **list, char *line, t_pars_info *p_info);

int		ft_s_quote_size(char *line, t_pars_info *p_info);
char	*ft_join_s_quote(char *line, char *content, t_pars_info *p_info);
int		ft_d_quote_size(char *line, t_pars_info *p_info);
char	*ft_join_d_quote(char *line, char *content, t_list **list, t_pars_info *p_info);

int		ft_is_valid(char c);
int		ft_env_size(char *line, t_pars_info *p_info);
char	*ft_env_name(char *line, t_pars_info *p_info);
char	*ft_join_env(char *line, char *content, t_list **list, t_pars_info *p_info);

void	ft_redir_out(char *line, t_pars_info *p_info);
void	ft_redir_in(char *line, t_pars_info *p_info);

int		ft_content_size(char *line, t_pars_info *p_info);

#endif