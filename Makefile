CC = gcc
CFLAGS = -Iinclude -Wall -D_USE_MATH_DEFINES
LDFLAGS = -lm

BUILDDIR = build
TARGET = $(BUILDDIR)/main

SRCDIR = src
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(patsubst $(SRCDIR)/%.c, $(SRCDIR)/%.o, $(SOURCES))

PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@mkdir -p $(BUILDDIR)
	$(CC) $(LDFLAGS) -o $@ $^

$(SRCDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR) $(SRCDIR)/*.o main

PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin

install: all
	@echo "Installing to $(BINDIR)..."
	@mkdir -p $(BINDIR)
	@install -m 755 $(TARGET) $(BINDIR)/vector
	@echo "Installed."

uninstall:
	@echo "Removing from $(BINDIR)..."
	@rm -f $(BINDIR)/vector
	@echo "Removed."

.PHONY: all clean install uninstall
