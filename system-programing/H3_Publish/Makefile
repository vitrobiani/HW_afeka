CC=gcc
OBJDIR=objdir
OBJ=$(addprefix $(OBJDIR)/, $(patsubst %.c, %.o, $(wildcard *.c)))
TARGET=prog
CFLAGS=-g -Wall -Werror -Wpedantic -Wextra
LDFLAGS= -lm
.PHONY: all clean

all: $(OBJDIR) $(TARGET)

$(OBJDIR):
	mkdir $(OBJDIR)

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^ 

clean:
	@rm -f $(TARGET) $(wildcard *.o)
	@rm -rf $(OBJDIR)

