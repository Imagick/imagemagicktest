
CC=gcc
CFLAGS=-I/usr/local/include/ImageMagick-6
DEFS=-DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16
DEPS = hellomake.h


LDIR =../lib

#IMAGICK_SHARED_LIBADD = -Wl,-rpath,/usr/local/lib -L/usr/local/lib -lMagickWand-6.Q16 -lMagickCore-6.Q16

#ldconfig /usr/local/lib

LIBS=-lMagickWand-6.Q16 -lMagickCore-6.Q16

ODIR=obj



first.o: first.c
	$(CC) -c -o $@ $< $(CFLAGS) $(DEFS)



.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

hellomake: first.o
	gcc -o $@ $^ $(CFLAGS) $(DEFS) $(LIBS)
