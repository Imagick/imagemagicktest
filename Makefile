

WAND_CFG=/usr/local/bin/MagickWand-config


DEFS=-DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16

# need to set libs to /usr/local/bin/MagickWand-config --libs
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


.PHONY : clean

clean:
	rm -f $(OBJDIR)/*.o

all: $(BINDIR)/%



