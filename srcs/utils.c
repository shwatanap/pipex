/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:49:33 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/04 02:07:28 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	perror_with_exit(const char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}

static void	split_free(char **strs)
{
	size_t	i;

	i = 0;
	while (strs[i] != NULL)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;
	char	*cmd_dir;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (paths == NULL)
		perror_with_exit("ft_split");
	i = 0;
	while (paths[i])
	{
		cmd_dir = ft_strjoin(paths[i], "/");
		if (cmd_dir == NULL)
			perror_with_exit("ft_strjoin");
		path = ft_strjoin(cmd_dir, cmd);
		if (path == NULL)
			perror_with_exit("ft_strjoin");
		free(cmd_dir);
		if (access(path, F_OK) == SUCCESS)
		{
			split_free(paths);
			return (path);
		}
		free(path);
		i++;
	}
	perror_with_exit("cmd not found");
	return (NULL);
}

void	execute(char *argv, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(argv, ' ');
	if (cmd == NULL)
		perror_with_exit("split");
	path = find_path(cmd[0], envp);
	if (execve(path, cmd, envp) == FAIL)
		perror_with_exit("execve");
	split_free(cmd);
}
