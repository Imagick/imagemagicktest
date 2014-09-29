
# DEFS=-DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=32
# LIBS=-lMagickWand-6.Q32 -lMagickCore-6.Q32

#DEFS=-DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=32
#LIBS=-lMagickWand-6.Q32HDRI -lMagickCore-6.Q32HDRI
#LIBDIR=/usr/local/lib/libMagickCore-6.Q32.so.2


#DEFS=-DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=32
#LIBS=-lMagickWand-6.Q32HDRI -lMagickCore-6.Q32HDRI
#LIBDIR=/usr/local/lib/libMagickCore-6.Q32HDRI.so.2

DEFS=-DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16
LIBS=-lMagickWand-6.Q16 -lMagickCore-6.Q16
LIBDIR=/usr/lib64/libMagickCore-6.Q16.so




#DEFS=-DMAGICKCORE_HDRI_ENABLE=1 -DMAGICKCORE_QUANTUM_DEPTH=16
#LIBS=-lMagickWand-6.Q16HDRI -lMagickCore-6.Q16HDRI


# DEFS=-DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16

CC=gcc
#CFLAGS=-I/usr/local/include/ImageMagick-6 -Wall -c $(DEFS)
#CFLAGS=-I/usr/local/include/ImageMagick-6 -g -O2 -Wall -c $(DEFS)
CFLAGS=-I/usr/include/ImageMagick-6 -g -O2 -Wall -c $(DEFS)



#LIBS=-lMagickWand-6.Q16 -lMagickCore-6.Q16
#LIBS=-lMagickWand-6.Q16HDRI -lMagickCore-6.Q16HDRI

#LDIR=../lib
#LIBDIR=/usr/local/lib/libMagickWand-6.Q16.so.2
#ldconfig /usr/local/lib

OBJDIR=obj
BINDIR=bin

SRCS:=$(shell ls | grep "\.c")
OBJS:=$(SRCS:%.c=obj/%.o)
PROGS:=$(SRCS:%.c=bin/%)


$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

$(BINDIR)/%: $(OBJDIR)/%.o
	gcc -L$(LIBDIR) -g -Wl,-rpath=/usr/local/lib -o $@ $^ $(LIBS)

 
#$(phony clean):
#	rm -f $(PROGRAMS) *.o

all: $(PROGS)
