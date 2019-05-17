# PRMS
Precipitation Runoff Modeling System

# Building From Source
To compile PRMS from source on Unix/Linux/POSIX systems, run:

```
./configure CPPFLAGS=-I../mmf LDFLAGS=-L../mmf
make LIBS=-lmmf
```
