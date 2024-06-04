CC = gcc
CFLAGS = -Wall -Wextra

all: test_storage_mgr

test_storage_mgr: test_storage_mgr.o storage_mgr.o dberror.o
	$(CC) $(CFLAGS) -o test_storage_mgr test_storage_mgr.o storage_mgr.o dberror.o

test_storage_mgr.o: test_storage_mgr.c storage_mgr.h test_helper.h
	$(CC) $(CFLAGS) -c test_storage_mgr.c

storage_mgr.o: storage_mgr.c storage_mgr.h dberror.h
	$(CC) $(CFLAGS) -c storage_mgr.c

dberror.o: dberror.c dberror.h
	$(CC) $(CFLAGS) -c dberror.c

clean:
	rm -f *.o test_storage_mgr
