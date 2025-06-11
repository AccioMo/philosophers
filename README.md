# Philosophers

This project is an implementation of the classic "Dining Philosophers" problem in C. It is divided into two parts: `philo` and `philo_bonus`.

## Structure

- `philo/`: Contains the implementation without using semaphores.
- `philo_bonus/`: Contains the implementation using semaphores.

## Requirements

- GCC compiler
- Make
- Docker (optional, for containerized builds)

## Build and Run

### Using Makefile

1. Navigate to the `philo` or `philo_bonus` directory.
2. Run `make` to build the project.
3. Execute the generated binary:
   - For `philo`: `./philo/philo`
   - For `philo_bonus`: `./philo_bonus/philo_bonus`

### Using Docker

1. Build the Docker image:
   ```sh
   docker build -t philosophers .
   ```
2. Run the container:
   ```sh
   docker run --rm philosophers
   ```

## Files

- `actions.c`: Contains the actions performed by philosophers.
- `create.c`: Handles the creation of threads or processes.
- `functions.c`: Contains utility functions.
- `main.c`: Entry point of the program.
- `utils.c`: Helper functions.

## License

This project is licensed under the MIT License.
