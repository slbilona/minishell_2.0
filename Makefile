SRCDIR = srcs
OBJDIR = points_o/
DEPDIR = dep
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$*.d

SRCS = main.c \
		utils.c \
		parsing.c \
		pre_parsing.c \
		ft_space.c \
		exec.c \

OBJFILES = $(SRCS:.c=.o)
OBJS 	= $(addprefix $(OBJDIR), $(OBJFILES))
VPATH   = srcs pars utils exec

CC = cc
CFLAGS = -g -Wall -Werror -Wextra -I /usr/include
NAME = minishell
LIBFT = libft_printf_gnl/libft.a

all : $(NAME)

${NAME}: $(OBJDIR) ${OBJS}
	@make -C libft_printf_gnl
	@$(CC) $(CFLAGS) ${OBJS} $(LIBFT) -o $(NAME) -lreadline
	@echo "🧚 tout est prêt 🧚"
		
${OBJDIR}%.o: %.c $(DEPDIR) 
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(DEPDIR):
	mkdir -p $(DEPDIR)

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
