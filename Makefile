# Rainbow Heart ~ Iris Star
# Flowering Love Maiden
# Makefile

CC = gcc
LD = gcc
CFLAGS = -c -Wall -Wextra
LDFLAGS =
SOURCES = Main.c \
	Document.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = Raheirst

all: $(SOURCES) $(EXECUTABLE)

clean:
	@rm -f \
		$(OBJECTS) \
		$(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	@$(LD) \
		$(LDFLAGS) \
		$(OBJECTS) \
		-o $@

.c.o:
	@$(CC) \
		$(CFLAGS) \
		$< \
		-o $@
