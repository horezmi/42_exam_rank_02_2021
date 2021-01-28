/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscamand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:08:56 by bscamand          #+#    #+#             */
/*   Updated: 2021/01/28 16:08:58 by bscamand         ###   ########.fr       */
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
			int j = 0;
			while (argv[2][j] != '\0')
			{
				if ((argv[1][i] == argv[2][j]) && !(check(argv[1], argv[1][i], i)))
				{
					write(1, &argv[1][i], 1);
					break;
				}
				j++;
			}
			i++;
		}
		write(1, "\n", 1);
	}
	else
		write(1, "\n", 1);
}
