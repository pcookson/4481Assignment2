CC = gcc

CFLAGS = -c -Wall

OBJECTS = libpnm.o
OUTPUT = libpnm.a


LIBS =  

SOURCES = $(OBJECTS:.o=.c)

pnmlib: $(OBJECTS)
	/usr/bin/ar rc $(OUTPUT) $(OBJECTS)
	/usr/bin/ranlib $(OUTPUT)
	/bin/rm $(OBJECTS)


.c.o:   $(SOURCES)
	$(CC) $(CFLAGS) $?

