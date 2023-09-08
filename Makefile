SRCDIR = src
OBJDIR = points_o

SRCS = main.c \
		parsing.c \
		utils.c \
		pre_parsing.c \
		ft_new_split.c \
		

SRCSI = src/main_ilona.c \
		utils/utils.c \
		src/builtins.c \
		src/exec.c \
		utils/utils_string.c \
		utils/free.c \

OBJSI = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCSI))
OBJS = $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))

DEPDIR = dep
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

CC = cc
CFLAGS = -g -Wall -Werror -Wextra -I /usr/include
NAME = minishell
LIBFT = libft_printf_gnl/libft.a

all : $(NAME)

$(NAME): $(OBJS) | $(OBJDIR)
	make -C libft_printf_gnl
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline
	@echo "🧚 tout est prêt 🧚"

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR) $(DEPDIR)
	$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(DEPDIR):
	mkdir -p $(DEPDIR)

ilona : $(OBJSI) | $(OBJDIR)
	make -C libft_printf_gnl
	$(CC) $(CFLAGS) $(OBJSI) $(LIBFT) -o $(NAME) -lreadline
	@echo "🧚 tout est prêt 🧚"

clean :
	rm -rf $(OBJDIR) $(DEPDIR)
	make clean -C libft_printf_gnl
	clear
	@echo "🧚 tout propre 🧚"

fclean : clean
	make fclean -C libft_printf_gnl
	rm -f $(NAME)
	clear
	@echo "🧚 tout propre 🧚"

leaks: $(NAME)
	valgrind --suppressions=ignore.txt -s --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./minishell

git : fclean
	git add *
	git commit
	git push

re : fclean all

-include $(wildcard $(DEPDIR)/*.d)

.PHONY : all clean fclean re git

.SILENT : all clean fclean re git $(NAME) $(OBJDIR)
