# Nim4Python

- [NimScript](https://nim-lang.github.io/Nim/nims.html) Interoperability for Python.


# Install

- `pip install nim4py`


# Use

```console
$ echo 'echo "NimScript embedded on Python"' > file.nims

$ python
Python 3.8.3 (default, May 17 2020, 18:15:42) [GCC 10.1.0] on linux
>>> from nimscript4python import nimscript
>>> nimscript("file.nims", ["/home/juan/.choosenim/toolchains/nim-1.2.2/lib/"])
NimScript embedded on Python

```


[![](https://raw.githubusercontent.com/juancarlospaco/nimscript4python/master/temp.png)](https://www.youtube.com/watch?v=BdQkU_HepIg)


# Requisites

- [Nim](http://nim-lang.org),
  [you can install it using choosenim_install](https://github.com/juancarlospaco/choosenim_install#choosenim-integration-for-python-pip).


## FAQ

- Why ?.

It can be useful for some cool ideas, on Nim you do not have GIL, Garbage Collector, Virtual Machine, etc
but adds code execution at compile-time, powerful metaprogramming, you can "import" C/C++/JS Code and more,
maybe for plugins for a Python project or embedded scripting or similar ideas,
with option to compile to machine code binary or run in the browser or WebAssembly.

- What works of NimScript inside Python ?.

Everything if you pass **all** the standard library folder paths (?).

- Fails to find the NimScript file ?.

Use full path to the `.nims` file, it wont expand stuff like `~`, etc.

- Fails to find the stdlib folder ?.

Use full path to the stdlib folder, it wont expand stuff like `~`, etc.

- Why not PIP ?.

Should be possible to install via Python PIP,
but I dont know how to patch the file that needs to be patched from PIP,
so for now it requires compiling with `nim` compiler. Pull Request welcome.

- Whats NimScript ?.

https://nim-lang.github.io/Nim/nims.html
