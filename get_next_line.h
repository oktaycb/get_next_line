/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocubukcu <ocubukcu@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 12:07:52 by ocubukcu          #+#    #+#             */
/*   Updated: 2025/07/05 19:09:34 by ocubukcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}					t_list;

char				*get_next_line(int fd);
int					search_newline(t_list *stash);
t_list				*list_get_last(t_list *stash);
void				read_and_stash(int fd, t_list **stash);
void				add_to_stash(t_list **stash, char *buf, int readed);
void				extract_line(t_list *stash, char **line);
void				generate_malloc(char **line, t_list *stash);
void				clean_stash(t_list **stash);
int					str_len(const char *str);
void				free_stash(t_list *stash);
t_list				*clean_last_node(t_list *last);

#endif