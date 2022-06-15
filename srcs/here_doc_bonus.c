/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 11:42:43 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/09 18:49:24 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex_bonus.h"

static void	here_doc_child_process(int pipe_fd[2], char *limiter);

int	here_doc(char *limiter)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == FAIL)
		perror_with_exit("pipe");
	here_doc_child_process(pipe_fd, limiter);
	// close(pipe_fd[OUT_FD]);
	// close(STDIN_FILENO);
	// dup2(pipe_fd[IN_FD], STDIN_FILENO);
	// close(pipe_fd[IN_FD]);
	// wait(NULL);
	return (pipe_fd[IN_FD]);
}

static void	here_doc_child_process(int pipe_fd[2], char *limiter)
{
	char	*line;

	line = NULL;
	while (!ft_read_line(&line))
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == SUCCESS
			&& line[ft_strlen(limiter)] == '\n')
		{
			close(pipe_fd[OUT_FD]);
			return ;
		}
		ft_putstr_fd(line, pipe_fd[OUT_FD]);
		free(line);
		line = NULL;
	}
	exit(EXIT_FAILURE);
}
