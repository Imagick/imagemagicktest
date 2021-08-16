imagemagicktest
===============

A C test suite/bug finder exercise.

This is very rough and ready dev environment for reproducing ImageMagick bugs in C code.


## Instructions/sugggestions

### Get the box running 

`docker-compose up --build developing`

### Install imagemagick

Download an appropriate release from https://github.com/ImageMagick/ImageMagick/releases into the imagemagick_src directory, and then the script `installImageMagick.sh` might work, or just look at what it does.

Then run `ldconfig /usr/local/lib` to make ImageMagick actually work... 

### Compile some C code

`make 452_borderImage`

which will produce a binary (or compile errors) which can be run with

`./452_borderImage`

And Robert is your father's brother.
