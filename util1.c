/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 10:41:46 by yel-guad          #+#    #+#             */
/*   Updated: 2025/02/13 17:14:11 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_files(char *file, char c)
{
	int	fd;

	if (c == 'i')
		fd = open(file, O_RDONLY);
	else if (c == 'o')
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

int	last_state(pid_t pid_last)
{
	pid_t	pid;
	int		wstate;
	int		wstate_last;

	while (1)
	{
		pid = wait(&wstate);
		if (pid < 0)
			break ;
		if (pid == pid_last)
			wstate_last = WEXITSTATUS(wstate);
	}
	return (wstate_last);
}

void	execute_command(char *cmd, char **envp)
{
	char	**cmds;
	char	*cmd_path;

	cmds = ft_split(cmd, ' ');
	if (!cmds)
		return (perror("split"));
	if (!*cmds)
	{
		write(2, "pipex: empty command\n", 22);
		free_split(cmds);
		exit(1);
	}
	cmd_path = get_cmd_path(cmds[0], envp);
	if (!cmd_path || cmd_path[0] == '-')
		error_cmd_not_found(cmds, cmd_path);
	execve(cmd_path, cmds, envp);
	perror("execve failed");
	free_split(cmds);
	exit(EXIT_FAILURE);
}

int	here_doc_fun(char *limiter)
{
	int		fdp[2];
	char	*line;

	if (pipe(fdp) == -1)
		return (perror("pipe"), 1);
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(0);
		if (!ft_strncmp(line, limiter, ft_strlen(limiter))
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break ;
		}
		write(fdp[1], line, ft_strlen(line));
		free(line);
	}
	close(fdp[1]);
	return (fdp[0]);
}

void	print_error(char *hd)
{
	if (ft_strncmp(hd, "here_doc", 8))
		write(2, "Usage: ./pipex file1 cmd1 ... cmdN file2\n", 41);
	else
		write(2, "Usage: ./pipex here_doc LIMITER cmd cmd1 file\n", 47);
}
