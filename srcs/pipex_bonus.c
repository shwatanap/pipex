/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 03:40:55 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/04 23:10:12 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static int	input_process(int argc, char **argv, int *out_file_fd);
static void	here_doc(char *limiter);
static void	here_doc_child_process(int pipe_fd[2], char *limiter);
static void	child_process(char *cmd, char **envp);

int	main(int argc, char **argv, char **envp)
{
	int	arg_idx;
	int	out_file_fd;

	if (argc >= 5)
	{
		arg_idx = input_process(argc, argv, &out_file_fd);
		while (arg_idx < argc - 2)
			child_process(argv[arg_idx++], envp);
		close(STDOUT_FILENO);
		dup2(out_file_fd, STDOUT_FILENO);
		close(out_file_fd);
		execute(argv[argc - 2], envp);
	}
	display_usage_with_exit();
}

static int	input_process(int argc, char **argv, int *out_file_fd)
{
	int	in_file_fd;
	int	first_cmd_idx;

	if (ft_strncmp(argv[1], HERE_DOG_STR, HERE_DOG_STR_LEN) == SUCCESS)
	{
		if (argc < 6)
			display_usage_with_exit();
		*out_file_fd = open_file(argv[argc - 1], FILE_APPEND_WRITE);
		here_doc(argv[2]);
		first_cmd_idx = 3;
		return (first_cmd_idx);
	}
	*out_file_fd = open_file(argv[argc - 1], FILE_OVER_WRITE);
	in_file_fd = open_file(argv[1], FILE_READ);
	close(STDIN_FILENO);
	dup2(in_file_fd, STDIN_FILENO);
	close(in_file_fd);
	first_cmd_idx = 2;
	return (first_cmd_idx);
}

static void	here_doc(char *limiter)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == FAIL)
		perror_with_exit("pipe");
	pid = fork();
	if (pid == FAIL)
		perror_with_exit("fork");
	if (pid == CPID)
		here_doc_child_process(pipe_fd, limiter);
	close(pipe_fd[PIPE_OUT_FD]);
	close(STDIN_FILENO);
	dup2(pipe_fd[PIPE_IN_FD], STDIN_FILENO);
	close(pipe_fd[PIPE_IN_FD]);
	wait(NULL);
}

static void	here_doc_child_process(int pipe_fd[2], char *limiter)
{
	char	*line;

	line = NULL;
	close(pipe_fd[PIPE_IN_FD]);
	while (!ft_read_line(&line))
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == SUCCESS
			&& line[ft_strlen(limiter)] == '\n')
			exit(EXIT_SUCCESS);
		ft_putstr_fd(line, pipe_fd[PIPE_OUT_FD]);
		free(line);
		line = NULL;
	}
	exit(EXIT_FAILURE);
}

static void	child_process(char *cmd, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (pipe(pipe_fd) == FAIL)
		perror_with_exit("pipe");
	pid = fork();
	if (pid == FAIL)
		perror_with_exit("fork");
	if (pid == CPID)
	{
		close(pipe_fd[PIPE_IN_FD]);
		close(STDOUT_FILENO);
		dup2(pipe_fd[PIPE_OUT_FD], STDOUT_FILENO);
		close(pipe_fd[PIPE_OUT_FD]);
		execute(cmd, envp);
	}
	if (waitpid(pid, NULL, 0) == FAIL)
		perror_with_exit("waitpid");
	close(pipe_fd[PIPE_OUT_FD]);
	close(STDIN_FILENO);
	dup2(pipe_fd[PIPE_IN_FD], STDIN_FILENO);
	close(pipe_fd[PIPE_IN_FD]);
}
