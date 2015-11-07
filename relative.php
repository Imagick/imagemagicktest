<?php

    chdir("/home/github/imagemagicktest/output");
    echo "curr dir ".getcwd()."\n";

    $imagePath = "../subdir/61806Convert_red.png";

    $radius = 5; 
    $sigma = 1;
    $channel = \Imagick::CHANNEL_DEFAULT;

    $imagick = new \Imagick($imagePath);
    $imagick->adaptiveBlurImage($radius, $sigma, $channel);
//    header("Content-Type: image/jpg");
//    echo $imagick->getImageBlob();

    $imagick->writeImage("relativeTestPHP.png");