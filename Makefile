FILES		= pipex.c utils.c
BFILES		= pipex_bonus.c utils_bonus.c utils_bonus2.c
OBJS		= $(addprefix $(OBJDIR)/, $(FILES:.c=.o))
BOBJS		= $(addprefix $(OBJDIR)/, $(BFILES:.c=.o))
SRCDIR		= srcs
OBJDIR		= objs
CC			= cc
NAME		= pipex
INCDIR		= includes
LIBFTDIR	= ./libft
LIBFT		= $(LIBFTDIR)/lib/libft.a
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -rf
AR			= ar rc
TESTER		= pipex_tester_42

all: $(OBJDIR) $(NAME)

ifdef WITH_BONUS
  OBJS = $(BOBJS)
endif

bonus:
	@make WITH_BONUS=true

# サニタイザーを消してください！！！！！！！
$(NAME): $(OBJS)
	make -C $(LIBFTDIR)
	$(CC) -o $(NAME) $^ $(LIBFT) #-g -fsanitize=address

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

rebonus: fclean bonus

norm:
	make -C $(LIBFTDIR) norm
	norminette $(SRCDIR) $(INCDIR)

debug: $(NAME)
	./$(NAME) README.md "cat -e" "tail -n 5" output.txt

$(TESTER):
	git clone git@github.com:Yoo0lh/pipex_tester_42.git
	git clone git@github.com:ael-bekk/PIPEX_TESTER.git

test: $(TESTER)
	./pipex_tester.sh m

.PHONY: all clean fclean re bonus
