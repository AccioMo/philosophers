
FROM gcc:latest

WORKDIR /app
COPY . /app
RUN make

# Example command
CMD ["./philo/philo", "5", "400", "200", "100"]
