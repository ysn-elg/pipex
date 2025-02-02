/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:24:33 by yel-guad          #+#    #+#             */
/*   Updated: 2025/02/02 11:40:41 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int open_files(char *file, char c)
{
	int	fd;

	if (c == 'i')
		fd = open(file, O_RDONLY);
	else if (c == 'o')
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
		perror("error split");
		exit(1);
	}
	cmd_path = get_cmd_path(cmds[0], envp);
	if (!cmd_path || !*cmds)
	{
		write(2, "pipex: command not found: ", 26);
		write(2, cmds[0], ft_strlen(cmds[0]));
		write(2, "\n", 1);
		free_split(cmds);
		exit (127);
	}
	execve(cmd_path, cmds, envp);
	perror("execve failed");
	free_split(cmds);
	exit(EXIT_FAILURE);
}

static void	child_process(char *file1, int fdp[2], char *cmd1, char **envp)
{
	int	fd_in;
	
	fd_in = open_files(file1, 'i');
	dup2(fd_in, STDIN_FILENO);
	dup2(fdp[1], STDOUT_FILENO);
	close(fd_in);
	close(fdp[0]);
	close(fdp[1]);
	execute_command(cmd1, envp);
}

static void	parent_process(char *file2, int fdp[2], char *cmd2, char **envp)
{
	int	fd_out;

	fd_out = open_files(file2, 'o');
	dup2(fd_out, STDOUT_FILENO);
	dup2(fdp[0], STDIN_FILENO);
	close(fd_out);
	close(fdp[1]);
	close(fdp[0]);
	execute_command(cmd2, envp);
}

int main (int ac, char ** av, char **envp)
{
	pid_t	pid;
	int		fdp[2];

	if (ac != 5)
		return (write(2, "Usage form: ./pipex file1 cmd1 cmd2 file2\n", 42), 1); // better to use a function
	if (pipe(fdp) == -1)
		return(perror("pipe"), 1);
	pid = fork();
	if (pid == -1)
		return(perror("fork"), 1);
	if (pid == 0)
		child_process(av[1], fdp, av[2], envp);
	else
	{
		waitpid(pid, NULL, 0);
		parent_process(av[4], fdp, av[3], envp);
	}
	return (0);
}
