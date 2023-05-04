# get a lightweight image
FROM alpine:latest

# install all required packages
RUN apk update && \
    apk add --no-cache gcc musl-dev

    
# copy the project image
COPY . /root/shell/s_image

# provide a working directory
WORKDIR /root/shell/s_image

# compile the project
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

ENTRYPOINT [ "./hsh" ]