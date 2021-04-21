#include "ft_printf.h"

void	reading(char **str, int *count)
{
	while (**str != '\0' && **str != '%')
	{
		write(1, (*str)++, 1);
		(*count)++;
	}
	if (**str == '%')
		(*str)++;
	if (**str == '%')
	{
		write(1, "%", 1);
		(*count)++;
		(*str)++;
		reading(str, count);
	}
}

int	check_flags(char **str, va_list args, t_flags *flags)
{
	flags->left_justify = 0;
	flags->padding = ' ';
	flags->min_width = 0;
	flags->precision = -1;
	while (**str != '\0' && (**str == '-' || **str == '0'))
	{
		if (**str == '-')
			flags->left_justify = 1;
		else if (**str == '0')
			flags->padding = '0';
		(*str)++;
	}
	flags->min_width = get_number(str, args);
	if (flags->left_justify == 1 && flags->padding == '0')
		flags->padding = ' ';
	if (**str == '.')
	{
		(*str)++;
		flags->precision = get_number(str, args);
	}
	return (0);
}

void	choose_conv(char **str, va_list args, t_flags *flags)
{
	flags->printed_chars = 0;
	if (**str == 'c')
		print_char(str, args, flags);
	else if (**str == 'd' || **str == 'i')
		print_int(str, args, flags);
	else if (**str == 'p')
		print_address(str, args, flags);
	else if (**str == 's')
		print_string(str, args, flags);
	else if (**str == 'u')
		print_unsigned_int(str, args, flags);
	else if (**str == 'x' || **str == 'X')
		print_hex(str, args, flags);
	else
		flags->printed_chars = -1;
}

int	ft_printf(const char *input, ...)
{
	int		count;
	char	*str;
	t_flags	flags;
	va_list	args;

	count = 0;
	str = (char *)input;
	va_start(args, input);
	while (*str != '\0')
	{
		reading(&str, &count);
		if (*str != '\0' && !(check_flags(&str, args, &flags)))
		{
			choose_conv(&str, args, &flags);
			if (flags.printed_chars >= 0)
				count += flags.printed_chars;
			else
				return (-1);
		}
	}
	va_end(args);
	return (count);
}
