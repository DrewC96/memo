# 0002: Store notebooks in SQLite

Date: 2026-11-10
Status: Accepted

## Context

Notes must survive crashes, open quickly, and load partially (one page, not a
whole notebook). Raw ink is also the training data for the recognizer, so it
must be kept in full.

## Decision

- One SQLite database per notebook, written from the C++ engine.
- Strokes are stored as compact binary blobs per page. Raw ink (points,
  timestamps, pressure) is kept permanently.
- Write-ahead logging for autosave and crash safety.
- A schema version table and a versioned blob encoding, so formats can change
  without losing old notes.

## Alternatives rejected

- A custom binary file format: crash safety, partial loading and migrations
  would all have to be built by hand.
- JSON: too large and slow for dense ink.
- One file per page: harder to keep consistent and to back up.

## Consequences

- Migrations must be written and tested whenever the schema or blob format changes.
- Database files hold personal notes, so they are excluded from git.
- SQLite is a dependency of the engine, managed through vcpkg.
