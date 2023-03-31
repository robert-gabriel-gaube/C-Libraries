BUILD_DIR=../../build
GENERALS_OBJ=$(BUILD_DIR)/generals.o
GENERALS_DIR=../../Generals
OBJ=$(BUILD_DIR)/huffman_compression.o
HEADER_FILE=headers/huffman_compresion.h
C_FILE=headers/huffman_compresion.c

client.exe: $(GENERALS_OBJ) $(OBJ) client.c
	gcc -Wall -o client.exe client.c $(OBJ) $(GENERALS_OBJ)

$(OBJ): $(C_FILE) $(HEADER_FILE)
	gcc -Wall -o $(OBJ) -c $(C_FILE)

$(GENERALS_OBJ):
	make -C $(GENERALS_DIR)

run:
	./client.exe

test_memory:
	valgrind ./client.exe

clean:
	rm $(OBJ) client.exe

