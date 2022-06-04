/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:31:18 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/04 22:52:43 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/includes/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define CPID 0
# define FAIL -1
# define SUCCESS 0
# define ARG_ERR_MSG "Bad Argument Error"
# define HERE_DOG_STR "here_doc"
# define HERE_DOG_STR_LEN 8

# define ESC_RESET "\033[0m"
# define ESC_CLR_RED "\033[38;5;01m"

typedef enum e_pipe_fd
{
	PIPE_IN_FD,
	PIPE_OUT_FD,
}		t_pipe_fd;

typedef enum e_open_mode
{
	FILE_APPEND_WRITE,
	FILE_OVER_WRITE,
	FILE_READ,
}		t_open_mode;

// utils_bonus.c
int		open_file(char *file_path, t_open_mode i);
bool	ft_read_line(char **line);

// utils_bonus2.c
void	execute(char *argv, char **envp);
void	perror_with_exit(const char *str);

#endif
