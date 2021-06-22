SRCDIR = src
OBJDIR = obj
BINDIR = bin
SRC += $(wildcard $(SRCDIR)/*.c)
OBJ += $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
DEP += $(OBJ:.o=.d)

CC = gcc
CFLAGS = -g --std=gnu99 -MMD -Wall -Wunused -I./src
CFLAGS += -O0
LDFLAGS =
dir_guard=@mkdir -p $(@D)

CFLAGS += -fsanitize=address -fsanitize=undefined
LDFLAGS += -lasan

.PHONY: all
all: $(BINDIR)/plumcc

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(dir_guard)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(OBJDIR) $(BINDIR)

$(BINDIR)/plumcc: $(OBJ)
	$(dir_guard)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

-include $(DEP)