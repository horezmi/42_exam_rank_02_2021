/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bscamand <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 16:10:51 by bscamand          #+#    #+#             */
/*   Updated: 2021/01/28 16:10:53 by bscamand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

#include <stdio.h>

typedef struct				s_parser
{
	va_list					args;
	char					*str;
	int						dot;
	char					type;
	int						accuracy;
	int						width;
	char					*s;
	int						di;
	unsigned int			x;
	char					*di_str;
	char					*x_str;
	int						len;
	int						len_di;
	int						len_x;
	char					tap;
}							t_parser;

# define ARGS ptr->args
# define STR ptr->str
# define DOT ptr->dot
# define TYPE ptr->type
# define ACCURACY ptr->accuracy
# define WIDTH ptr->width
# define S ptr->s
# define D ptr->di
# define X ptr->x
# define D_STR ptr->di_str
# define X_STR ptr->x_str
# define LEN ptr->len
# define LEN_D ptr->len_di
# define LEN_X ptr->len_x
# define TAP ptr->tap

void	ft_init_struct_start(t_parser *ptr)
{
	STR = 0;
	DOT = 0;
	TYPE = 0;
	ACCURACY = 0;
	WIDTH = 0;
	S = 0;
	D = 0;
	X = 0;
	D_STR = 0;
	X_STR = 0;
	LEN = 0;
	LEN_D = 0;
	LEN_X = 0;
	TAP = ' ';
}

void	ft_init_struct_end(t_parser *ptr)
{
	DOT = 0;
	TYPE = 0;
	ACCURACY = 0;
	WIDTH = 0;
	S = 0;
	D = 0;
	X = 0;
	D_STR = 0;
	X_STR = 0;
	LEN_D = 0;
	LEN_X = 0;
	TAP = ' ';
}

void	ft_putchar_fd(int c, int fd, t_parser *ptr)
{
	write(fd, &c, 1);
	LEN++;
}

void	ft_putchar_fd_tap(int c, int fd, t_parser *ptr, int count)
{
	while (count-- > 0)
	{
		write(fd, &c, 1);
		LEN++;
	}
}

void	ft_putstr_fd(char *s, int fd, t_parser *ptr)
{
	if (s)
	{
		while (*s)
			ft_putchar_fd(*s++, fd, ptr);
	}
}

void	ft_putstr_fd_len(char *s, int fd, int len, t_parser *ptr)
{
	if (s)
	{
		while (len--)
			ft_putchar_fd(*s++, fd, ptr);
	}
}

size_t		ft_strlen(const char *s)
{
	size_t n;

	n = 0;
	while (s[n] != '\0')
	{
		n++;
	}
	return (n);
}

void		ft_parse_flag(t_parser *ptr)
{
	while (*STR == '.' || (*STR >= '0' && *STR <= '9'))
	{
		if (*STR >= '0' && *STR <= '9')
		{
			while (*STR >= '0' && *STR <= '9')
			{
				WIDTH = (WIDTH * 10) + *STR - '0';
				STR++;
			}
			STR--;
		}
		else if (*STR == '.')
		{
			DOT = 1;
			STR++;
			while (*STR >= '0' && *STR <= '9')
			{
				ACCURACY = (ACCURACY * 10) + *STR - '0';
				STR++;
			}
			if (ACCURACY < 0)
			{
				ACCURACY = 0;
				DOT = 0;
			}
			STR--;
		}
		STR++;
	}
	return ;
}

void		ft_parse_type(t_parser *ptr)
{
	if (*STR == 'd')
	{
		TYPE = 'd';
		D = va_arg(ARGS, int);
	}
	else if (*STR == 's')
	{
		TYPE = 's';
		S = va_arg(ARGS, char*);
		if (!S)
			S = "(null)";
	}
	else if (*STR == 'x')
	{
		TYPE = 'x';
		X = va_arg(ARGS, unsigned int);
	}
	return ;
}

void	ft_accuracy_len(int len, t_parser *ptr)
{
	if (DOT && TYPE == 's')
	{
		if (ACCURACY > len && ACCURACY)
			ACCURACY = len;
	}
	else
	{
		if (ACCURACY <= len)
			ACCURACY = len;
	}
}

size_t			ft_intlen(long long nbr, int signlen)
{
	int			intlen;

	intlen = 1;
	while (nbr /= 10)
		intlen++;
	return (intlen + signlen);
}

char			*ft_itoa(long long n)
{
	char		*str;
	int			sign;
	int			intlen;
	long long	nbr;

	sign = (n < 0) ? 1 : 0;
	nbr = (n < 0) ? -(long long)n : (long long)n;
	intlen = ft_intlen(nbr, sign);
	str = (char *)malloc(sizeof(char) * (intlen + 1));
	if (!str)
		return (NULL);
	str[intlen--] = '\0';
	while (intlen >= sign)
	{
		str[intlen--] = (nbr % 10) + '0';
		nbr /= 10;
	}
	if (sign == 1)
		str[0] = '-';
	return (str);
}

size_t				ft_hex_len(unsigned int nbr)
{
	int				hex_len;

	hex_len = 1;
	while (nbr /= 16)
		hex_len++;
	return (hex_len);
}

char				*ft_itoa_hex(unsigned int n,
								t_parser *ptr)
{
	char			*str;
	int				hex_len;
	unsigned int	res;

	hex_len = ft_hex_len(n);
	str = (char *)malloc(sizeof(char) * (hex_len + 1));
	if (!str)
		return (NULL);
	str[hex_len--] = '\0';
	while (hex_len >= 0)
	{
		res = n % 16;
		if (res > 9)
			res = res - 9 + 96;
		else
			res += 48;
		str[hex_len--] = res;
		n /= 16;
	}
	return (str);
}

void	ft_char_minus(int flag, t_parser *ptr)
{
	if (D < 0 && flag)
	{
		ft_putchar_fd('-', 1, ptr);
		D_STR++;
	}
	if (D < 0 && DOT && !flag)
	{
		LEN_D--;
		WIDTH--;
	}
}

int		ft_accuracy_and_value_dx(char *str, t_parser *ptr)
{
	if (DOT)
	{
		if (!WIDTH)
			return (0);
		ft_putchar_fd_tap(TAP, 1, ptr, WIDTH - ACCURACY);
		return (1);
	}
	ft_putchar_fd_tap(TAP, 1, ptr, WIDTH - ACCURACY - 1);
	ft_putchar_fd(*str++, 1, ptr);
	return (1);
}

void	ft_process_x(t_parser *ptr)
{
	if (DOT)
	{
		ft_accuracy_len(LEN_X, ptr);
		ft_putchar_fd_tap(' ', 1, ptr, WIDTH - ACCURACY);
		ft_putchar_fd_tap('0', 1, ptr, ACCURACY - LEN_X);
		ft_putstr_fd_len(X_STR, 1, LEN_X, ptr);
	}
	else
	{
		ft_putchar_fd_tap(TAP, 1, ptr, WIDTH - LEN_X);
		ft_putstr_fd(X_STR, 1, ptr);
	}
}

void	ft_process_d(t_parser *ptr)
{
	if (DOT)
	{
		ft_accuracy_len(LEN_D, ptr);
		ft_putchar_fd_tap(' ', 1, ptr, WIDTH - ACCURACY);
		ft_char_minus(1, ptr);
		ft_putchar_fd_tap('0', 1, ptr, ACCURACY - LEN_D);
		ft_putstr_fd_len(D_STR, 1, LEN_D, ptr);
	}
	else
	{
		ft_putchar_fd_tap(TAP, 1, ptr, WIDTH - LEN_D);
		ft_char_minus(1, ptr);
		ft_putstr_fd(D_STR, 1, ptr);
	}
}

void	ft_print(t_parser *ptr)
{
	if (TYPE == 's')
	{
		int len_s;

		len_s = ft_strlen(S);
		ft_accuracy_len(len_s, ptr);
		if (DOT)
		{
			ft_putchar_fd_tap(' ', 1, ptr, WIDTH - ACCURACY);
			ft_putstr_fd_len(S, 1, ACCURACY, ptr);
			return ;
		}
		ft_putchar_fd_tap(' ', 1, ptr, WIDTH - len_s);
		ft_putstr_fd(S, 1, ptr);
	}
	else if (TYPE == 'd')
	{
		char *d_str;

		d_str = ft_itoa(D);
		D_STR = d_str;
		free(d_str);
		LEN_D = ft_strlen(D_STR);
		ft_char_minus(0, ptr);
		if (!ACCURACY && !D)
		{
			if (!(ft_accuracy_and_value_dx(D_STR, ptr)))
				ft_accuracy_and_value_dx(D_STR, ptr);
			else
				return ;
		}
		else
			ft_process_d(ptr);
	}
	else if (TYPE == 'x')
	{
		char	*x_str;

		x_str = ft_itoa_hex(X, ptr);
		X_STR = x_str;
		free(x_str);
		LEN_X = ft_strlen(X_STR);
		if (!ACCURACY && !X)
		{
			if (!(ft_accuracy_and_value_dx(X_STR, ptr)))
				ft_accuracy_and_value_dx(X_STR, ptr);
			else
				return ;
		}
		else
			ft_process_x(ptr);
	}
	return ;
}

void		ft_parse_and_print(t_parser *ptr)
{
	while (*STR)
	{
		if (*STR == '%')
		{
			if (*++STR != '%')
			{
				ft_init_struct_end(ptr);
				ft_parse_flag(ptr);
				ft_parse_type(ptr);
				if (TYPE)
					ft_print(ptr);
				else
					return ;
			}
			else
				ft_putchar_fd(*STR, 1, ptr);
		}
		else
			ft_putchar_fd(*STR, 1, ptr);
		STR++;
	}
	return ;
}

int				ft_printf(const char *str, ...)
{
	t_parser	parser;
	t_parser	*ptr;

	ptr = &parser;
	ft_init_struct_start(ptr);
	STR = (char *)str;
	va_start(ARGS, str);
	ft_parse_and_print(ptr);
	va_end(ARGS);
	return (LEN);
}
