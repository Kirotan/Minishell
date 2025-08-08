NAME := minishell

CC := gcc
CFLAGS := -Wall -Wextra -Werror -g
CPPFLAGS := -Iinclude

SRCDIR := src
OBJDIR := obj

LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a

SRCS := $(shell find $(SRCDIR) -name '*.c')
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -lm -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

