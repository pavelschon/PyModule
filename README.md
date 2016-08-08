# Boost::Python project skeleton #

The project is a skeleton of **Boost::Python** project. It supports both **Python 2.x** and **Python 3.x**.

## Requirements ##

1. C++ compiler

2. CMake

3. Python headers (2.x or 3.x)

4. Boost libraries


## Build ##

```
$ mkdir build
$ cd build
$ cmake ..
$ make -j4 package
$ dpkg -i pymodule-0.1.0-Linux.deb
```

## Run ##

```
$ python -c "import pymodule; pymodule.greet()"
greet from pymodule
```
