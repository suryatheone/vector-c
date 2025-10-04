CC = gcc
CFLAGS = -Iinclude -Wall -D_USE_MATH_DEFINES
LDFLAGS = -lm

BUILDDIR = build
TARGET = $(BUILDDIR)/main

SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(SRCDIR)/%.o, $(SOURCES))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILDDIR)
	$(CC) $(LDFLAGS) -o $@ $^

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR) $(SRCDIR)/*.o main

.PHONY: all clean