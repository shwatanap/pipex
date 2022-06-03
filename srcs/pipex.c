/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:10:39 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/03 22:22:37 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(char **argv, char **envp, int pipe_fd[2]);
void	parent_process(char **argv, char **envp, int pipe_fd[2]);

int	main(int argc, char **argv, char **envp)
{
	int		pipe_fd[2];
	pid_t	pid;

	(void)argv;
	if (argc != 5)
	{
		ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", STDERR_FILENO);
		ft_putstr_fd("Usage: ./pipex <infile> <cmd1> <cmd2> <outfile>\n",
						STDOUT_FILENO);
		return (1);
	}
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
}

void	child_process(char **argv, char **envp, int pipe_fd[2])
{
	int	in_fd;

	in_fd = open(argv[1], O_RDONLY, 0777);
	if (in_fd == FAIL)
		perror_with_exit("open");
	close(pipe_fd[0]);
	dup2(pipe_fd[1], STDOUT_FILENO);
	dup2(in_fd, STDIN_FILENO);
	close(pipe_fd[1]);
	execute(argv[2], envp);
}

void	parent_process(char **argv, char **envp, int pipe_fd[2])
{
	int	out_fd;

	out_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (out_fd == FAIL)
		perror_with_exit("open");
	close(pipe_fd[1]);
	dup2(pipe_fd[0], STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	close(pipe_fd[0]);
	execute(argv[3], envp);
}
