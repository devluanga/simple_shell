              **  Building a simple shell in C**

List of allowed functions and system calls
            access (man 2 access)
            chdir (man 2 chdir)
            close (man 2 close)
            closedir (man 3 closedir)
            execve (man 2 execve)
            exit (man 3 exit)
            _exit (man 2 _exit)
            fflush (man 3 fflush)
            fork (man 2 fork)
            free (man 3 free)
            getcwd (man 3 getcwd)
            getline (man 3 getline)
            getpid (man 2 getpid)
            isatty (man 3 isatty)
            kill (man 2 kill)
            malloc (man 3 malloc)
            open (man 2 open)
            opendir (man 3 opendir)
            perror (man 3 perror)
            read (man 2 read)
            readdir (man 3 readdir)
            signal (man 2 signal)
            stat (__xstat) (man 2 stat)
            lstat (__lxstat) (man 2 lstat)
            fstat (__fxstat) (man 2 fstat)
            strtok (man 3 strtok)
            wait (man 2 wait)
            waitpid (man 2 waitpid)
            wait3 (man 2 wait3)
            wait4 (man 2 wait4)
            write (man 2 write)   


**Compilation**
run this code to compile the program

        gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

		SIMPLE SHELL pROJECT
#PARSING DATA
1.  create variables to hold input string without delimters
        say char *inputptr;
2.  create a variable to hold the delimters
        const char *delim = '\n'
3.  dynamically allocate memory to inputptr
        inputptr = malloc(sizeof(char)*input_count);
        if (inputptr == NULL)
        {
            perror("memory allocation failed!!\n");
            exit(EXIT_FAILURE);
        }
4.  make a copy of input string to store in inputptr
        strcpy(inputptr, source);
5.  split the string stored in inputptr into an array hence:
            a. calc the total number of tokens expected.
                token = strtok(source, delimeters);
                while(token != NULL)
                {
                    tokenvalue++;
                    toek = strtok(NULL, delimeters);
                }
                tokenvalue++
            b. using the number of tokens from above allocate the required memory
               to hold array of all the string as the 
               argv = malloc(sizeof(char *)* tokenvalue);
            c. store the tokens properly in the array.
            token = strtok(inputptr, delimeters);
                for (int x = 0; x != NULL; x++ )
                {
                    argv[x] = malloc(sizeof(char)* strlen(tokenvalue));
                    strcpy(argv[x], token);

                    token = strtok(NULL, delimeters);
                }
                argv[x] = NULL;


##Implementing the execve functionality of the imput
        -->built-in commands
        -->Binary executable 
        -->Aliases
Now that we have been able to create a problem get the user input and even store it in an array,
we need to use the execute commands ti make sure that thesecommands are properly executed as per user needs.

In this project we are restricted to using execve command only and we'll begin by looking at its man page 
        man 3 execve

image.png

SYNOPSIS
       #include <unistd.h>

       int execve(const char *pathname, char *const argv[],
                  char *const envp[]);

from the above the execve command will need some arguements to be passed
        pathname
        argv[]
        envvp -->environment arguements
    >>environment variables
        these are all the commands created and maintained at the OS level.
        inside these variables we have path variables that make it possible for execve to execute commands given to it.
    >so I will create another file to handle command execution
        execfile.c

##Configuring the path for commands
-->> we'll create a file to configure the path for each command the user gives to our terminal
            filepath.c
-->>we then use the command getenv function to get the environment for the path
-->Now to get the path each given command;
        1.get the length of the command
            clength = strlen(command)
        2.break the loop the path into tokens
            ctokens = strtok(cpath, ":");
        3.create a loop to ensure we append (/) followed by the command, then a terminating null character(\0)

            Dockerfile
Docker is a powerful platform for developing, shipping and running applications inside lightweight, portable containers. By incorporating Docker into our shell project, we can achieve several benefits:

1. Reproducible builds
Docker containers help maintain consistent environments across development, testing, and production stages, eliminating the "it works on my machine" problem.
2. Faster deployments
Docker images can be quickly built, shipped, and deployed, speeding up the overall deployment process.
3. Scalability
Docker enables easy horizontal scaling of your application, ensuring high availability and optimal resource utilization.
4. Isolation
Containers provide an isolated environment for your applications, preventing potential conflicts with other applications or system dependencies.

To build the Docker image, navigate to the directory where you saved the Dockerfile and run the following command:
            docker build -t my-shell-image .

This will build the Docker image and tag it with the name my-shell-image. 
Don't forget the . at the end of the command, which tells Docker to look for the Dockerfile in the current directory.

Once the image is built, you can run your shell program inside a Docker container using the following command:

        docker run -it my-shell-image

This will start a new Docker container from the my-shell-image image and run your shell program inside it.
