# 0003: Everything runs locally

Date: 2026-11-10
Status: Accepted

## Context

Notes and handwriting are personal data. Memo also needs to work in class
without a reliable network connection.

## Decision

- Notes, ink, trained models and recognition all stay on the user's machine.
- No cloud recognition APIs.
- The Python service is reachable only from the local machine (a named pipe
  or a loopback-only connection).
- No sync or collaboration in the first versions.

## Alternatives rejected

- A cloud recognition API: faster to start, but it sends handwriting off the
  machine, costs money, and fails offline.

## Consequences

- The recognizer has to be trained and shipped by this project, and must run
  acceptably on the Intel laptop (CPU or integrated GPU).
- Backups are the user's responsibility, so an export feature is needed later.
- Model files and training data stay out of git.
