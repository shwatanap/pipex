/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shwatana <shwatana@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 18:31:18 by shwatana          #+#    #+#             */
/*   Updated: 2022/06/04 04:08:09 by shwatana         ###   ########.fr       */
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

# define FAIL -1
# define CPID 0
# define PIPE_IN_FD 0
# define PIPE_OUT_FD 1
# define SUCCESS 0
# define ARG_ERR_MSG "Bad Argument Error"

# define ESC_RESET "\033[0m"
# define ESC_CLR_RED "\033[38;5;01m"

// utils.c
void	execute(char *argv, char **envp);
void	perror_with_exit(const char *str);

#endif
