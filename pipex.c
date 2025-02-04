/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:24:33 by yel-guad          #+#    #+#             */
/*   Updated: 2025/02/04 17:49:51 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int open_files(char *file, char c)
{
	int	fd;

	if (c == 'i')
		fd = open(file, O_RDONLY);
	else
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

static void	execute_command(char *cmd, char **envp)
{
	char	**cmds;
	char	*cmd_path;

	cmds = ft_split(cmd, ' ');
	if (!cmds)
	{
		perror("pipex: empty command\n");
		free_split(cmds);
		exit(1);
	}
	cmd_path = get_cmd_path(cmds[0], envp);
	if (!cmd_path)
	{
		write(2, "pipex: command not found: ", 26);
		write(2, cmds[0], ft_strlen(cmds[0]));
		write(2, "\n", 1);
		free_split(cmds);
		exit (127);
	}
	// Is directory
	// Not a directoy
	execve(cmd_path, cmds, envp);
	perror("execve failed");
	free_split(cmds);
	exit(EXIT_FAILURE);
}

static void	child_process(int read_fd, int fdp[2], char *cmd1, char **envp)
{
	dup2(read_fd, STDIN_FILENO);
	dup2(fdp[1], STDOUT_FILENO);
	close(read_fd);
	close(fdp[0]);
	close(fdp[1]);
	execute_command(cmd1, envp);
}

static void	last_child(int read_fd, char *file2, char *cmd2, char **envp)
{
	int	fd_out;

	fd_out = open_files(file2, 'o');
	dup2(read_fd, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	close(read_fd);
	execute_command(cmd2, envp);
}

void	here_doc_fun(char *limiter, int pipe_fd)
{
	char	*line;

	write(1, "pipe here_doc> ", 15);
	while ((line = get_next_line(0)))
	{
		if(!ft_strncmp(line, limiter, ft_strlen(limiter)))
		{
			free(line);
			break ;
		}
		write(pipe_fd, line, ft_strlen(line));
		free(line);
		write(1, "pipe here_doc> ", 15);
	}
	close(pipe_fd);
}

int main (int ac, char ** av, char **envp)
{
	pid_t	pid;
	int		fdp[2];
	int		read_fd;
	int		i;

	if (ac < 5)
		return (write(2, "Usage: ./pipex file1 cmd1 ... cmdN file2\n", 41), 1);
	if (!ft_strncmp(av[1], "here_doc", 8)) //////////////////////////////////////////////////
	{
		pipe(fdp);
		here_doc_fun(av[2], fdp[1]);
		read_fd = fdp[0];
		i = 3;
	}
	else
	{
		read_fd = open_files(av[1], 'i');
		i = 2;
	}
	while (i < ac -2)
	{
		if (pipe(fdp) == -1)
			return(perror("pipe"), 1);
		pid = fork();
		if (pid == -1)
			return(perror("fork"), 1);
		else if (pid == 0)
			child_process(read_fd, fdp, av[i], envp);
		close(read_fd);
		close(fdp[1]);
		read_fd = fdp[0];
		i++;
	}
	pid = fork();
	if (pid == -1)
		return(perror("fork"), 1);
	if (pid == 0)
		last_child(read_fd, av[ac -1], av[ac -2], envp);
	close(read_fd);
	close(fdp[0]);
	close(fdp[1]);
	while (wait(NULL) > 0);//////////////////////////////until false
	return (0);
}
