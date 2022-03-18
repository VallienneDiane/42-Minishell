/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvallien <dvallien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 14:47:22 by dvallien          #+#    #+#             */
/*   Updated: 2022/03/18 17:06:09 by dvallien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_list
{
	char			*content;
	char			*type;
	struct s_list	*next;
	struct s_list	*previous;
}	t_list;

typedef struct s_cmd
{
	char	*line_path;
	char	**tab_path;
	char	*valid_path;
	char	**tab_args;
	int		fd1;
	int		fd2;
}	t_cmd;

// DIANE //

int		main(int ac, char **av, char **env);

// Chained list
void	ft_create_list(t_list **list);
t_list	*ft_lstnew(void *content, void *type);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);
void	ft_print_list(t_list *list);

// Utils
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *src);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
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

// ALEXI //
void	ft_simple_quote(t_list **list, char *line, int i);

#endif