BUILD_DIR=../../build
GENERALS_OBJ=$(BUILD_DIR)/generals.o
GENERALS_DIR=../../Generals
BINARY_TREE_OBJ=$(BUILD_DIR)/binary_tree.o

client.exe: $(GENERALS_OBJ) $(BINARY_TREE_OBJ) client.c
	gcc -Wall -o client.exe client.c $(BINARY_TREE_OBJ) $(GENERALS_OBJ)

$(BINARY_TREE_OBJ): headers/binary_tree.c headers/binary_tree.h
	gcc -Wall -o $(BINARY_TREE_OBJ) -c headers/binary_tree.c

$(GENERALS_OBJ):
	make -C $(GENERALS_DIR)

run:
	./client.exe

test_memory:
	valgrind ./client.exe

clean:
	rm $(BINARY_TREE_OBJ) client.exe

