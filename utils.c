#include "ft_printf.h"

int	get_number(char **str, va_list args)
{
	int	number;

	number = 0;
	if (**str == '*')
	{
		number = va_arg(args, int);
		(*str)++;
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

/*
** incorrect explanation!!! change it
**
** if precision >len && precision < min_width, adds (precision - len)
** number of zeros, and the rest is padding ' '
** if precision > min width, padding = '0' * precision e leftlustify 0
** e min width = precision
**
** if precision is specified and smaller than what we want to print,
** we have two different behaviours depending on what we are printing:
**   if it's a string, then it might cut it (therefore we change flags->len);
**   if it's a int or hex, it doesn't cut it, it only decreases the
** padding (therefore, we change flags->min_width);
*/

char	*check_precision(char *string, t_flags *flags)
{
	int		zeros;
	char	*string2;
	char	*string3;

	if (flags->precision <= flags->len)
	{
		flags->padding = ' ';
		if (ft_strncmp(string, "", 2) == '0')  ///acrescentei aqui para o caso de querer imprimir 0 com precisao 0 nao ser suposto dar nada
        {
            free(string);
            flags->len = 0;
            return (ft_strdup(""));
        }
		else
            return (string);
	}
	else if (flags->precision < flags->min_width)
	{
		flags->padding = ' ';
		zeros = flags->precision - flags->len;
		if (flags->negative < 0)  ////acrescentei aqui +1 se negativo porque acrescentamos 1 ao len na printf_d
		    zeros++;
		flags->len += zeros;
		string2 = malloc((zeros + 1) * (sizeof(char)));
		string2[zeros] = '\0';
		while (zeros-- > 0)
			string2[zeros] = '0';
		string3 = ft_strjoin(string2, string);
		free(string);
		free(string2);
		return (string3);
	}
	else
	{
		flags->left_justify = 0;
		flags->padding = '0';
		flags->min_width = flags->precision;
		if (flags->negative < 0)  //acrescentei este if para retirar o caracter do menos
            flags->len--;
        sign_printer(flags);
		return (string);
	}
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

void    sign_printer(t_flags *flags)
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
