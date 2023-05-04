# Use Ubuntu as the base image
FROM ubuntu:latest

# Update package index and install GCC
RUN apt-get update && apt-get install -y gcc

# Set the working directory
WORKDIR /app

# Copy the source code into the image
COPY . .

# Compile the program
RUN gcc -Wall -Werror -Wextra -pedantic -std=c89 *.c -o hsh

# Set the entrypoint command
ENTRYPOINT ["./hsh"]
