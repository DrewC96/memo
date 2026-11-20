# 0004: Recognize first, then check with a symbolic engine

Date: 2026-11-10
Status: Accepted

## Context

Memo should flag wrong algebra steps in handwritten notes. A model that only
classifies "this page has a mistake" cannot verify algebra and cannot explain
what is wrong.

## Decision

A pipeline, not an end-to-end classifier:

1. Group strokes into lines by position (one line is one step).
2. Recognize each line into LaTeX with an online (stroke-based) model that is
   fine-tuned on my own handwriting.
3. Check each step against the previous one with SymPy: symbolic equivalence
   first, random numeric substitution as a fallback, and solution-set checks
   for equation chains.
4. Show a subtle marker beside the first failing line. If recognition
   confidence is low, show "could not read this line" instead of a mistake flag.

## Alternatives rejected

- An end-to-end classifier: needs far more labeled data than one person can
  produce, and gives no reason for its answers.
- An LLM as the checker: non-deterministic and heavy to run locally.

## Consequences

- Recognition errors can look like math errors, so the confidence threshold
  is a core feature, not a polish item.
- The checker can be tested with typed LaTeX, independent of the recognizer.
- Scope is algebra and basic calculus step chains. Proofs are out of scope.
