FILES	 = pipex.c utils.c
SRCS	 = $(addprefix $(SRCDIR)/, $(FILES))
OBJS	 = $(addprefix $(OBJDIR)/, $(FILES:.c=.o))
SRCDIR	 = srcs
OBJDIR	 = objs
CC		 = cc
NAME	 = pipex
INCDIR	 = includes
LIBFTDIR = ./libft
LIBFT	 = $(LIBFTDIR)/lib/libft.a
CFLAGS	 = -Wall -Wextra -Werror
RM		 = rm -rf
AR		 = ar rc
TESTER	 = pipex_tester_42

all: $(OBJDIR) $(NAME)

ifdef WITH_BONUS
  OBJS += $(BOBJS)
endif

bonus:
	@make WITH_BONUS=true

# サニタイザーを消してください！！！！！！！
$(NAME): $(OBJS)
	make -C $(LIBFTDIR)
	$(CC) -o $(NAME) $(OBJS) $(LIBFT) -g -fsanitize=address

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -I $(INCDIR) -c $< -o $@

$(OBJDIR):
	mkdir -p $@

clean:
	make -C $(LIBFTDIR) clean
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(LIBFT)
	$(RM) $(NAME)

re: fclean all

norm:
	make -C $(LIBFTDIR) norm
	norminette $(SRCS) $(INCDIR)

debug: $(NAME)
	./$(NAME) README.md "cat -e" "tail -n 5" output.txt

$(TESTER):
	git clone git@github.com:Yoo0lh/pipex_tester_42.git

test: $(TESTER)
	./pipex_tester.sh m

.PHONY: all clean fclean re bonus
