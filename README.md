# Tetris Agent

![Tetris](https://img.shields.io/badge/Game-Tetris-00BFFF)
![C](https://img.shields.io/badge/Language-C-00599C)
![License](https://img.shields.io/badge/License-MIT-green)

A fast, lightweight **Tetris implementation** written in C with several heuristic algorithms and performance analysis tools. Built as a TIPE project for the 2026 French MPI engineering entrance exams.


## Overview

This project implements a complete Tetris game engine in C along with multiple AI agents that can play the game autonomously. It includes:

- Several evaluation heuristics (simple, random, linear)
- Depth-limited search with averaging
- Optimizations using next-piece prediction to significantly reduce computation time
- A robust analysis module to benchmark algorithm performance over thousands of games


## Features

- **Several Strategies**:
  - Random agent (baseline)
  - Simple heuristic agent
  - Depth-average search with linear evaluation
  - Optimization by predicting following pieces using set theory

- **Analysis Tools**:
  - `analysis.c` perform several simulations
  - Detailed statistics (average lines cleared, average score, standard deviation)


## How to use

### Prerequisites
- GCC & Make

### Compilation
- Compilation : ```make```
- Execution : ```./exec```
