# Memo Plan

Memo is a Windows ink notetaking app with a fast infinite canvas. It reads
handwritten math and flags algebra mistakes. The goal is a tool for my own
classes. There is no deadline; work happens at 2-5 hours per week.

Full plan: see the "Memo: Implementation Plan" Claude doc. This file is the
short version that lives with the code.

## Stack

- Engine: C++17, CMake, vcpkg, SQLite, Direct2D/Direct3D
- App: WinUI 3, current .NET LTS, calling the engine through a C API
- ML: Python, PyTorch for training, ONNX Runtime for inference, SymPy for checking
- Everything runs locally. Notes and ink never leave the machine.

## Phases

0. Setup and spikes: repo, CI, pen-to-pixel latency spike on the target laptop
1. Ink canvas MVP: pen, eraser, pan/zoom, pages, save/load, undo/redo
2. Performance and daily use: spatial index, caching, selection, correction tool
3. Collect and label my ink, fine-tune the recognizer, measure on a held-out set
4. Step checker with SymPy
5. Integrate the Python service into the app
6. Polish, search, export, possibly iPad

## Non-goals for now

Sync, collaboration, proof checking, prose recognition, typed rich text,
images, macOS/Linux.

## Current status

Phase 0: repo skeleton and build setup in progress.
