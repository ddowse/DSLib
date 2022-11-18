DSLib
=====

DSLib is a Library based on the wxWidgets framework for developing easily database used applications.   



## Compile and install on FreeBSD

# Install dependencies

```sh
pkg install gmake fcgi-devkit mcrypt  
```

# Compile

```sh 
cd src/lib/cpp/   
gmake -f Makefile.FreeBSD
```

# Install

```sh
gmake -f Makefile.FreeBSD install
```

