# Definición de variables
CC = gcc
CFLAGS = -Wall `pkg-config --cflags gtk+-3.0` -Iinclude
LDFLAGS = `pkg-config --libs gtk+-3.0`
SRC = src/main.c src/ui.c src/tasks.c src/calendar.c
OBJ = $(SRC:.c=.o)
TARGET = todo-app

# Regla principal
all: $(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

# Regla para compilar los archivos objeto
%.o: src/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

# Regla para limpiar los archivos generados
clean:
	rm -f $(OBJ) $(TARGET)

