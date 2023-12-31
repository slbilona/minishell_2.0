SRCDIR = srcs
OBJDIR = points_o/

SRCS = main.c \
		cd.c \
		echo.c \
		exec.c \
		exit.c \
		fork.c \
		free.c \
		init.c \
		pipe.c \
		mange.c \
		export.c \
		utils_1.c \
		utils_2.c \
		expand_1.c \
		expand_2.c \
		ft_space.c \
		ft_quotes.c \
		heredoc_1.c \
		heredoc_2.c \
		parsing_1.c \
		parsing_2.c \
		parsing_3.c \
		signaux_1.c \
		signaux_2.c \
		utils_exec.c \
		builtins_1.c \
		builtins_2.c \
		redirection.c \
		utils_expand.c \
		ft_new_split.c \
		pre_parsing_1.c \
		pre_parsing_2.c \
		utils_builtins.c \
		ft_clean_quotes.c \
		ft_expand_heredoc.c \

OBJFILES = $(SRCS:.c=.o)
OBJS 	= $(addprefix $(OBJDIR), $(OBJFILES))
VPATH   = srcs srcs/pars srcs/utils srcs/exec srcs/builtins

CC = cc
CFLAGS = -g -Wall -Werror -Wextra -I /usr/include
NAME = minishell
LIBFT = libft_printf_gnl/libft.a

all : $(NAME)

${NAME}: $(OBJDIR) ${OBJS}
	make -C libft_printf_gnl
	$(CC) $(CFLAGS) ${OBJS} $(LIBFT) -o $(NAME) -lreadline
	@echo "🧚 tout est prêt 🧚"
		
${OBJDIR}%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean :
	rm -rf $(OBJDIR)
	make clean -C libft_printf_gnl
	clear
	@echo "🧚 tout propre 🧚"

fclean : clean
	make fclean -C libft_printf_gnl
	rm -f $(NAME)
	clear
	@echo "🧚 tout propre 🧚"

leaks: $(NAME)
	valgrind --suppressions=autre/ignore.txt -s --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./minishell

git : fclean
	git add *
	git commit
	git push

re : fclean all


.PHONY : all clean fclean re git

.SILENT : all clean fclean re git $(NAME) $(OBJDIR)
