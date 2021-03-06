/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:31:18 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/07 22:42:01 by shwatana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

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
# define EXIT_CMD_NOT_FOUND 127

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

// utils.c
void	execute(char *argv, char **envp);
void	perror_with_exit(const char *str);

char	*replace_space_doble_quart(char *cmd);
void	revert_replace_space(char **cmd);

char	**cmd_parse(char *cmd);

#endif
