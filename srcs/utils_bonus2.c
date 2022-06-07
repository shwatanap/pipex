/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:49:33 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/07 23:27:51 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

void		perror_with_exit(const char *str);
static char	*make_cmd_path(char *path, char *cmd);
static char	*find_path(char *cmd, char **envp);
static void	split_free(char **strs);

void	execute(char *arg, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = cmd_parse(arg);
	if (cmd == NULL)
		perror_with_exit("cmd_parse");
	path = find_path(cmd[0], envp);
	if (execve(path, cmd, envp) == FAIL)
		perror_with_exit("execve");
}

void	perror_with_exit(const char *str)
{
	ft_putstr_fd(ESC_CLR_RED, STDERR_FILENO);
	perror(str);
	ft_putstr_fd(ESC_RESET, STDERR_FILENO);
	exit(EXIT_FAILURE);
}

static char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (envp[i] != NULL && ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	if (paths == NULL)
		perror_with_exit("ft_split");
	i = 0;
	while (paths[i])
	{
		path = make_cmd_path(paths[i], cmd);
		if (access(path, F_OK) == SUCCESS)
		{
			split_free(paths);
			return (path);
		}
		free(path);
		i++;
	}
	perror("cmd not found");
	exit(EXIT_CMD_NOT_FOUND);
}

static char	*make_cmd_path(char *path, char *cmd)
{
	char	*cmd_dir;
	char	*cmd_path;

	cmd_dir = ft_strjoin(path, "/");
	if (cmd_dir == NULL)
		perror_with_exit("ft_strjoin");
	cmd_path = ft_strjoin(cmd_dir, cmd);
	if (cmd_path == NULL)
		perror_with_exit("ft_strjoin");
	free(cmd_dir);
	return (cmd_path);
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
