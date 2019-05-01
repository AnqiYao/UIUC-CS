/**
* Networking Lab
* CS 241 - Spring 2018
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/epoll.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "vector.h"
#include "format.h"
#include "common.h"
#include <sys/mman.h>
#include <sys/stat.h>
#include <signal.h>

static char* port_idx;
static vector* file_vector;
static struct addrinfo* result;
static size_t num_byte_file;
static char* direction;
static char temp_buffer[1024*1000];

void t_handler(int signum) {
		if (signum == SIGINT) {
		size_t i;
		for (i = 0; i < vector_size(file_vector); i++) {
			char* this_str = vector_get(file_vector, i);
			char file_delete[1024];
			memset(file_delete, 0, 1024);
			strcat(file_delete, "./");
			strcat(file_delete, this_str);
			remove(file_delete);
		}
		char temp[1024];
    		getcwd(temp, 1024);
		chdir("./..");
		getcwd(temp, 1024);
		if (rmdir(temp) < 0) {
			fprintf(stderr ,"rmdir fail\n");
		}
		vector_destroy(file_vector);
		freeaddrinfo(result);
		exit(1);
	}
}

void change_size(unsigned char* array, size_t size) {
	  int k;
	  for (k = 0; k < 8; k++) {
			array[k] = 0xFF & size;
			size = size >> 8;
		}
}

size_t change_arr(char* start_size) {
	unsigned char* temp = (unsigned char*)start_size;
	size_t size = 0;
	for (int i = 7; i >= 0; i--) {
		size_t a = temp[i] << (8 * i);
		size += a;
	}
	return size;
}

void happy_end_accept_info(struct epoll_event* event,int epoll_fd){
        while(1) {
        struct sockaddr_in new_addr_in;
        socklen_t new_length = sizeof(new_addr_in);
        int new_fd_idx = accept(event->data.fd, (struct sockaddr*) &new_addr_in, &new_length);

        if(new_fd_idx == -1) {
          if(errno == EAGAIN || errno == EWOULDBLOCK)
            break;
          else {
            perror("accept");
            exit(1);
          }
        }

        char* connect_ip = inet_ntoa(new_addr_in.sin_addr);

        printf("Accepted Connection %s port %s\n", connect_ip, port_idx);

        int flag = fcntl(new_fd_idx, F_GETFL, 0);
        fcntl(new_fd_idx, F_SETFL, flag | O_NONBLOCK);

        struct epoll_event event_e;
        event_e.data.fd = new_fd_idx;
        event_e.events = EPOLLIN | EPOLLET;
        if(epoll_ctl (epoll_fd, EPOLL_CTL_ADD, new_fd_idx, &event_e) == -1) {
            perror("accept epoll_ctl");
            exit(1);
        }
      }
}

void happy_end_data(struct epoll_event* event){
  ssize_t num;
  size_t byte_read = 0;
  int isfinish = 0;
  int isfull = 0;
  int ifoption = 0;
  char* buff_pointer = temp_buffer;

  while(1) {
    num = read(event->data.fd, buff_pointer, 1024*250 - byte_read);
    if(num == -1) {
      if(errno != EAGAIN) {
        perror("read error");
        printf("Closed connection on descriptor %d with error\n", event->data.fd);
        break;
      }
    }if( num == 0) {
      isfinish = 1;
      break;
    }else if(num > 0) {
      byte_read += num;
      buff_pointer = buff_pointer + num;
      if (num >= 1024) {
        isfull = 1;
        break;
      }
    }
  }

  if (byte_read == 5) {
    temp_buffer[4] = 0;
    if (strcmp(temp_buffer, "LIST") == 0) {
      ifoption = 3;
    } else {
      ifoption = 0;
    }
  } else {
    if (strstr(temp_buffer, "GET") == temp_buffer) ifoption = 1;
  	else if (strstr(temp_buffer, "PUT") == temp_buffer) ifoption = 2;
  	else if (strstr(temp_buffer, "LIST") == temp_buffer) ifoption = 3;
  	else if (strstr(temp_buffer, "DELETE") == temp_buffer) ifoption = 4;
    else ifoption = 0;
  }


  if (ifoption == 0) {
    print_invalid_response();
    dprintf(event->data.fd, "ERROR\n%s\n", err_bad_request);
  } else if (ifoption == 1) {
    char* blank = strstr(temp_buffer, " ");
    char* new_line_char = strstr(temp_buffer, "\n");
    char name_of_file[1024];
    memset(name_of_file, 0, 1024);
    *new_line_char = 0;
    strcpy(name_of_file, blank+ 1);
    *new_line_char = '\n';
    int iffind_file = 0;
    for (size_t i = 0; i < vector_size(file_vector); i++) {
      if (strcmp(name_of_file, vector_get(file_vector, i)) == 0) {
        iffind_file = 1;
        break;
      }
    }
    if (!iffind_file) {
      dprintf(event->data.fd, "ERROR\n%s\n", err_no_such_file);
    } else {
      int fd_bendi = open(name_of_file, O_RDONLY, S_IRWXU | S_IRWXG | S_IRWXO);
      struct stat st;
      dprintf(event->data.fd, "OK\n");

			stat(name_of_file, &st);

      size_t size = st.st_size;
      unsigned char size_array[8];
      change_size(size_array, size);
      write(event->data.fd,size_array, 8);
      char* file_arr = mmap(NULL, size, PROT_READ, MAP_FILE | MAP_SHARED, fd_bendi, 0);
      write(event->data.fd, file_arr, size);
      close(fd_bendi);
    }

    close(event->data.fd);
  } else if (ifoption == 2) {
    char* new_line_char = strstr(temp_buffer, "\n");
    char* start_of_size = new_line_char + 1;
		for (int i = 0; i < 10; i++) {
				//wait  for signal
		}
    size_t size_of_file_uploaded = change_arr(start_of_size);
    fprintf(stderr, "size of uploaded file is %zu\n",size_of_file_uploaded);

    char name_of_file[1024];
    memset(name_of_file, 0, 1024);
    char* blank = strstr(temp_buffer, " ");
    *new_line_char = 0;
    strcpy(name_of_file, blank + 1);
    *new_line_char = '\n';
    if (num_byte_file == 0) {
      char temp_arr[] = "XXXXXX";
      direction = mkdtemp(temp_arr);
      print_temp_directory(direction);
      chdir(direction);
    }

    int fd_bendi = open(name_of_file, O_CREAT | O_TRUNC | O_RDWR, S_IRWXU | S_IRWXG | S_IRWXO);
    char* cont_start = start_of_size + 8;
    ssize_t real_size_file_rn = byte_read - (cont_start - temp_buffer);
    ssize_t write_byte = real_size_file_rn;
    while (1) {
      if (write_byte <= 0) break;
      if (write_byte <= 1024) {
        lseek(fd_bendi, 0, SEEK_END);
        write(fd_bendi, cont_start, write_byte);
        write_byte = 0;
      } else {
        lseek(fd_bendi, 0, SEEK_END);
        write(fd_bendi, cont_start, 1024);
        cont_start += 1024;
        write_byte -= 1024;
      }
    }
    if (isfull) {
      while (1) {
        char loc_buff[4096 * 100];
        int temp_read_in = read(event ->data.fd, loc_buff, 4096 * 100);
        if (temp_read_in > 0) {
          lseek(fd_bendi, 0, SEEK_END);
          write(fd_bendi, loc_buff, temp_read_in);
          real_size_file_rn += temp_read_in;
        } else if (temp_read_in == 0) {
          break;
        }
      }
    }
    if ((size_t)real_size_file_rn > size_of_file_uploaded) {
      print_received_too_much_data();
      dprintf(event ->data.fd,"ERROR\n%s\n",err_bad_file_size);
    } else if ((size_t)real_size_file_rn < size_of_file_uploaded) {
      print_too_little_data();
      dprintf(event ->data.fd,"ERROR\n%s\n",err_bad_file_size);
    } else {
      dprintf(event ->data.fd,"OK\n");
    }
    vector_push_back(file_vector, name_of_file);
    num_byte_file += strlen(name_of_file);
    close(fd_bendi);
    close(event ->data.fd);
  } else if (ifoption == 3) {
    unsigned char size_array[8];
    change_size(size_array, num_byte_file + vector_size(file_vector) - 1);
    dprintf(event->data.fd, "OK\n");
    write(event->data.fd, size_array, 8);
    for (size_t i = 0; i < vector_size(file_vector); i++) {
      char* this_str = vector_get(file_vector, i);
      if (i != vector_size(file_vector) - 1) {
        char temp_word = '\n';
        write(event->data.fd, &temp_word, 1);
        write(event->data.fd, this_str, strlen(this_str));
      } else {
        write(event->data.fd, this_str, strlen(this_str));
      }
    }
    close(event->data.fd);
  }else if (ifoption == 4) {
    char* blank = strstr(temp_buffer, " ");
    char* new_line_char = strstr(temp_buffer, "\n");
    char name_of_file[1024];
    memset(name_of_file, 0, 1024);
    *new_line_char = 0;
    strcpy(name_of_file, blank + 1);
    *new_line_char = '\n';
    size_t i;
    size_t successful = 0;
    for (i = 0; i < vector_size(file_vector); i++) {
      char* this_str = vector_get(file_vector, i);
      if (strcmp(this_str, name_of_file) == 0) {
        vector_erase(file_vector, i);
        num_byte_file -= strlen(name_of_file);
        char file_d[1024];
        memset(file_d, 0, 1024);
        strcat(file_d, "./");
        strcat(file_d, name_of_file);
        int rm = unlink(file_d);
        if (rm < 0) fprintf(stderr, "rm failed\n");
        successful = 1;
        break;
      }
    }
    if (!successful) {
      dprintf(event ->data.fd, "ERROR\n%s\n", err_no_such_file);
    } else {
      dprintf(event ->data.fd, "OK\n");
    }
    close(event ->data.fd);
  }

}



//help function of my own
int create_connection(const char* host, const char* port_idx){
    int s;
    int sock_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);

    struct addrinfo hints;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET; /* IPv4 only */
    hints.ai_socktype = SOCK_STREAM; /* TCP */
    hints.ai_flags = AI_PASSIVE;

    s = getaddrinfo(host, port_idx, &hints, &result);
    if (s != 0) {
          fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
          exit(1);
    }

    int optval = 1;
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval));

    if (bind(sock_fd, result->ai_addr, result->ai_addrlen) != 0) {
       perror("bind()");
       exit(1);
    }

    if (listen(sock_fd, 10) != 0) {
       perror("listen()");
       exit(1);
    }

    return sock_fd;
}

