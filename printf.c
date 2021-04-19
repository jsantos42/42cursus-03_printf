#include "printf.h"

void reading(char **str, int *count)
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
        reading(str,count);
    }
}

int check_flags(char **str, t_flags *flags)
{
    flags->left_justify = 0;
    flags->padding = ' ';
    flags->min_width = 0;
    flags->precision = -1;
    while(**str != '\0' && (**str == '-' || **str == '0'))
    {
        if (**str == '-')
            flags->left_justify = 1;
        else if (**str == '0')
            flags->padding = '0';
        (*str)++;
    }
    flags->min_width = get_number(str);
    if (flags->left_justify == 1 && flags->padding == '0')
        flags->padding = ' ';
    if (**str == '.')
    {
        (*str)++;
        flags->precision = get_number(str);
    }
    return (0);
}


void    choose_conv(char **str, va_list args, t_flags *flags)
{
    flags->type = **str;
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


int ft_printf(const char *input, ...)
{
    int     count;
    char    *str;
    t_flags flags;
    va_list args;

    count = 0;
    str = (char *)input;
    va_start(args, input);
    while (*str != '\0')
    {
        reading(&str, &count);
        if (*str != '\0' && !(check_flags(&str, &flags)))
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


#include <stdio.h>

int main()
{
    char a = 'k';
    char *b = "exame";
    int i = -66;
    int res1 = ft_printf("ola %-5.s adeus %-014ua\n", b, i);
    int res2 = printf("ola %-5.s adeus %-014ua\n", b, i);
    printf("%d\n", res1);
    printf("%d\n\n", res2);


    int j = 2;
    unsigned long int u = 2;
    char *s = "a";

    unsigned long int ju = (unsigned long int)&j;
    unsigned long int uu = (unsigned long int)&u;
    unsigned long int su = (unsigned long int)s;

    char *s1 = hex_converter(ju);
    char *s2 = hex_converter(uu);
    char *s3 = hex_converter(su);


    printf("integer %d\n", j);
    printf("address of integer %p\n\n", &j);
    printf("unsigned long %lu\n", u);
    printf("address of unsigned long %p\n\n", &u);
    printf("string %s\n", s);
    printf("address of string %p\n", s);


    printf("unsigned long %lu\n", ju);
    printf("unsigned long %lu\n", uu);
    printf("unsigned long %lu\n", su);

    printf("hex %s\n", s1);
    printf("hex %s\n", s2);
    printf("hex %s\n", s3);
    return 0;
}

