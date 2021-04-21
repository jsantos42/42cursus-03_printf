#include "ft_printf.h"

void	print_char(char **str, va_list args, t_flags *flags)
{
	char	character;

	character = va_arg(args, int);
	flags->len = 1;
	if (flags->left_justify != 0)
	{
		write(1, &character, 1);
		padding(flags);
		flags->printed_chars += flags->len;
	}
	else
	{
		padding(flags);
		write(1, &character, 1);
		flags->printed_chars += flags->len;
	}
	(*str)++;
}
