# Ocar
Ocar is a low-level Assembly transpiler (not a compiler!). With its C-inspired syntax, it aims to provide a more visually appealing way of writing raw assembly.
## Now with syntax highlighting!
A previous commit added a VSCode syntax highlighter. To use, run:
```bash
code --install-extension ocarlang-0.0.4.vsix
```
Then press `Ctrl+Shift+P` and type `Developer: Reload Window` and press enter. Then, after creating a `.ocar` file, you *should* be able to see it syntax highlighted!
## Why is it a transpiler and not a compiler?
Technically, it _is_ indeed a compiler. However, because it doesn't provide many features compilers are known to provide (mainly register allocation and recursive expressions), I choose to call it a transpiler because the information for every instruction is pretty much self-contained.
## Syntax example
```
#stdlib entry
#stdlib exit
#stdlib printer

rtn _start() noret {
  rax myVar = 5;
  print_rax_decimal();

  myVar = 10; // ascii code for newline character
  print_rax_char();

  myVar = 25;
  print_rax_decimal();

  myVar = 10; // ascii code for newlien character
  print_rax_char();

  delete myVar;
  exit();
}
```
### Explanation
1) `#stdlib entry` includes `entry.ocar` from the standard library, which defines `_start()` as the entry point.
2) `#stdlib exit` includes `exit.ocar` from the standard library, which allows `exit()` to exit the program with exit code 0.
3) `rtn` means routine. It is the language's version of a function. 
4) `rtn _start()` defines a routine called `_start()`. `noret` makes it that the transpiler doesn't add a `ret` at the end of the function, which is not needed for the entry point.
5) `rbx myVar1 = 3;` and `rcx myVar2 = 5;` define two variables that take up the registers `rbx` and `rcx` respectively. Note that the user manually declares which registers they should take. If any other variable tries to claim those registers without the registers being freed first, the compiler will throw.
6) `@push rax` and `@pop rax` are prefixed with `@` to signal direct assembly conversion; everything after `@` is emitted to assembly directly without any checks.
7) `delete myVar1;` and `delete myVar2;` end the lifetime of `myVar1` and `myVar2`, freeing the registers `rbx` and `rcx` for possible future use.
8) `exit()` cals the standard function imported earlier to exit the program.

## To-do list
- [x] Add register freeing (e.g. `free rax`, `free rdi`)
- [x] Add multiline comments
- [x] Add `syscall` operation
- [x] Raw register access (e.g. `raw rax = 5`)
- [x] Variable support for assignment (allow `rax a = b;`)
- [x] Four operations
  - Implemented three operations; addition, subtraction, and multiplication. Division requires hardcoded registers which doesn't currently work.
- [x] If statements
  - [x] Comparisons
  - [ ] Else statements
- [x] Goto and labels
- [x] While loops
- [ ] For loops
- [ ] Add linking. Probably C-style, because it's easier.
  - [ ] Make a standard library
- [x] `#noheader` option that removes the autogeneration header
- [ ] Stack memory acces (e.g. `stk[bytecount] varname = 0;`, `stk[8] myint = 17;`)
- [ ] Function parameters/arguments
  - Maybe give an optional `autopush` keyword that finds free spots in the stack and pushes the registers used by parameters into them, then loads them on exit, so users don't have to worry about register data disappearing.
- [ ] `auto` keyword to automatically choose an unused register

## Name
Ocar's name is a recursive acronym stnding for OCAR Can't Allocate Registers.
