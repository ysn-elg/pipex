/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:57:55 by yel-guad          #+#    #+#             */
/*   Updated: 2025/02/12 22:42:42 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_cmd_not_found(char **cmds, char *cmd_path)
{
	if (!cmd_path)
	{
		write(2, "pipex: command not found: ", 26);
		write(2, cmds[0], ft_strlen(cmds[0]));
		write(2, "\n", 1);
	}
	else if (cmd_path[0] == '-')
		perror(cmds[0]);
	free_split(cmds);
	exit (127);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

// static char	*ft_strjoin1(char const *s1, char const *s2)
// {
// 	int		i;
// 	int		j;
// 	char	*res;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	i = 0;
// 	j = 0;
// 	res = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
// 	if (!res)
// 		return (NULL);
// 	while (s1[i])
// 		res[j++] = s1[i++];
// 	res[j++] = '/';
// 	i = 0;
// 	while (s2[i])
// 		res[j++] = s2[i++];
// 	res[j] = '\0';
// 	return (res);
// }

static char	*the_cmd_path(char *cmd, char **paths)
{
	int		i;
	char	*the_path;
	char	*tmp;

	i = 0;
	if (!cmd)
		return (NULL);
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		the_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!the_path)
			continue ;
		if (access(the_path, X_OK) == 0)
			return (the_path);
		free(the_path);
		i++;
	}
	return (NULL);
}

static char	*slashcmd(char *cmd)
{
	if (access(cmd, X_OK) == 0)
		return (cmd);
	else
		return ("-");
}

char	*get_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	*path_env;
	char	**paths;
	char	*cmd_path;

	i = 0;
	path_env = NULL;
	if (ft_strchr(cmd, '/'))
		return (slashcmd(cmd));
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path_env = envp[i] + 5;
			break ;
		}
		i++;
	}
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	cmd_path = the_cmd_path(cmd, paths);
	return (free_split(paths), cmd_path);
}
