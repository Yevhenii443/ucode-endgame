# A simple Makefile for compiling small SDL projects

# set the compiler
CC := clang
INC = inc


# set the compiler flags
FFLAGS = -F ./resource/frameworks -framework SDL2 -rpath ./resource/frameworks \
	 -F ./resource/frameworks -framework SDL2_image -rpath ./resource/frameworks \
	 -F ./resource/frameworks -framework SDL2_ttf -rpath ./resource/frameworks \
	 -F ./resource/frameworks -framework SDL2_mixer -rpath ./resource/frameworks \

CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -Werror
# add header files here
HDRS := inc/header.h \

# add source files here
SRCS := src/*.c\


# generate names of object files
# OBJS := $(SRCS:.c=.o)

# name of executable
EXEC := endgame

# default recipe
all: $(EXEC)

# recipe for building the final executable
$(EXEC): $(SRCS) $(INC) Makefile
	@$(CC) $(SRCS) $(CFLAGS) $(FFLAGS) -o $(EXEC) -I $(INC)
	@printf "\r\33[2K $(NAME)\033[33;1m\tcompile\n"

# recipe for building object files
#$(OBJS): $(@:.o=.c) $(HDRS) Makefile
#	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)

# recipe to clean the workspace
clean:		
	rm -f $(OBJS)
	@printf "Object files - \t\033[31;1mdeleted\033[0m\n"


uninstall: clean
	rm -f $(EXEC)
	@printf "$(NAME)\t\033[31;1muninstalled\n"

reinstall: uninstall all

run: all
	./$(EXEC)

.PHONY: all clean
