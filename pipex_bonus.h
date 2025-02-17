/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:43:19 by yel-guad          #+#    #+#             */
/*   Updated: 2025/02/14 10:36:13 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
// # include <sys/stat.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

int		open_files(char *file, char c);
void	execute_command(char *cmd, char **envp);
char	**ft_split(const char *s, char c);
char	*get_cmd_path(char *cmd, char **envp);
void	free_split(char **array);
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		last_state(pid_t pid_last);
int		here_doc_fun(char *limiter);
void	print_error(char **av);
void	error_cmd_not_found(char **cmds, char *cmd_path);
char	*get_next_line(int fd);
char	*get_the_line(char *buff);
char	*get_linee(int fd, char *res);
char	*get_rest(char *buff);
char	*ft_strdup(const char *s1);
char	*ft_substr(const char *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);

#endif
