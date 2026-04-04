# Changelog

## 5.0.3 - (2026-02)
- Cleaned the analysis module
- Fixed statistics calculations

## 5.0.2 - (2026-02)
- Renamed most variables
- Reorganised file architecture
- Optimised and cleaned most functions and structure
- Fixed bugs inherited from the change

## 4.7.1 - (2026-01)
- Added CLI to manipulate algorithms better
- Added analysis module to extract data from the algorithms

## 4.2.1 (2025-11)
- Added Algorithm 7
- Enhanced compute time by reducing, when feasible, the possibles next pieces to calculate by knowing which ones have already been placed before.
- Impelmented sets called Ensemble
- All more complex algorithm are now handled by `markov.c`

## 4.0.1 (2025-10)
- Addded Algorithm 6, iterating policy for each possible pieces on a depth chosen and computing average in each possible scenario.
- Added a function to sanitize algorithms outputs ensuring viable placement
- Packed board evaluation in a single function
- Embeded piece sets in the `Game` structure

## 3.1.0 (2025-10)
- Created an `Analysis` module to assess algorithms performances
- Added support for pentamino
- Added changelog to track devlopment
- Added MIT license
- Encapsulated structures to avoid errors


## 3.0.0 (2025-10)
- Added several linear board analysis function
- Added Algorithm 5, inspired by Pierre Delacherie
- Generalized tetromino values to match any polyomino size

## 2.4.0-  Olders versions
- Such versions are deprecated.
