/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocubukcu <ocubukcu@student.42kocaeli.com.t +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 21:46:49 by ocubukcu          #+#    #+#             */
/*   Updated: 2025/07/05 19:24:26 by ocubukcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*line;

	if (!fd || fd < 0 || BUFFER_SIZE <= 0)
		return (free(stash), NULL);
	line = NULL;
	read_and_stash(fd, &stash);
	if (stash == NULL)
	{
		clean_stash(&stash);
		return (NULL);
	}
	extract_line(stash, &line);
	clean_stash(&stash);
	if (line[0] == '\0')
	{
		free_stash(stash);
		stash = NULL;
		free(line);
		return (NULL);
	}
	return (line);
}

void	read_and_stash(int fd, t_list **stash)
{
	char	*buffer;
	int		a_read;

	a_read = 1;
	while (!search_newline(*stash) && a_read >= 0)
	{
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buffer == NULL)
			return ;
		a_read = read(fd, buffer, BUFFER_SIZE);
		if (a_read == 0)
			return (free(buffer));
		if ((*stash == NULL && a_read == 0) || a_read == -1)
		{
			free(buffer);
			return ;
		}
		buffer[a_read] = '\0';
		add_to_stash(stash, buffer, a_read);
		free(buffer);
	}
}

void	add_to_stash(t_list **stash, char *buf, int a_read)
{
	int		i;
	t_list	*last;
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return ;
	new_node->next = NULL;
	new_node->content = malloc(sizeof(char) * (a_read + 1));
	if (new_node->content == NULL)
		return (free(new_node));
	i = 0;
	while (buf[i] && i < a_read)
	{
		new_node->content[i] = buf[i];
		i++;
	}
	new_node->content[i] = '\0';
	if (*stash == NULL)
	{
		*stash = new_node;
		return ;
	}
	last = list_get_last(*stash);
	last->next = new_node;
}

void	extract_line(t_list *stash, char **line)
{
	int	i;
	int	j;

	if (stash == NULL)
		return ;
	generate_malloc(line, stash);
	if (*line == NULL)
		return ;
	j = 0;
	while (stash)
	{
		i = 0;
		while (stash->content[i])
		{
			if (stash->content[i] == '\n')
			{
				(*line)[j++] = stash->content[i];
				break ;
			}
			(*line)[j++] = stash->content[i++];
		}
		stash = stash->next;
	}
	(*line)[j] = '\0';
}

void	clean_stash(t_list **stash)
{
	t_list	*last;
	t_list	*cln_node;
	int		i;
	int		j;

	if (!stash || !(*stash))
		return ;
	last = list_get_last(*stash);
	i = 0;
	while (last->content[i] && last->content[i] != '\n')
		i++;
	if (last->content[i] == '\n')
		i++;
	cln_node = malloc(sizeof(t_list));
	cln_node->content = malloc(sizeof(char) * ((str_len(last->content) - i)
				+ 1));
	if (cln_node->content == NULL)
		return (free(cln_node));
	j = 0;
	while (last->content[i])
		cln_node->content[j++] = last->content[i++];
	cln_node->content[j] = '\0';
	cln_node->next = NULL;
	free_stash(*stash);
	*stash = cln_node;
}
