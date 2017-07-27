CC = g++
CFLAGS = -Wall
LIBS = -std=c++11 
LIBP = -lprotobuf
DEPEND = server client 
FILECC = test.cc 

ifdef DEBUG 
CFLAGS += -g -O0
DEPEND = clean server client 
endif 

all: $(DEPEND)

server: test
	$(CC) $(CFLAGS) $@.cpp $^.o test.pb.cc $(LIBS) -o $@ $(LIBP)

client: test
	$(CC) $(CFLAGS) $@.cpp $^.o test.pb.cc $(LIBS) -o $@ $(LIBP)

test: test.pb.cc 
	$(CC) -c test.cc $(LIBS)

test.pb.cc:
	protoc --proto_path =. --cpp_out=. test.proto

clean:
	rm -r ../Autogenerated 








