/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youjeon <youjeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/02 15:53:46 by youjeon           #+#    #+#             */
/*   Updated: 2022/06/05 02:52:02 by mher             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILES_H
# define UTILES_H

# include <unistd.h>
# include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <sys/errno.h>

int		ft_isalpha(int c);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_atoi(const char *str);
char		*ft_itoa(int n);
char		**ft_split(char const *s, char c);
int		ft_strcmp(const char *s1, const char *s2);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
size_t		ft_strlcpy(char *dest, const char *src, size_t destsize);
char		*ft_strdup(const char *s1);
void		ft_putstr_fd(char *s, int fd);

int		ft_open(char *fname, int oflag, int mode);
void		ft_close(int fd);
void		ft_dup2(int fd1, int fd2);
void		ft_pipe(int *fds);
pid_t		ft_fork(void);
void		*ft_malloc(size_t size, size_t n);
int		ft_write(int fd, const void *buf, size_t byte);
int		ft_access(char *tmp_file_name);

void		exit_with_err(char *str1, char *str2, int exit_code);
void		print_err3(char *cmd, char *str1, char *str2);
void		print_err2(char *cmd, char *str);

#endif
