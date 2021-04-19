#include "printf.h"

void    print_char(char **str, va_list args, t_flags *flags)
{
    char character;

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

/*
 * incorrect explanation!!! change it
 *
 * //}
// if precision >len && precision < min_width, adds (precision - len) number of zeros, and the rest is padding ' '
// if precision > min width, padding = '0' * precision e leftlustify 0 e min width = precision
//
// acrescentar a .h

** if precision is specified and smaller than what we want to print,
** we have two different behaviours depending on what we are printing:
**   if it's a string, then it might cut it (therefore we change flags->len);
**   if it's a int or hex, it doesn't cut it, it only decreases the
** padding (therefore, we change flags->min_width);
*/

void    print_int(char **str, va_list args, t_flags *flags)
{
    int     decimal;
    char    *string;

    decimal = va_arg(args, int);
    string = ft_itoa(decimal);
    flags->len = ft_strlen(string);
    if (flags->precision >= 0)
        string = check_precision(string, flags);
    if (flags->left_justify != 0)
    {
        ft_putstr_fd(string, 1);
        padding(flags);
        flags->printed_chars += flags->len;
    }
    else
    {
        padding(flags);
        ft_putstr_fd(string, 1);
        flags->printed_chars += flags->len;
    }
    (*str)++;
}

void    print_address(char **str, va_list args, t_flags *flags)
{
    unsigned long int   address;
    char                *hexadecimal;
    char                *temp;

    address = va_arg(args, unsigned long int);
    hexadecimal = hex_converter(address);

    flags->len = ft_strlen(hexadecimal);
    if (flags->precision >= 0)
        hexadecimal = check_precision(hexadecimal, flags);
    if (flags->precision >= flags->min_width)
    {
        ft_putstr_fd("0x", 1);
        flags->printed_chars += 2;
    }
    else
    {
        temp = hexadecimal;
        hexadecimal = ft_strjoin("0x", temp);
        free(temp);
        flags->len += 2;
    }
    if (flags->left_justify != 0)
    {
        ft_putstr_fd(hexadecimal, 1);
        padding(flags);
        flags->printed_chars += flags->len;
    }
    else
    {
        padding(flags);
        ft_putstr_fd(hexadecimal, 1);
        flags->printed_chars += flags->len;
    }
    (*str)++;
    free(hexadecimal);
}

void    print_string(char **str, va_list args, t_flags *flags)
{
    char    *string;
    int     heap;

    string = va_arg(args, char *);
    heap = 0;
    flags->len = ft_strlen(string);
    if (flags->precision >= 0 && flags->precision < flags->len)
    {
        flags->len = flags->precision;
        string = ft_substr(string, 0, flags->precision);
        heap = 1;
    }
    if (flags->left_justify != 0)
    {
        ft_putstr_fd(string, 1);
        padding(flags);
        flags->printed_chars += flags->len;
    }
    else
    {
        padding(flags);
        ft_putstr_fd(string, 1);
        flags->printed_chars += flags->len;
    }
    (*str)++;
    if (heap)
        free(string);
}

void    print_hex(char **str, va_list args, t_flags *flags)
{
    int     decimal;
    char    *hexadecimal;

    decimal = va_arg(args, int);
    hexadecimal = hex_converter(decimal);
    flags->len = ft_strlen(hexadecimal);
    if (flags->precision >= 0)
        hexadecimal = check_precision(hexadecimal, flags);
    if (flags->left_justify != 0)
    {
        ft_putstr_fd(hexadecimal, 1);
        padding(flags);
        flags->printed_chars += flags->len;
    }
    else
    {
        padding(flags);
        ft_putstr_fd(hexadecimal, 1);
        flags->printed_chars += flags->len;
    }
    (*str)++;
    free(hexadecimal);
}

void    print_unsigned_int(char **str, va_list args, t_flags *flags)
{
    unsigned int    number;
    char            *string;

    number = va_arg(args, unsigned int);
    string = unsigned_itoa(number);
    flags->len = ft_strlen(string);
    if (flags->precision >= 0)
        string = check_precision(string, flags);
    if (flags->left_justify != 0)
    {
        ft_putstr_fd(string, 1);
        padding(flags);
        flags->printed_chars += flags->len;
    }
    else
    {
        padding(flags);
        ft_putstr_fd(string, 1);
        flags->printed_chars += flags->len;
    }
    (*str)++;
    free(string);
}
