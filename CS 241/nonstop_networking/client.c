/**
* Networking Lab
* CS 241 - Spring 2018
*/

#include "common.h"
#include "format.h"
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdbool.h>
#include <arpa/inet.h>
char **parse_args(int argc, char **argv);
verb check_args(char **args);

size_t read_from_socket(int sock_fd, char* line, size_t num){
    	size_t byte_read = 0;
    	while (byte_read < num) {
        ssize_t new_read = read(sock_fd, line + byte_read, num - byte_read);
        if (new_read == 0)
            return byte_read;
        if (new_read == -1 && errno == EINTR)
            continue;
        if (new_read == -1 && errno != EINTR)
            return -1;
        byte_read += new_read;
    }
    	return byte_read;
}

size_t write_to_socket(int sock_fd, char* line, size_t num){
    	size_t byte_write = 0;
    	while (byte_write < num) {
    	ssize_t new_write = write(sock_fd, line + byte_write, num - byte_write);
        if (new_write == 0)
            return byte_write;
        if (new_write == -1 && errno == EINTR)
            continue;
        if (new_write == -1 && errno != EINTR)
            return -1;
        byte_write += new_write;
    }
    	return byte_write;
}

ssize_t get_whole_size(int sock_fd){
    uint64_t whole_size;
    ssize_t read_byte = read_from_socket(sock_fd,(char *)&whole_size, 8);
    if(read_byte == 0 || read_byte == -1) return read_byte;
    return (ssize_t) whole_size;
}


ssize_t write_for_put(size_t size, int sock_fd){
    uint64_t temp = size;
    ssize_t write_byte = write_to_socket(sock_fd, (char *)&temp, 8);

    return write_byte;
}

//help function of my own
int create_connection(const char* host, const char* port){
    	int s;
	int sock_fd = socket(AF_INET, SOCK_STREAM, 0);

	struct addrinfo hints, *result;
	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;

	s = getaddrinfo(host, port, &hints, &result);
	if (s != 0) {
	        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
        	exit(1);
	}

	if(connect(sock_fd, result->ai_addr, result->ai_addrlen) == -1){
                perror("connect");
                exit(1);
        }
	freeaddrinfo(result);
	return sock_fd;
}

