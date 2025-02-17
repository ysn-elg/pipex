/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 10:24:33 by yel-guad          #+#    #+#             */
/*   Updated: 2025/02/14 10:25:21 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	child_process(int read_fd, int fdp[2], char *cmd, char **envp)
{
	dup2(read_fd, STDIN_FILENO);
	dup2(fdp[1], STDOUT_FILENO);
	close(read_fd);
	close(fdp[0]);
	close(fdp[1]);
	execute_command(cmd, envp);
}

static void	do_pipes(int *read_fd, char *cmd, char **env, char **file1)
{
	pid_t	pid;
	int		fdp[2];

	if (pipe(fdp) == -1)
		return (perror("pipe"));
	pid = fork();
	if (pid == -1)
		return (perror("fork"));
	else if (pid == 0)
	{
		if (*file1 != NULL)
			*read_fd = open_files(*file1, 'i');
		child_process(*read_fd, fdp, cmd, env);
	}
	if (*read_fd != -1)
		close(*read_fd);
	close(fdp[1]);
	*read_fd = fdp[0];
	*file1 = NULL;
}

static void	execute_last_child(int read_fd, int ac, char **av, char **env)
{
	int	fd_out;

	if (!ft_strncmp(av[1], "here_doc", 9))
		fd_out = open_files(av[ac -1], 'h');
	else
		fd_out = open_files(av[ac -1], 'o');
	dup2(read_fd, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_out);
	close(read_fd);
	execute_command(av[ac -2], env);
}

static pid_t	last_child(int read_fd, int ac, char **av, char **env)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (perror("fork"), 1);
	if (pid == 0)
		execute_last_child(read_fd, ac, av, env);
	close(read_fd);
	return (pid);
}

int	main(int ac, char **av, char **env)
{
	pid_t	pid_last;
	int		read_fd;
	int		i;
	char	*file1;

	if (ac < 5)
		return (print_error(av), 1);
	file1 = av[1];
	i = 2;
	read_fd = -1;
	if (!ft_strncmp(av[1], "here_doc", 9))
	{
		if (ac != 6)
			return (print_error(av), 1);
		read_fd = here_doc_fun(av[2]);
		file1 = NULL;
		i = 3;
	}
	while (i < ac -2)
		do_pipes(&read_fd, av[i++], env, &file1);
	pid_last = last_child(read_fd, ac, av, env);
	return (last_state(pid_last));
}
