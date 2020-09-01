import compiler/nimeval, nimpy


proc nimscript(script: string; stdlib: seq[string]) {.exportpy.} =
  ## NimScript Interpreter for Python, see https://nim-lang.github.io/Nim/nims.html
  ## func nimscript(script: string; stdlib: openArray[string]; verbose: bool = false)
  assert script.len > 0, "NimScript must not be empty string"
  assert stdlib.len > 0, "stdlib must not be empty openArray"
  let interpreter = createInterpreter(script, stdlib)
  interpreter.evalScript()
  interpreter.destroyInterpreter()
