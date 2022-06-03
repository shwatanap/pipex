/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 20:10:39 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/03 20:53:06 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	main(int argc, char **argv)
{
	int fd[2];
	pid_t pid;

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
};
