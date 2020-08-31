import os, compiler/nimeval, nimpy


let folder = currentSourcePath().splitPath.head
let stdlib = @[
  folder / "lib",
  folder / "lib" / "arch",
  folder / "lib" / "core",
  folder / "lib" / "deprecated",
  folder / "lib" / "experimental",
  folder / "lib" / "impure",
  folder / "lib" / "packages",
  folder / "lib" / "posix",
  folder / "lib" / "pure",
  folder / "lib" / "std",
  folder / "lib" / "system",
  folder / "lib" / "windows",
  folder / "lib" / "wrappers",
]


proc nimscript(script: string; stdlib: seq[string] = stdlib) {.exportpy.} =
  ## NimScript Interpreter for Python, see https://nim-lang.github.io/Nim/nims.html
  ## func nimscript(script: string; stdlib: openArray[string]; verbose: bool = false)
  assert script.len > 0, "NimScript must not be empty string"
  assert stdlib.len > 0, "stdlib must not be empty openArray"
  let interpreter = createInterpreter(script, stdlib)
  interpreter.evalScript()
  interpreter.destroyInterpreter()
