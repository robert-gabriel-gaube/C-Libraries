BUILD_DIR=../../Build
GENERALS_OBJ=$(BUILD_DIR)/generals.o
GENERALS_DIR=../../Generals
GENERAL_TREE_OBJ=$(BUILD_DIR)/general_tree.o

client.exe: $(GENERALS_OBJ) $(GENERAL_TREE_OBJ) client.c
	gcc -Wall -o client.exe client.c $(GENERAL_TREE_OBJ) $(GENERALS_OBJ)

$(GENERAL_TREE_OBJ): Headers/general_tree.c Headers/general_tree.h
	gcc -Wall -o $(GENERAL_TREE_OBJ) -c Headers/general_tree.c

$(GENERALS_OBJ):
	make -C $(GENERALS_DIR)

run:
	./client.exe

test_memory:
	valgrind ./client.exe

clean:
	rm $(GENERAL_TREE_OBJ) client.exe

