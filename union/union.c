/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   union.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscamand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:08:38 by bscamand          #+#    #+#             */
/*   Updated: 2021/01/28 16:08:39 by bscamand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int check(char *argv, char c, int i)
{
	i--;
	while (i >= 0)
	{
		if (c == argv[i])
			return (1);
		i--;
	}
	return (0);
}

int main(int argc, char **argv)
{
	if (argc == 3)
	{
		int i = 0;
		while (argv[1][i] != '\0')		
		{
			if (!(check(argv[1], argv[1][i], i)))
				write(1, &argv[1][i], 1);
			i++;
		}
		int j = 0;
		while (argv[2][j] != '\0')		
		{
			if (!(check(argv[1], argv[2][j], i)) && !(check(argv[2], argv[2][j], j)))
				write(1, &argv[2][j], 1);
			j++;
		}
		write(1, "\n", 1);
	}
	else 
		write(1, "\n", 1);
}
