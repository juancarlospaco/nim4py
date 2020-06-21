# NimScript4Python

- [NimScript](https://nim-lang.github.io/Nim/nims.html) Interoperability for Python.


# Troubleshooting

`ImportError: dynamic module does not define module export function` OR `Segmentation fault` ?.

- Rename the compiled output file to `nimscript4python.so` on Linux and Mac, or `nimscript4python.pyd` on Windows,
  this is a Bug on Pythons `setuptools.Extension`, it renames the output file to random crap, not my bug.

**Example:**

If it install with the filename
`/usr/lib/python3.8/site-packages/nimscript4python.cpython-3.8.1-x86_64-linux-gnu.so`,
rename it to
`/usr/lib/python3.8/site-packages/nimscript4python.so`,
If it still wont work, uninstall it, and compile it again but with the filename
`nimscript4python.so` on Linux and Mac, or `nimscript4python.pyd` on Windows, not my bug.

The solution is that it *must* be compiled with the filename `nimscript4python`.
