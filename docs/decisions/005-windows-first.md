# 0005: Windows first, engine kept portable

Date: 2026-11-10
Status: Accepted

## Context

The target machine is a Windows laptop with a pen (HP MPP 2.0 Tilt Pen).
An iPad with Apple Pencil is a possible later target.

## Decision

- Target Windows x64 only for now, with a WinUI 3 shell.
- Keep `engine/core` (document model, geometry, undo, serialization) free of
  Windows APIs. Windows-specific code lives in `engine/render` and the input glue.

## Alternatives rejected

- A cross-platform UI framework now: adds an abstraction layer next to the pen
  path and splits effort before the core app works.

## Consequences

- An iPad version would need a new shell and renderer. Only the engine core,
  storage format and ML parts would be reused.
- macOS and Linux are non-goals.
