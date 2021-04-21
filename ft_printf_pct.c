#include "ft_printf.h"

void	print_pct(char **str, t_flags *flags)
{
	flags->len = 1;
	if (flags->left_justify != 0)
	{
		write(1, *str, 1);
		padding(flags);
		flags->printed_chars += flags->len;
	}
	else
	{
		padding(flags);
		write(1, *str, 1);
		flags->printed_chars += flags->len;
	}
	(*str)++;
}
