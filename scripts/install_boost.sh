#!/usr/bin/env bash
##  Download the Boost libraries into the lib folder and create the "src" links.

download_boost() {
    ##  Download the Boost library named by $1.
    if [ ! -d lib ]; then
        mkdir lib
    fi
    if [ ! -d lib/boost_$1 ]; then
        mkdir lib/boost_$1
    fi
    cd lib/boost_$1
    rmdir $1  ####
    if [ ! -d $1 ]; then
        git clone https://github.com/boostorg/$1.git
    fi
    if [ ! -d src  ]; then
        mkdir src
    fi
    cd src
    if [ ! -f boost_$1.hpp ]; then
        echo //  Force boost_$1 library to be included. >boost_$1.hpp
    fi
    if [ ! -h boost ]; then
        ln -s ../$1/include/boost .
    fi
    cd ../../..
}

download_boost assert
download_boost config
download_boost core
download_boost detail
download_boost iterator
download_boost lockfree
download_boost mpl
download_boost parameter
download_boost predef
download_boost preprocessor
download_boost static_assert
download_boost type_traits
download_boost utility

