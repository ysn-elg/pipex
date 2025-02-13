/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:43:19 by yel-guad          #+#    #+#             */
/*   Updated: 2025/02/13 16:16:01 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "get_next_line/get_next_line.h"

int		open_files(char *file, char c);
void	execute_command(char *cmd, char **envp);
char	**ft_split(const char *s, char c);
char	*get_cmd_path(char *cmd, char **envp);
void	free_split(char **array);
int		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		last_state(pid_t pid_last);
int		here_doc_fun(char *limiter);
void	print_error(char *hd);
void	error_cmd_not_found(char **cmds, char *cmd_path);

#endif
