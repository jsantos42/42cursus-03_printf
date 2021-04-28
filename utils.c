#include "ft_printf.h"

int	get_min_width(char **str, va_list args, t_flags *flags)
{
	int	number;

	number = 0;
	if (**str == '*')
	{
		number = va_arg(args, int);
		(*str)++;
		if (number < 0)
		{
			flags->left_justify = 1;
			number *= -1;
		}
		return (number);
	}
	while (**str >= '0' && **str <= '9')
	{
		number = number * 10 + **str - '0';
		if (number > 2147483647)
			return (-1);
		else
			(*str)++;
	}
	return (number);
}

void	padding(t_flags *flags)
{
	while (flags->min_width > flags->len)
	{
		write(1, &flags->padding, 1);
		(flags->printed_chars)++;
		flags->min_width--;
	}
}

void	sign_printer(t_flags *flags)
{
	if (flags->negative < 0)
	{
		write(1, "-", 1);
		flags->negative = 0;
	}
}

void	str_printer(char *str, t_flags *flags)
{
	if (flags->left_justify != 0)
	{
		sign_printer(flags);
		ft_putstr_fd(str, 1);
		padding(flags);
		flags->printed_chars += flags->len;
	}
	else
	{
		if (flags->padding == ' ')
		{
			padding(flags);
			sign_printer(flags);
		}
		else
		{
			sign_printer(flags);
			padding(flags);
		}
		ft_putstr_fd(str, 1);
		flags->printed_chars += flags->len;
	}
}
