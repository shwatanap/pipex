/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 03:40:55 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/09 11:44:59 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static int	input_process(int argc, char **argv, int (*file_fd)[2]);
static void	child_process(char *cmd, char **envp, int *use_fd, int pipe_in_fd);

int	main(int argc, char **argv, char **envp)
{
	int	arg_idx;
	int	file_fd[2];
	int	pipe_fd[2];
	int	use_fd[2];

	if (argc < 5)
		display_usage_with_exit();
	arg_idx = input_process(argc, argv, &file_fd);
	while (arg_idx < argc - 1)
	{
		if (arg_idx != 2)
		{
			close(use_fd[0]);
			close(use_fd[1]);
		}
		use_fd[0] = pipe_fd[0];
		use_fd[1] = pipe_fd[1];
		// TODO: heredocにも対応させる
		if (pipe(pipe_fd) == FAIL)
			perror_with_exit("pipe");
		if (arg_idx == 2)
		{
			use_fd[0] = file_fd[0];
			use_fd[1] = pipe_fd[1];
		}
		else if (arg_idx == argc - 2)
			use_fd[1] = file_fd[1];
		else
			use_fd[1] = pipe_fd[1];
		child_process(argv[arg_idx], envp, use_fd, pipe_fd[PIPE_IN_FD]);
		// なぜか必要
		close(use_fd[0]);
		close(use_fd[1]);
		arg_idx++;
	}
	close(file_fd[0]);
	close(file_fd[1]);
	while (wait(NULL) != FAIL)
		;
}

static int	input_process(int argc, char **argv, int (*file_fd)[2])
{
	int	first_cmd_idx;

	if (ft_strncmp(argv[1], HERE_DOG_STR, HERE_DOG_STR_LEN) == SUCCESS)
	{
		if (argc < 6)
			display_usage_with_exit();
		(*file_fd)[1] = open_file(argv[argc - 1], FILE_APPEND_WRITE);
		// TODO: here_docのinfile対応
		here_doc(argv[2]);
		first_cmd_idx = 3;
		return (first_cmd_idx);
	}
	(*file_fd)[0] = open_file(argv[1], FILE_READ);
	(*file_fd)[1] = open_file(argv[argc - 1], FILE_OVER_WRITE);
	first_cmd_idx = 2;
	return (first_cmd_idx);
}

static void	child_process(char *cmd, char **envp, int *use_fd, int pipe_in_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == FAIL)
		perror_with_exit("fork");
	if (pid == CPID)
	{
		close(pipe_in_fd);
		close(STDOUT_FILENO);
		close(STDIN_FILENO);
		dup2(use_fd[0], STDIN_FILENO);
		dup2(use_fd[1], STDOUT_FILENO);
		close(use_fd[0]);
		close(use_fd[1]);
		execute(cmd, envp);
	}
}
