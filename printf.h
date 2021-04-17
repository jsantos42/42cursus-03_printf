#ifndef FT_FTPRINTF_H
# define FT_FTPRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"
/* incluir so as funcoes necessarias do libft?
garantir que o libft passa na nova norma
retirar o segundo unistd deste ficheiro
*/

typedef struct s_flags {
    int      left_justify;
    char     padding;
    int      min_width;
    int      precision;
    int     len;
} t_flags;

void reading(char **str, int *count);
int get_number(char **str);
int choose_conv(char **str, va_list args, t_flags *flags);
int check_flags(char **str, t_flags *flags);
void    print_char(char **str, va_list args, int *printed_chars, t_flags *flags);
void    print_string(char **str, va_list args, int *printed_chars, t_flags *flags);
//void    print_address(char **str, va_list args, int *printed_chars, t_flags *flags);
void    print_int(char **str, va_list args, int *printed_chars, t_flags *flags);
void    print_hex(char **str, va_list args, int *printed_chars, t_flags *flags);
//int     count_digits(int number); DESNESSARIO CREIO
char    *hex_converter(size_t decimal);
void padding(int *printed_chars, t_flags *flags);
char    *check_precision(char *string, t_flags *flags);
int ft_printf(const char *input, ...);

#endif
