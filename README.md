# Memo

A Windows app for ink note taking and management. Memo is designed to be simple, fast, and efficient, so you can jot down ideas, organize notes, and find them again quickly.

<!-- Add a screenshot of the Home page here -->
<!-- ![Memo home page](docs/home.png) -->

## Features

**Current**
- Notebooks and pages, organized OneNote-style
- Home page with recent pages and a notebook shelf
- Navigation pane for Home, Library, Recent, and Trash
- Dark theme with a jade and green accent palette
- Ink canvas for handwriting with a pen or touch

**In progress**
- Fast, infinite ink canvas with save and load
- Per-notebook cover colors, changeable by right-clicking a notebook
- Search across notebooks and pages

**Planned**
- Handwriting recognition that runs locally on the device
- A model fine-tuned on the user's own handwriting
- Math checking: Memo reads your handwritten work and flags logical errors, such as bad algebra or invalid proof steps
- Possible iPad and Apple Pencil support later

## Tech stack

| Layer | Technology |
|-------|------------|
| Frontend | .NET, WinUI 3 (Windows App SDK) |
| Backend | C++ |
| ML | Python |

## Getting started

### Requirements
- Windows 10 (1809+) or Windows 11
- Visual Studio 2022 with the **.NET desktop development** and **Windows application development** workloads
- A pen or touch display is recommended for ink input

### Build and run
1. Clone the repository:
   ```
   git clone <your-repo-url>
   cd memo
   ```
2. Open the solution in Visual Studio 2022.
3. Set the configuration to **Debug | x64**.
4. Press **F5** to build and run.

## Project structure

```
app/Memo/        WinUI 3 application (pages, controls, resources)
Assets/          Fonts and images
```

<!-- Update this as the C++ backend and ML code are added -->

## Roadmap

1. Fast ink canvas with save and load
2. Notebook and page management
3. Local handwriting recognition
4. Fine-tuning on personal handwriting
5. Math error detection

## License

MIT
