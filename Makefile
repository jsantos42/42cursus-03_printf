CC	=		gcc

CFLAGS =	-Wall -Werror -Wextra

RM =		rm -fr

NAME =		libftprintf.a

SRCS =		ft_printf.c		ft_printf_c.c	ft_printf_di.c	ft_printf_p.c \
			ft_printf_s.c	ft_printf_u.c	ft_printf_xX.c	utils.c

LIBFT =		libft

OBJS =		$(SRCS:.c=.o)

all:		$(NAME)

$(NAME):	$(OBJS)
				$(MAKE) -C $(LIBFT)
				cp $(LIBFT)/libft.a $(NAME)
				ar -crs $(NAME) $(OBJS)

%.c.o:		%.c
				$(CC) $(CFLAGS) -I. -c $< -o $(<:.c=.o)

clean:
				make clean -C $(LIBFT)
				$(RM) $(OBJS)

fclean:		clean
				make fclean -C $(LIBFT)
				$(RM) $(NAME)

re:			fclean	all

.PHONY:		all	clean	fclean	re
