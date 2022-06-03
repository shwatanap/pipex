FILES	= pipex.c
SRCS	= $(addprefix $(SRCDIR)/, $(FILES))
OBJS	= $(addprefix $(OBJDIR)/, $(FILES:.c=.o))
SRCDIR	:= srcs
OBJDIR	:= objs
CC		= cc
NAME	= pipex.a
INCDIR	:= includes
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf
AR		= ar rc

all: $(OBJDIR) $(NAME)

ifdef WITH_BONUS
  OBJS += $(BOBJS)
endif

bonus:
	@make WITH_BONUS=true

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(LIBDIR)

re: fclean all

.PHONY: all clean fclean re bonus
