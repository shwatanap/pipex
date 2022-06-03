FILES	= pipex.c utils.c
SRCS	= $(addprefix $(SRCDIR)/, $(FILES))
OBJS	= $(addprefix $(OBJDIR)/, $(FILES:.c=.o))
SRCDIR	:= srcs
OBJDIR	:= objs
CC		= cc
NAME	= pipex
INCDIR	= includes
LIBFT	= ./libft/lib/libft.a
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf
AR		= ar rc
TESTER	= pipex_tester_42

all: $(OBJDIR) $(NAME)

ifdef WITH_BONUS
  OBJS += $(BOBJS)
endif

bonus:
	@make WITH_BONUS=true

$(NAME): $(OBJS)
	make -C ./libft
	$(CC) -o $(NAME) $(OBJS) $(LIBFT)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(LIBDIR)

re: fclean all

norm:
	norminette $(SRCS) $(INCDIR)

debug: $(NAME)
	./$(NAME) README.md "cat -e" "tail -n 5" output.txt

$(TESTER):
	git clone git@github.com:Yoo0lh/pipex_tester_42.git

test: $(TESTER)

.PHONY: all clean fclean re bonus
