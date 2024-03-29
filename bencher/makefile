OBJECT_FILES = cpp.o bencher.o
TESTER_FILES = cpp.o test.o

CC = g++ -std=c++17 -v
CFLAGS = -Wall -Wextra -Wunreachable-code -g
BENCHER = build/bencher
TESTER = build/tester

INC_PATH = -I ../lib/include/ -I /usr/local/include
LIB_PATH = -L ../lib/target/release/ -L /usr/local/lib
LIB_NAME = -lriir -lbenchmark -ldl -lgtest -lpthread

$(BENCHER): $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(INC_PATH) $(OBJECT_FILES) $(LIB_PATH) $(LIB_NAME) -o $(BENCHER)

$(TESTER): $(TESTER_FILES)
	$(CC) $(CFLAGS) $(INC_PATH) $(TESTER_FILES) $(LIB_PATH) $(LIB_NAME) -o $(TESTER)

bencher.o: bencher.cpp
	cd ../lib && cargo build --release && cd ../bencher && $(CC) $(CFLAGS) $(INC_PATH) -c bencher.cpp $(LIB_PATH) $(LIB_NAME)
test.o: test.cpp
	cd ../lib && cargo build --release && cd ../bencher && $(CC) $(CFLAGS) $(INC_PATH) -c test.cpp $(LIB_PATH) $(LIB_NAME)
cpp.o: cpp.cpp
	$(CC) $(CFLAGS) -c cpp.cpp
clean:
	cd ../lib && cargo clean && cd ../bencher && rm -f $(BENCHER) $(OBJECT_FILES) $(TESTER) $(TESTER_FILES) *~
build:
	make
bench:
	make clean && cd ../lib && cargo bench && cd ../bencher && make && $(BENCHER)
test:
	make clean && cd ../lib && cargo test && cd ../bencher && make $(TESTER) && $(TESTER)
