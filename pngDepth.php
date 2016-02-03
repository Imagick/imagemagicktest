<?php



$imagick = new Imagick("./images/pngFlopOriginal.png");
$imagick->flopImage();
//$imagick->setOption('png:format', 'png00');
$imagick->writeImage("./images/pngDepth_output.png");

system('identify -verbose ./images/pngFlopOriginal.png | grep depth');
system('identify -verbose ./images/pngDepth_output.png | grep depth');