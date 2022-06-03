/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:10:39 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/04 04:56:24 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	child_process(char **argv, char **envp, int pipe_fd[2]);
static void	parent_process(char **argv, char **envp, int pipe_fd[2]);
static void	display_usage_with_exit(void);

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (argc != 5)
		display_usage_with_exit();
	if (pipe(pipe_fd) == FAIL)
		perror_with_exit("pipe");
	pid = fork();
	if (pid == FAIL)
		perror_with_exit("fork");
	if (pid == CPID)
		child_process(argv, envp, pipe_fd);
	else
	{
		if (waitpid(pid, NULL, 0) == FAIL)
			perror_with_exit("waitpid");
		parent_process(argv, envp, pipe_fd);
	}
	return (EXIT_SUCCESS);
}

static void	child_process(char **argv, char **envp, int pipe_fd[2])
{
	int	in_file_fd;

	in_file_fd = open(argv[1], O_RDONLY, 0777);
	if (in_file_fd == FAIL)
		perror_with_exit("open");
	close(pipe_fd[PIPE_IN_FD]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(pipe_fd[PIPE_OUT_FD], STDOUT_FILENO);
	close(pipe_fd[PIPE_OUT_FD]);
	dup2(in_file_fd, STDIN_FILENO);
	close(in_file_fd);
	execute(argv[2], envp);
}

static void	parent_process(char **argv, char **envp, int pipe_fd[2])
{
	int	out_file_fd;

	out_file_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (out_file_fd == FAIL)
		perror_with_exit("open");
	close(pipe_fd[PIPE_OUT_FD]);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(pipe_fd[PIPE_IN_FD], STDIN_FILENO);
	close(pipe_fd[PIPE_IN_FD]);
	dup2(out_file_fd, STDOUT_FILENO);
	close(out_file_fd);
	execute(argv[3], envp);
}

static void	display_usage_with_exit(void)
{
	ft_putstr_fd(ESC_CLR_RED, STDERR_FILENO);
	perror(ARG_ERR_MSG);
	ft_putstr_fd(ESC_RESET, STDERR_FILENO);
	ft_putstr_fd("Usage: ./pipex <infile> <cmd1> <cmd2> <outfile>\n",
		STDOUT_FILENO);
	exit(EXIT_FAILURE);
}
