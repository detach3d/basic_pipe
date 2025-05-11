#include <iostream>
#include <unistd.h>
#include <cstring>

std::size_t message_size;

int main(){
	int pipe_array[2]{};
	char buffer[5];
	if(pipe(pipe_array) == -1){
		exit(EXIT_FAILURE);
	}

	if(int pid = fork(); pid == -1){
		perror("Process creation failed");
		exit(EXIT_FAILURE);
	}else if(pid == 0){
		sleep(1);
		close(pipe_array[1]);
			
		read(pipe_array[0], buffer, 5);
		int buff_size= atoi(buffer);
		std::cout << "Message size in Child: " << buff_size << '\n';

		char buffer_message[buff_size+1]{};
		read(pipe_array[0], buffer_message, buff_size);
		buffer_message[buff_size] ='\0';
		std::cout << "Buffer message: " << buffer_message << " " << '\n';

	}else{
		close(pipe_array[0]);
		const char* message = "Hello from parent\0";

		message_size = strlen(message);
		std::string s = std::to_string(message_size);
		char const *pchar = s.c_str();

		std::cout << "Message size in Parent: "<< message_size << '\n';

		write(pipe_array[1], pchar, 5);
		write(pipe_array[1], message, message_size+1);
		
	}
}
