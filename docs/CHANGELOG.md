# Version History

## Version 3.1.0 - (2026-02)
This update improves the analysis module.

- Cleaned the analysis module
- Updated statistics calculations

## Version 3.0.0 - (2026-02)
This update brings significant improvements to overall code clarity and efficiency.

- Renamed most variables
- Reorganised file architecture
- Optimised and cleaned most functions and structure
- Fixed bugs inherited from the change

## Version 2.4.0 - (2026-01)
This updates brings an analysis module and a terminal-based interface.

- Added CLI to manipulate algorithms better
- Added `analysis` module to extract data from the algorithms

## Version 2.3.0 (2025-11)
This update adds algorithm 7, as fixing some bugs.

- Added Algorithm 7
- Enhanced compute time by reducing, when feasible, the possibles next pieces to calculate by knowing which ones have already been placed before.
- Implemented sets called Ensemble
- All more complex algorithm are now handled by `markov.c`

## Version 2.2.0 (2025-10)
This update adds algorithm 6 and improves algorithms safety.

- Added Algorithm 6, iterating policy for each possible pieces on a depth chosen and computing average in each possible scenario.
- Added a function to sanitise algorithms outputs ensuring viable placement
- Packed board evaluation in a single function
- Embedded piece sets in the `Game` structure

## Version 2.1.0 (2025-10)
This update improves documentation and decrease storage use.

- Added changelog to track development
- Added license to allow use
- Encapsulated structures to avoid errors


## Version 2.0.0 (2025-10)
This update brings significant improvements to algorithms and code.

- Added several linear board analysis function
- Added Algorithm 5, inspired by Pierre Delacherie
- Generalised tetromino values to match any polyomino size


