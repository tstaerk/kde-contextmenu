#!/bin/bash

# setup.sh (c) 2013 by Thorsten Staerk (http://www.staerk.de/thorsten/kde-contextmenu)
# This program builds and installs kde-contextmenu. It is especially important to have
# the correct parameters for the cmake call and to call kbuildsycoca4 after 
# installation. With this script you cannot forget it :) Also, it outputs sensible
# error messages to help the user when build/install goes wrong.

# define a function die()
die() { echo "$@" 1>&2 ;exit 1; }

mkdir -p build 2>/dev/null || die "Cannot create directory build. Please cd to your home directory."
cd build
cmake -DCMAKE_INSTALL_PREFIX=`kde4-config --prefix` .. 2>/dev/null || die "Cannot call cmake. Please install cmake."
make -j8 2>/dev/null || die "Cannot build. Make sure gcc, make and libkde4-devel is installed."
make install 2>/dev/null || die "Cannot install. Make sure you are root."

# re-discover .desktop files
kbuildsycoca4 2>/dev/null || die "Cannot call kbuildsycoca4. Make sure KDE 4 is installed."

