/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 03:40:55 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/16 12:23:00 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static int	input_process(int argc, char **argv, int (*file_fd)[2]);
static void	exec_process(t_main_arg *main_arg, int arg_idx, int file_fd[2],
				bool is_first_process);
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
	bool		is_first_process;
	t_main_arg	main_arg;

	set_main_arg_struct(argc, argv, envp, &main_arg);
	if (argc < 5)
		display_usage_with_exit();
	arg_idx = input_process(argc, argv, &file_fd);
	is_first_process = true;
	while (arg_idx < argc - 1)
	{
		exec_process(&main_arg, arg_idx, file_fd, is_first_process);
		is_first_process = false;
		arg_idx++;
	}
	close(file_fd[IN_FD]);
	close(file_fd[OUT_FD]);
	while (wait(NULL) != FAIL)
		;
}

static int	input_process(int argc, char **argv, int (*file_fd)[2])
{
	int	first_cmd_idx;

	if ((ft_strncmp(argv[1], HERE_DOG_STR, HERE_DOG_STR_LEN) == SUCCESS)
		&& argv[1][HERE_DOG_STR_LEN] == '\0')
	{
		if (argc < 6)
			display_usage_with_exit();
		(*file_fd)[OUT_FD] = open_file(argv[argc - 1], FILE_APPEND_WRITE);
		(*file_fd)[IN_FD] = here_doc(argv[2]);
		first_cmd_idx = 3;
		return (first_cmd_idx);
	}
	(*file_fd)[IN_FD] = open_file(argv[1], FILE_READ);
	(*file_fd)[OUT_FD] = open_file(argv[argc - 1], FILE_OVER_WRITE);
	first_cmd_idx = 2;
	return (first_cmd_idx);
}

static void	exec_process(t_main_arg *main_arg, int arg_idx, int file_fd[2],
		bool is_first_process)
{
	int	use_fd[2];
	int	pipe_fd[2];

	if (!is_first_process)
	{
		close(use_fd[IN_FD]);
		close(use_fd[OUT_FD]);
	}
	use_fd[IN_FD] = pipe_fd[IN_FD];
	use_fd[OUT_FD] = pipe_fd[OUT_FD];
	if (pipe(pipe_fd) == FAIL)
		perror_with_exit("pipe");
	if (is_first_process)
	{
		use_fd[IN_FD] = file_fd[IN_FD];
		use_fd[OUT_FD] = pipe_fd[OUT_FD];
	}
	else if (arg_idx == main_arg->argc - 2)
		use_fd[OUT_FD] = file_fd[OUT_FD];
	else
		use_fd[OUT_FD] = pipe_fd[OUT_FD];
	child_process(main_arg->argv[arg_idx], main_arg->envp, use_fd,
		pipe_fd[IN_FD]);
}

static void	child_process(char *cmd, char **envp, int *use_fd, int pipe_in_fd)
{
	pid_t	pid;

	pid = fork();
	if (pid == FAIL)
		perror_with_exit("fork");
	if (pid == CPID)
	{
		if (use_fd[IN_FD] == FAIL)
			perror_with_exit("infile");
		close(pipe_in_fd);
		close(STDOUT_FILENO);
		close(STDIN_FILENO);
		dup2(use_fd[IN_FD], STDIN_FILENO);
		dup2(use_fd[OUT_FD], STDOUT_FILENO);
		close(use_fd[IN_FD]);
		close(use_fd[OUT_FD]);
		execute(cmd, envp);
	}
	close(use_fd[IN_FD]);
	close(use_fd[OUT_FD]);
}
