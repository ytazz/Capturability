# Tex

$ platex main.tex
$ dvipdfmx main.dvi

sudo cp /home/kuribayashi/study/capturability/lib/libCapturability.so /usr/local/lib/libCapturability.so

# Installation

## Gnuplot

    $ sudo apt-get install libgd2-dev

    $ cd ~/Downloads
    $ wget http://sourceforge.net/projects/gnuplot/files/gnuplot/5.2.7/gnuplot-5.2.7.tar.gz
    $ tar zxvf gnuplot-5.2.7.tar.gz
    $ cd gnuplot-5.2.7
    $ ls
    $ ./configure --with-gd
    $ make -j4
    $ sudo make install

# Setting

## CUDA

    $ sudo gedit /usr/local/cuda/include/crt/common_functions.h

comment out follow line

```cpp
    // #define __CUDACC_VER__ "__CUDACC_VER__ is no longer supported. Use __CUDACC_VER_MAJOR__, __CUDACC_VER_MINOR__, and __CUDACC_VER_BUILD__ instead."
```