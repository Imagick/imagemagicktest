<?php


$colours = [
    'blue',
    'transparent'
];

foreach ($colours as $colour) {

    $draw = new \ImagickDraw();
    $draw->setStrokeOpacity(1);

    $draw->setFillColor('white');
    $draw->point(0, 0);

    $draw->setFillColor('yellow');
    $draw->point(0, 1);

    $draw->setFillColor('red');
    $draw->point(0, 2);

    $gradient = new Imagick();
    $gradient->newPseudoImage(1, 5, 'xc:' . $colour);
    $gradient->drawImage($draw);
    $gradient->setImageFormat('png');

    $gradient_filename = __DIR__ . "/clut_gradient_image_$colour.png";
    $gradient->writeImage($gradient_filename);

//    $gradient->setImageAlphaChannel(Imagick::ALPHACHANNEL_DEACTIVATE);

    $canvas = new Imagick(__DIR__ . "/clut_drawn_image.png");
    $gradient = new Imagick($gradient_filename);
    $canvas->clutImageWithInterpolateMethod($gradient, Imagick::INTERPOLATE_BILINEAR);
    $canvas->writeImage(__DIR__ . "/clut_with_interpolate_$colour.png");
};

