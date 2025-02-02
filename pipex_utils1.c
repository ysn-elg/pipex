/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-guad <yel-guad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:57:55 by yel-guad          #+#    #+#             */
/*   Updated: 2025/02/02 11:32:17 by yel-guad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	res = (char *) malloc((ft_strlen(s1) + ft_strlen(s2) + 2) * sizeof(char));
	if (!res)
		return (NULL);
	while (s1[i])
		res[j++] = s1[i++];
	res[j++] = '/';
	i = 0;
	while (s2[i])
		res[j++] = s2[i++];
	res[j] = '\0';
	return (res);
}

static char	*the_cmd_path(char *cmd, char **paths)
{
	int		i;
	char	*the_path;

	i = 0;
	if (!cmd)
		return (NULL);
	while (paths[i])
	{
		the_path = ft_strjoin(paths[i], cmd);
		if (!the_path)
			continue; // learn more
		if (access(the_path, X_OK) == 0)
			return(the_path);
		free(the_path);
		i++;
	}
	return (NULL);
}

char	*get_cmd_path(char *cmd, char **envp)
{
	int		i;
	char	*path_env;
	char	**paths;
	char	*cmd_path;

	i = 0;
	path_env = NULL;
	if (access(cmd, X_OK) == 0)
		return (cmd);
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
	free_split(paths);
	return (cmd_path);
}
