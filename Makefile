
DEFS=-DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16




CC=gcc
#CFLAGS=-I/usr/local/include/ImageMagick-6 -Wall -c $(DEFS)
CFLAGS=-I/usr/local/include/ImageMagick-6 -Wall -c $(DEFS)




LIBS=-lMagickWand-6.Q32HDRI -lMagickCore-6.Q32HDRI
#LIBS=-lMagickWand-6.Q16 -lMagickCore-6.Q16

#LDIR=../lib
LIBDIR=/usr/local/lib/libMagickWand-6.Q16.so.2
#ldconfig /usr/local/lib




OBJDIR=obj

SRCS:=$(shell ls | grep "\.c")
OBJS:=$(SRCS:%.c=obj/%.o)
PROGS:=$(SRCS:%.c=%)



$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

%: $(OBJDIR)/%.o
	gcc -L$(LIBDIR) -Wl,-rpath=/usr/local/lib -o $@ $^ $(LIBS)

#$(phony clean):
#	rm -f $(PROGRAMS) *.o

all: $(PROGS)
