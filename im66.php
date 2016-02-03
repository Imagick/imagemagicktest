<?php

$imagick = new Imagick();
$imagick->newPseudoImage(200, 200, 'xc:white');
$imagick->setImageFormat('tiff');
$imagick->setImageDepth(16);
$imagick->writeImage("./output_default.tif");
system('identify ./output_default.tif');


$imagick = new Imagick();
$imagick->newPseudoImage(200, 200, 'xc:white');
$imagick->setType(\Imagick::IMGTYPE_TRUECOLOR);
$imagick->setImageFormat('tiff');
$imagick->setImageDepth(16);
$imagick->writeImage("./output_forceTrueColor.tif");
system("identify ./output_forceTrueColor.tif");