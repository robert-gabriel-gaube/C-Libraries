BUILD_DIR=../build
GENERALS_OBJ=$(BUILD_DIR)/generals.o

$(GENERALS_OBJ): generals.c generals.h
	gcc -Wall -o $(GENERALS_OBJ) -c generals.c

clean:
	rm $(GENERALS_OBJ)