/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscamand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:04:07 by bscamand          #+#    #+#             */
/*   Updated: 2021/01/28 16:04:09 by bscamand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

int			get_next_line(char **line);
size_t		ft_strlen(const char *s);
char		*ft_strnew(int size);
char		*ft_strjoin(char *s1, char *s2);

#endif
