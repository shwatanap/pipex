/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 03:40:55 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/09 12:39:41 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static int	input_process(int argc, char **argv, int (*file_fd)[2]);
static void	exec_process(t_main_arg *main_arg, int arg_idx, int file_fd[2]);
static void	child_process(char *cmd, char **envp, int *use_fd, int pipe_in_fd);

void	set_main_arg_struct(int argc, char **argv, char **envp,
		t_main_arg *main_arg)
{
	main_arg->argc = argc;
	main_arg->argv = argv;
	main_arg->envp = envp;
}

int	main(int argc, char **argv, char **envp)
{
	int			arg_idx;
	int			file_fd[2];
	t_main_arg	main_arg;

	set_main_arg_struct(argc, argv, envp, &main_arg);
	if (argc < 5)
		display_usage_with_exit();
	arg_idx = input_process(argc, argv, &file_fd);
	while (arg_idx < argc - 1)
	{
		exec_process(&main_arg, arg_idx, file_fd);
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

static void	exec_process(t_main_arg *main_arg, int arg_idx, int file_fd[2])
{
	int	use_fd[2];
	int	pipe_fd[2];

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
	else if (arg_idx == main_arg->argc - 2)
		use_fd[1] = file_fd[1];
	else
		use_fd[1] = pipe_fd[1];
	child_process(main_arg->argv[arg_idx], main_arg->envp, use_fd,
			pipe_fd[PIPE_IN_FD]);
	// なぜか必要
	close(use_fd[0]);
	close(use_fd[1]);
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
