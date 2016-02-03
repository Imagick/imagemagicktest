
#/usr/sbin/bin/MagickWand-config --version

WAND_CFG=/usr/sbin/bin/MagickWand-config
# WAND_CFG=/usr/sbin/bin/MagickWand-config


DEFS=-DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16
#LIBS=-lMagickWand-6.Q16 -lMagickCore-6.Q16
#LIBS=-lMagickCore-6.Q16

# need to set libs to /usr/sbin/bin/MagickWand-config --libs
LIBS=`$(WAND_CFG) --libs`

#centos
LIBDIR=


.SUFFIXES:

CFLAGS=`$(WAND_CFG) --cflags`



OBJDIR=obj
BINDIR=bin

$(OBJDIR)/%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

%: $(OBJDIR)/%.o
	gcc -L$(LIBDIR) -g -Wl,-rpath=/usr/sbin/lib -o $@ $< $(LIBS)
#	gcc -L$(LIBDIR) -g -Wl,-rpath=/usr/local/lib -o $@ $< $(LIBS)



.PHONY : clean

clean:
	rm -f $(OBJDIR)/*.o

all: $(BINDIR)/%



