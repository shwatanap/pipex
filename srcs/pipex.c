/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:10:39 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/03 21:13:25 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	child_process(char **argv, char **envp, int fd[2]);
void	parent_process(char **argv, char **envp, int fd[2]);

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	pid_t	pid;

	(void)argv;
	if (argc != 5)
	{
		ft_putstr_fd("\033[31mError: Bad arguments\n\e[0m", STDERR_FILENO);
		ft_putstr_fd("Usage: ./pipex <infile> <cmd1> <cmd2> <outfile>\n",
			STDOUT_FILENO);
		return (1);
	}
	if (pipe(fd) == FAIL)
		perror_with_exit("pipe");
	pid = fork();
	if (pid == FAIL)
		perror_with_exit("fork");
	if (pid == CPID)
		child_process(argv, envp, fd);
	else
	{
		if (waitpid(pid, NULL, 0) == FAIL)
			perror_with_exit("waitpid");
		parent_process(argv, envp, fd);
	}
}

void	child_process(char **argv, char **envp, int fd[2])
{
	(void)argv;
	(void)envp;
	(void)fd;
	printf("I am Child!\n");
}

void	parent_process(char **argv, char **envp, int fd[2])
{
	(void)argv;
	(void)envp;
	(void)fd;
	printf("I am Parent!\n");
}
