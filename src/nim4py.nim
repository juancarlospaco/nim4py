## Nim for Python: A programming language embedded inside a programming language, installable via PIP.
import compiler/nimeval, nimpy


proc nimscript(script: string; nim_stdlib_paths: seq[string]) {.exportpy.} =
  ## NimScript Interpreter for Python, see https://nim-lang.github.io/Nim/nims.html
  ## * ``func nimscript(script: string; nim_stdlib_paths: seq[string])``
  assert script.len > 0, "NimScript must not be empty string"
  assert nim_stdlib_paths.len > 0, "nim_stdlib_paths must not be empty seq"
  let interpreter = createInterpreter(script, nim_stdlib_paths)
  interpreter.evalScript()
  interpreter.destroyInterpreter()