void happy_end_client(int sock_fd, char** commands, verb  action){
    char* temp = calloc(1,4);
    ssize_t read_byte = read_from_socket(sock_fd, temp, 3);
    if(read_byte == -1){
        print_connection_closed();
        free(temp);
        exit(1);
    }
    if(strcmp(temp, "OK\n") == 0){
        if (action == DELETE) {
            print_success();
            free(temp);
            return;
        }
        if(action == PUT){
            print_success();
            free(temp);
            return;
        }
        free(temp);
        ssize_t size_all = get_whole_size(sock_fd);
        int final = 1;
        if(action == GET){
            final = open(commands[4],  O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
        }

        ssize_t total_count = 0;
	int max = 65536;
        temp = calloc(1,max);
        while ((read_byte = read_from_socket(sock_fd, temp, 65535)) != 0) {
            if (read_byte == -1) {
                print_connection_closed();
                free(temp);
                exit(1);
            }
            write_to_socket(final, temp, read_byte);
            total_count += read_byte;
        }
	free(temp);
        if (total_count < size_all) {
            print_too_little_data();
            exit(1);
        }
        if (total_count > size_all) {
            print_received_too_much_data();
            exit(1);
        }
        return;
    }else if(strcmp(temp, "ERR") == 0){
        char* message = calloc(1,256);
        read_byte = read_from_socket(sock_fd, message, 255);
        if (read_byte == -1) {
            print_connection_closed();
            free(temp);
            free(message);
            exit(1);
        }
        temp = realloc(temp, 260);
        temp = strcat(temp, message);
        if(temp[5] == '\n' && temp[4] == 'R' && temp[3] == 'O'){
       	   print_error_message(temp + 6);
           free(temp);
           free(message);
           exit(1);
        }
        free(message);
    }
    print_invalid_response();
    free(temp);
    exit(1);
}


void help_get(int sock_fd, char** commands){
//    char* command_need = strdup(commands[3]); //needs free
    size_t count_num = strlen(commands[3]) + 6;
    char* buffer = calloc(1, count_num);
    sprintf(buffer, "GET %s\n", commands[3]);
    ssize_t write_byte = write_to_socket(sock_fd, buffer, count_num - 1);
//    free(command_need);
    free(buffer);
    if(write_byte == -1){
        print_connection_closed();
        exit(1);
    }
    shutdown(sock_fd, SHUT_WR);
    happy_end_client(sock_fd, commands, GET);
}

void help_put(int sock_fd, char** commands){
    int sock_fd_1 = open(commands[4], O_RDONLY, S_IRUSR | S_IWUSR);
    if(sock_fd_1 < 0) exit(1);
    struct stat buf;
    stat(commands[4], &buf);
    // do something?
    size_t size_of_file = buf.st_size;
    
    size_t count_num = strlen(commands[3]) + 6;
    char* buffer = calloc(1, count_num);
    sprintf(buffer, "PUT %s\n", commands[3]);
    
    ssize_t write_byte = write_to_socket(sock_fd, buffer,count_num - 1);
    free(buffer);
    if(write_byte == -1){
        print_connection_closed();
        exit(1);
    }
    write_for_put(size_of_file, sock_fd);

    buffer = calloc(1,65536);
    ssize_t read_byte = 0;
    while ((read_byte = read_from_socket(sock_fd_1, buffer, 65535)) > 0) {
        write_byte = write_to_socket(sock_fd, buffer, read_byte);
        if (write_byte == -1) {
            print_connection_closed();
            free(buffer);
            exit(1);
        }
    }
    free(buffer);

    shutdown(sock_fd, SHUT_WR);
    happy_end_client(sock_fd, commands, PUT);
}

void help_list(int sock_fd, char** commands){
    char* buffer = calloc(1, 6);
    sprintf(buffer, "LIST\n");
    ssize_t write_byte = write_to_socket(sock_fd, buffer, 5);
    free(buffer);
    if(write_byte == -1){
        print_connection_closed();
        exit(1);
    }
    shutdown(sock_fd, SHUT_WR);
    happy_end_client(sock_fd, commands, LIST);
}

void help_delete(int sock_fd, char** commands){
    size_t count_num = strlen(commands[3]) + 9;
    char* buffer = calloc(1, count_num);
    sprintf(buffer, "DELETE %s\n", commands[3]);
    ssize_t write_byte = write_to_socket(sock_fd, buffer, count_num - 1);
    free(buffer);
    if(write_byte == -1){
        print_connection_closed();
        exit(1);
    }
    shutdown(sock_fd, SHUT_WR);
    happy_end_client(sock_fd, commands, DELETE);
}
//main function
int main(int argc, char **argv) {
    // Good luck!
    char **commands = parse_args(argc,argv);
    int sock_fd = create_connection(commands[0], commands[1]);
    verb new_verb = check_args(argv);
    if(new_verb == GET) help_get(sock_fd,commands);
    else if(new_verb == PUT)  help_put(sock_fd,commands);
    else if(new_verb == LIST) help_list(sock_fd,commands);
    else if(new_verb == DELETE) help_delete(sock_fd,commands);
    free(commands);
    close(sock_fd);
//    return 1;
}

/**
 * Given commandline argc and argv, parses argv.
 *
 * argc argc from main()
 * argv argv from main()
 *
 * Returns char* array in form of {host, port, method, remote, local, NULL}
 * where `method` is ALL CAPS
 */
char **parse_args(int argc, char **argv) {
    if (argc < 3) {
        return NULL;
    }

    char *host = strtok(argv[1], ":");
    char *port = strtok(NULL, ":");
    if (port == NULL) {
        return NULL;
    }

    char **args = calloc(1, 6 * sizeof(char *));
    args[0] = host;
    args[1] = port;
    args[2] = argv[2];
    char *temp = args[2];
    while (*temp) {
        *temp = toupper((unsigned char)*temp);
        temp++;
    }
    if (argc > 3) {
        args[3] = argv[3];
    }
    if (argc > 4) {
        args[4] = argv[4];
    }

    return args;
}

/**
 * Validates args to program.  If `args` are not valid, help information for the
 * program is printed.
 *
 * args     arguments to parse
 *
 * Returns a verb which corresponds to the request method
 */
verb check_args(char **args) {
    if (args == NULL) {
        print_client_usage();
        exit(1);
    }

    char *command = args[2];

    if (strcmp(command, "LIST") == 0) {
        return LIST;
    }

    if (strcmp(command, "GET") == 0) {
        if (args[3] != NULL && args[4] != NULL) {
            return GET;
        }
        print_client_help();
        exit(1);
    }

    if (strcmp(command, "DELETE") == 0) {
        if (args[3] != NULL) {
            return DELETE;
        }
        print_client_help();
        exit(1);
    }

    if (strcmp(command, "PUT") == 0) {
        if (args[3] == NULL || args[4] == NULL) {
            print_client_help();
            exit(1);
        }
        return PUT;
    }

    // Not a valid Method
    print_client_help();
    exit(1);
}
