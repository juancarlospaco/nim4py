# NimScript4Python

- [NimScript](https://nim-lang.github.io/Nim/nims.html) Interoperability for Python.


```console
$ nim c -d:release --app:lib --out:nimscript5python.so nimscript5python.nim
Hint: 9310 LOC; 20 sec; 300MiB peakmem; Dangerous build; proj: nimscript4python.nim; out: nimscript4python.so [SuccessX]

$ file nimscript4python.so
nimscript4python.so: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked, not stripped

$ echo 'echo "NimScript embedded on Python!"' > file.nims

$ python
Python 3.8.3 (default, May 17 2020, 18:15:42) [GCC 10.1.0] on linux
>>> import nimscript4python
>>> nimscript4python.nimscript("file.nims", ["/home/juan/.choosenim/toolchains/nim-1.2.2/lib/"])
NimScript embebed on Python

```
