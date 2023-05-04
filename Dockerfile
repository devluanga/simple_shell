# # Use Ubuntu as the base image
# FROM ubuntu:latest

# # Update package index and install GCC
# RUN apt-get update && apt-get install -y gcc

# # Set the working directory
# WORKDIR /app

# # Copy the source code into the image
# COPY . .

# # Compile the program
# RUN gcc -Wall -Werror -Wextra -pedantic -std=c89 *.c -o hsh

# # Set the entrypoint command
# ENTRYPOINT ["./hsh"]

# Set the base image
FROM ubuntu:latest

# Update the package list
RUN apt-get update

# Install the required dependencies
RUN apt-get install -y gcc

# Copy the source code to the container
COPY . /app

# Set the working directory
WORKDIR /app

# Compile the program
RUN gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

# Set the entrypoint command
ENTRYPOINT ["/app/hsh"]
