/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:43:19 by yel-guad          #+#    #+#             */
/*   Updated: 2025/02/02 09:53:05 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

char	**ft_split(const char *s, char c);
char	*get_cmd_path(char *cmd, char **envp);
void	free_split(char **array);
int	    ft_strlen(const char *s);

#endif
