<p align="center">
  <img src="https://github.com/xSilverWasHere/42-project-badges/blob/main/covers/cover-philosophers.png" alt="PHILOSOPHERS"/>
</p>

# 🍝 Philosophers – Multithreading and Synchronization in C

*This project has been created as part of the 42 curriculum by jpedro-g.*

Philosophers is a multithreading and synchronization project that simulates the classic Dining Philosophers problem. The goal is to create a simulation where philosophers sit at a round table, alternating between eating, sleeping, and thinking, while sharing forks and avoiding starvation or deadlock.

## 📚 Project Overview

**Objective:**  
Implement a concurrent simulation in which multiple philosopher threads share forks (mutexes), follow precise timing rules, and the program correctly detects when a philosopher dies or when all philosophers have eaten enough times.

**Language:** C  

**Deliverable:**  
- An executable `philo` that:
  - Parses and validates command line arguments.
  - Initializes shared data, philosopher structures, and forks.
  - Spawns one thread per philosopher (plus a monitor thread).
  - Runs the simulation and prints philosopher states with timestamps.

## 🧱 Core Concepts

### Thread & Data Model

- Each philosopher is represented by a structure with:
  - `id`, `meals_eaten`, `last_meal`, and pointers to its left and right fork mutexes.
- Shared configuration and state are stored in a global data structure:
  - `nbr_philo`, `time_to_die`, `time_to_eat`, `time_to_sleep`, `must_eat`.
  - Global flags and counters such as `someone_died` and `finished_eating`.
  - Mutexes for shared state and printing.
  - An array of fork mutexes and an array of philosophers.

### Simulation Flow

- The program:
  - Parses and validates arguments (numeric checks, positive values, correct argument count).
  - Initializes data, forks, philosophers, and threads.
- Time utilities:
  - A function to get the current time in milliseconds.
  - A sleep helper to wait a given amount of milliseconds.
- Each philosopher thread typically loops through:
  - Thinking  
  - Taking forks  
  - Eating  
  - Sleeping  
- A dedicated monitor thread continuously checks:
  - If any philosopher exceeded `time_to_die` since the last meal.
  - If all philosophers have reached the required number of meals (when that argument is provided).
- The **single philosopher** edge case is handled separately so that the simulation behaves correctly when only one fork is available.

## ⚙️ Instructions

### Compilation

``make``

This compiles the project with -Wall -Wextra -Werror and produces the philo executable.

To clean or rebuild:

``make clean``    # Remove object files

``make fclean``  # Remove objects and the philo executable

``make re``       # Rebuild from scratch

Execution

``./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]``

Arguments:

  number_of_philosophers: Number of philosophers and forks.

  time_to_die (ms): Time until a philosopher dies without eating.

  time_to_eat (ms): Time a philosopher spends eating (holding two forks).

  time_to_sleep (ms): Time a philosopher spends sleeping.

  number_of_times_each_philosopher_must_eat (optional): Simulation stops when all philosophers have eaten this many times.

Examples:

``./philo 5 800 200 200``

``./philo 4 410 200 200 5``

``./philo 1 800 200 200``    # Single philosopher case

Output

The program logs state changes with timestamps in milliseconds, for example:

text
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking

The simulation stops when a philosopher dies or when all philosophers have eaten the required number of times.

## 🎯 What I Learned

This project was an opportunity to deepen understanding of:

- **Multithreading fundamentals:** Creating and managing threads, coordinating their lifecycle, and ensuring safe access to shared data using mutexes.
- **Race conditions and deadlocks:** Designing fork acquisition and monitoring logic to avoid deadlock scenarios and minimize race conditions in a highly concurrent context.
- **Timing and precision:** Working with millisecond-accurate timing, detecting philosopher death reliably, and balancing sleeps with periodic checks.
- **Clean concurrent design:** Separating responsibilities across initialization, routines, monitoring, and cleanup to keep the codebase maintainable and easier to debug.