int main(int argc, char **argv) {
// good luck!
    if(argc!=2) exit(1);
//port_idx
    port_idx = argv[1];
//sigaction
    struct sigaction siga_c;
    siga_c.sa_handler = t_handler;
    sigaction(SIGINT, &siga_c, NULL);
//create a vector
    file_vector = string_vector_create();
//create socket connection
    int sock_fd = create_connection(NULL, port_idx);

    struct sockaddr_in address_in;
    socklen_t sock_lenth = sizeof(address_in);
    if(getsockname(sock_fd, (struct sockaddr *)&address_in, &sock_lenth) == -1){
        perror("getsockname");
    }else{
        printf("Listening on port number %d\n", ntohs(address_in.sin_port));
    }

    int epoll_fd = epoll_create(1);
  	if(epoll_fd == -1){
          perror("epoll_create()");
          exit(1);
    }

    struct epoll_event event_e;
  	event_e.data.fd = sock_fd;
  	event_e.events = EPOLLIN | EPOLLET;

//Add to the epoll
  	if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, sock_fd, &event_e))
  	{
          perror("epoll_ctl()");
          exit(1);
  	}

    int istrue = 1;
    while(istrue){
        struct epoll_event new_event_e;
        int a = 1;
        int b = -1;
        if(epoll_wait(epoll_fd, &new_event_e, a, b) > 0){
          if(sock_fd == new_event_e.data.fd)
            happy_end_accept_info(&new_event_e, epoll_fd);
          else
            happy_end_data(&new_event_e);
        }
    }
    return 0;
}

