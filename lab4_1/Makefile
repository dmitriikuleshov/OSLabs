# Makefile for dynamic library project

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -I$(LIB_DIR) # Указан путь к заголовочным файлам
LDFLAGS = -shared

# Директории
SRC_DIR = src
LIB_DIR = lib
BUILD_DIR = build

# Библиотеки
LIB1 = $(BUILD_DIR)/lib1.so
LIB2 = $(BUILD_DIR)/lib2.so

# Заголовочные файлы
LAB1_H = $(LIB_DIR)/lib1.h
LAB2_H = $(LIB_DIR)/lib2.h

# Исходники библиотек
SRC1 = $(SRC_DIR)/lib1.c
SRC2 = $(SRC_DIR)/lib2.c

# Исходники тестовых программ
STATIC_TEST = $(SRC_DIR)/main_static.c
DYNAMIC_TEST = $(SRC_DIR)/main_dynamic.c

# Тестовые программы
STATIC_BIN = $(BUILD_DIR)/test_static
DYNAMIC_BIN = $(BUILD_DIR)/test_dynamic

# Общие флаги
DLFLAGS = -ldl -lm

.PHONY: all clean

# Основная цель: сборка всего проекта
all: $(BUILD_DIR) $(LIB1) $(LIB2) $(STATIC_BIN) $(DYNAMIC_BIN)

# Создание директории сборки, если её нет
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Сборка lib1.so
$(LIB1): $(SRC1) $(LAB1_H)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< -lm

# Сборка lib2.so
$(LIB2): $(SRC2) $(LAB2_H)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< -lm

# Сборка test_static (с линковкой с lib1.so)
$(STATIC_BIN): $(STATIC_TEST) $(LIB1)
	$(CC) $(CFLAGS) -o $@ $< -L$(BUILD_DIR) -l1 -Wl,-rpath=$(BUILD_DIR) -lm

# Сборка test_dynamic (динамическая загрузка библиотек)
$(DYNAMIC_BIN): $(DYNAMIC_TEST)
	$(CC) $(CFLAGS) -o $@ $< $(DLFLAGS)

# Очистка
clean:
	rm -rf $(BUILD_DIR)
