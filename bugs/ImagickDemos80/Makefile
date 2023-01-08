

WAND_CFG=/usr/local/bin/MagickWand-config


IM_VERSION=`/usr/local/bin/MagickWand-config --version | cut -c 1-1`

# DEFS=-DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16 -DIM$(IM_VERSION)=1
DEFS=-DIM$(IM_VERSION)=1

# need to set libs to /usr/local/bin/MagickWand-config --libs
LIBS=`$(WAND_CFG) --libs`


#centos
LIBDIR=


.SUFFIXES:

CFLAGS=`$(WAND_CFG) --cflags`

OBJDIR=obj
BINDIR=bin

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@ $(DEFS)

%: %.o
	gcc -g -Wl -o $@ $< $(LIBS)

	#gcc -L$(LIBDIR) -g -Wl,-rpath=/usr/sbin/lib -o $@ $< $(LIBS)


.PHONY : clean

clean:
	rm -f $(OBJDIR)/*.o

all: $(BINDIR)/%



