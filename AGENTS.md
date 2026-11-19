# mini_libc

## Purpose

mini_libc is a learning project for understanding how a C runtime and library work. It targets Linux x86-64 with Clang in C23 mode. The project defines its own APIs and carries no promise of libc source or ABI compatibility, portability, or production readiness. Focus on memory, console and file I/O, strings, and containers.

## Build and runtime

- Compile as freestanding C23 with Clang. Use project-owned headers. Clang predefined types and extensions are available where needed.
- Use direct Linux syscalls and keep syscall ABI and process entry details in the platform implementation.
- Use Clang, an assembler, a linker, and binary inspection tools as build tools. Executables and standalone checks must link without libc, external libraries, system startup objects, or compiler runtimes.
- Check final linkage for compiler-generated calls, including memory operations. Supply project-owned implementations when the compiler requires them.

## Naming

- Use `Mini` as the public namespace and `__` as the namespace separator.
- Use PascalCase for functions, types, struct and enum names, enumerators, and compile-time constants. For example, use `Mini__PrintF` and `Mini__StringView`.
- Use snake_case for variables and fields. Keep ABI-mandated spellings such as `_start` at the runtime boundary.
- Expose fully qualified names in public headers. In a private header, gate explicit aliases such as `#define PrintF Mini__PrintF` with `#ifdef UsingMini`. Implementation files opt in by defining `UsingMini` before including that header.

## API conventions

- Represent sized string views with a pointer and an explicit length.
- Distinguish borrowed views from owned data and document lifetime and ownership where relevant.
- Use `Option` for ordinary absence and `Result` for recoverable errors. Choose concrete layouts and signatures as each module takes shape.

## Working with the maintainer

Guide first. Explain tradeoffs and leave new core algorithms and API decisions to the maintainer unless delegated. Help with requested repetitive work, debugging, and code review. Measure performance before and after optimizations.

## First milestone

Build a freestanding executable that writes to the console and exits through direct Linux syscalls. Verify its output and exit status. Inspect the ELF to confirm it has no interpreter, dynamic dependencies, or unresolved symbols. Apply the same dependency checks to future standalone binaries.

Choose allocator, formatting, file API, and container details when work on each module begins.
