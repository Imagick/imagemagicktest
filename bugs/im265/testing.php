<?php




$imagick = new \Imagick();
$imagick->newPseudoImage(300, 300, "gradient:black-fuchsia");
$imagick->setImageFormat("png");
$imagick->writeImage(__DIR__ . "/output.png");

echo "fin.\n";