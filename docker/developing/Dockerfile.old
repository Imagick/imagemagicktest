FROM debian:10-slim

USER root

## Get Debian up-to-date
#RUN apt-get update -qq \
#    && DEBIAN_FRONTEND=noninteractive apt-get install -y \
#    apt-transport-https autoconf bison bsdmainutils ca-certificates curl \
#    gcc git gnupg lsb-release make pkg-config re2c wget \
#    libpng-dev libjpeg-dev ghostscript libxml2-dev libfreetype6-dev \
#    libonig-dev libssl1.0-dev libcurl4-openssl-dev libwebp-dev vim \
#    strace valgrind libtiff5-dev
#
# libssl1.0-dev libonig-dev


RUN apt-get update -qq \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y git \
    mariadb-client wget curl unzip inetutils-ping \
    ca-certificates lsb-release apt-transport-https gnupg libtiff5-dev libwebp-dev \
    libpng-dev libjpeg-dev ghostscript libxml2-dev libfreetype6-dev \
    gcc git gnupg make pkg-config re2c \
    strace valgrind

# Install 3rd party PHP packages
RUN echo "deb https://packages.sury.org/php/ $(lsb_release -sc) main" | tee -a /etc/apt/sources.list.d/php.list \
    && curl https://packages.sury.org/php/apt.gpg | apt-key add - \
    && apt-get update -qq \
    && DEBIAN_FRONTEND=noninteractive apt-get install -y php8.0 php8.0-common php8.0-cli php8.0-fpm \
    php8.0-mysql  php8.0-curl php8.0-xml php8.0-mbstring php8.0-imagick \
    php8.0-intl php8.0-redis php8.0-zip



# Make the default directory you
WORKDIR /var/app

CMD tail -f /var/app/README.md

