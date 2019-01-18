FROM ubuntu:18.04


RUN apt update && apt install -y php-cli php-imagick strace

WORKDIR /var/app

CMD tail -f /var/app/readme.MD
