#!/usr/bin/env bash

set -e
set -x

# git clone https://github.com/ImageMagick/ImageMagick.git
# SRCFILE="ImageMagick-7.0.8-14"
SRCFILE="ImageMagick-7.1.0-4"


tar -xzf /var/app/imagemagick_src/${SRCFILE}.tar.gz -C /var/app/imagemagick_src

cd /var/app/imagemagick_src/${SRCFILE}

./configure --with-quantum-depth=16 \
           --with-magick-plus-plus=no \
           --without-perl \
           --disable-docs \
           --with-jpeg=yes \
           --with-png=yes \
           --with-fontconfig=yes \
           --with-webp=yes \
           --with-tiff=yes



# --disable-openmp

# ImageMagick appears to not fully respect lib paths even when
# setting `--libdir=/usr/local/lib` running this ldconfig command
# is needed to avoid errors like:
# convert -v
# convert: error while loading shared libraries: libMagickCore-7.Q16HDRI.so.9:
# cannot open shared object file: No such file or directory
sudo ldconfig /usr/local/lib

# If for some reason you can't run ldconfig, you could also symlink
# the files directly.
# ln -s /usr/local/lib/libMagickCore-7.Q16HDRI.so.0 /usr/lib/x86_64-linux-gnu/libMagickCore-7.Q16HDRI.so.0
# ln -s /usr/local/lib/libMagickWand-7.Q16HDRI.so.0 /usr/lib/x86_64-linux-gnu/libMagickWand-7.Q16HDRI.so.0

make install -j 4

