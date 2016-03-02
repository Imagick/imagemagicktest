
set -eux -o pipefail
# set -x

packages=()

packages+=("autoconf")
packages+=("bison")
packages+=("re2c")
packages+=("bzip2-devel")
packages+=("libcurl-devel")
packages+=("libjpeg-turbo-devel")
packages+=("libpng-devel")
packages+=("libxml2-devel")
packages+=("freetype-devel")
packages+=("libpng")
packages+=("libjpeg-turbo")
packages+=("libmcrypt-devel")
packages+=("libicu-devel")
packages+=("libyaml-devel")
packages+=("ghostscript")
packages+=("gcc")
packages+=("gcc-c++")
packages+=("openssl-devel")
packages+=("pcre-devel")
packages+=("jasper-devel")
packages+=("lcms-devel")
packages+=("libX11-devel")
packages+=("libXext-devel")
packages+=("ghostscript-devel")
packages+=("libtiff-devel")
packages+=("giflib-devel")
packages+=("libtool")



#this is an implode
packageString=$( IFS=$' '; echo "${packages[*]}" )

echo "Installing packages $packageString"

# yum -y erase python-setuptools-0.6.10-3.el6.noarch
#remove this package without any of it's dependencies.
rpm -e --nodeps python-setuptools-0.6.10-3.el6.noarch || true

yum -y install $packageString



