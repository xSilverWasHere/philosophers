# Philosophers

*This project has been created as part of the 42 curriculum by jpedro-g.*

## Description

Philosophers is a multithreading and synchronization project that simulates the classic Dining Philosophers problem. The goal is to create a simulation where philosophers sit at a round table, alternating between eating, sleeping, and thinking, while sharing forks and avoiding starvation or deadlock.

Each philosopher needs two forks to eat, but there are only as many forks as philosophers. The program must prevent data races, ensure proper synchronization using mutexes, and detect when a philosopher dies of starvation (when they haven't eaten within `time_to_die` milliseconds).

The project teaches fundamental concepts of concurrent programming: thread management with `pthread_create` and `pthread_join`, mutual exclusion with `pthread_mutex`, race condition prevention, and deadlock avoidance strategies.

## Instructions

### Compilation

```bash
make
```

This will compile the project with flags `-Wall -Wextra -Werror` and produce the `philo` executable.

### Execution

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

**Arguments:**
- `number_of_philosophers`: Number of philosophers and forks
- `time_to_die` (ms): Time until a philosopher dies without eating
- `time_to_eat` (ms): Time a philosopher spends eating (holding two forks)
- `time_to_sleep` (ms): Time a philosopher spends sleeping
- `number_of_times_each_philosopher_must_eat` (optional): Simulation stops when all philosophers have eaten this many times

**Example:**
```bash
./philo 5 800 200 200
./philo 4 410 200 200 5
./philo 1 800 200 200    # Single philosopher case
```

### Expected Output

The program logs state changes with timestamps in milliseconds:
```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

The simulation stops when a philosopher dies or when all have eaten the required number of times.

## Resources

### Classic References
- **Dining Philosophers Problem** - Edsger Dijkstra's original formulation of the synchronization problem
- [POSIX Threads Programming](https://computing.llnl.gov/tutorials/pthreads/) - Lawrence Livermore National Laboratory guide
- `man pthread_create`, `man pthread_mutex_lock`, `man gettimeofday` - POSIX documentation

### AI Usage

AI tools were used for the following tasks:

**Debugging and Testing:**
- Identifying race conditions and timing issues in death detection logic
- Analyzing tester output discrepancies (edge cases with fork acquisition timing)
- Explaining timing precision requirements for the 10ms death print constraint

## Project Structure

```
philo/
├── Makefile
├── philo.h              # Structures and function prototypes
├── main.c               # Argument parsing and program entry
├── init.c               # Data initialization
├── init_threads.c       # Thread creation
├── monitor.c            # Death monitoring loop
├── routine.c            # Main philosopher routine
├── routine2.c           # Phase implementations
├── forks.c              # Fork acquisition logic
├── check.c              # State checks
├── single_philo.c       # Single philosopher case
└── README.md
```