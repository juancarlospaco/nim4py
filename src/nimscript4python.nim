import compiler/nimeval, nimpy

proc nimscript(script: string; stdlib: openArray[string]; verbose: bool = false) {.exportpy.} =
  ## NimScript Interpreter for Python, see https://nim-lang.github.io/Nim/nims.html
  ## func nimscript(script: string; stdlib: openArray[string]; verbose: bool = false)
  assert script.len > 0, "NimScript must not be empty string"
  assert stdlib.len > 0, "stdlib must not be empty openArray"
  if unlikely(verbose): echo "NimScript: createInterpreter()"
  let interpreter = createInterpreter(script, stdlib)
  if unlikely(verbose): echo "NimScript: evalScript()"
  interpreter.evalScript()
  if unlikely(verbose): echo "NimScript: destroyInterpreter()"
  interpreter.destroyInterpreter()
