# 0001: Layered architecture with C++ owning ink and rendering

Date: 2026-11-10
Status: Accepted

## Context

Pen latency is the make-or-break quality of a notetaking app. The app also
needs a UI shell and ML code, and the stack is fixed: C++, .NET and Python.

## Decision

- The C++ engine owns the document model, strokes, spatial index, storage and
  rendering (Direct2D/Direct3D into a swap chain hosted in the WinUI window).
- The .NET app is the shell: windows, toolbar, pages, and pen event capture.
  It calls the engine through a small C API, with opaque handles and plain
  structs only.
- Python runs as a separate local process for recognition and checking. It
  never runs on the UI thread, and the canvas never waits for it.

## Alternatives rejected

- Drawing strokes in .NET: garbage collection and compositor delay put the
  pen-to-pixel path at risk.
- C++/CLI instead of a C API: harder to debug, and it ties the engine to Windows.

## Consequences

- The pen path (input to pixels) stays inside C++, so crossing the .NET
  boundary does not affect drawing latency.
- The engine's `core` stays free of Windows APIs, which keeps an iPad port possible.
- More build complexity: three toolchains must build together. CI covers this.
- The C API must stay small and stable.
