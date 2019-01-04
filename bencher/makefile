OBJECT_FILES = cpp.o bencher.o

CC = g++
CFLAGS = -Wall -Wextra -Wunreachable-code -g -O3
TARGET = bencher

INC_PATH = -I ../lib/include/
LIB_PATH = -L ../lib/target/release/
LIB_NAME = -lriir -lbenchmark -lpthread -ldl

$(TARGET): $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(INC_PATH) $(OBJECT_FILES) $(LIB_PATH) $(LIB_NAME) -o $(TARGET)
bencher.o: bencher.cpp
	cd ../lib && cargo build --release && cd ../bencher && $(CC) $(CFLAGS) $(INC_PATH) -c bencher.cpp  $(LIB_PATH) $(LIB_NAME)
cpp.o: cpp.cpp
	$(CC) $(CFLAGS) -c cpp.cpp
clean:
	cd ../lib && cargo clean && cd ../bencher && rm -f $(TARGET) $(OBJECT_FILES) *~
build:
	make
run:
	make && ./bencher