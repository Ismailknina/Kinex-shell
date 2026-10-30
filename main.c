#include "shell_config.h"

void run_shell(char** env){

    char* input = NULL;
    size_t input_size = 0;
    
    char** args;
    
    char* initial_directory = getcwd(NULL,0);

    while (1)
    {
        printf("[Kiniex-Shell]>> "); // The user sees this and knows that the shell is ready to receive a command.

        if (getline(&input , &input_size , stdin) == -1) // EOF , Error , Ctrl+D
        {
            perror("getline");
            break;
        }
        //printf("Input %s" , input);

        args = split_commands(input);
        
    }

}


int main(int argc , char** argv , char** env){ 

    (void)argc; 
    (void)argv;

    run_shell(env); // Keep the shell running and waiting for commands.

    return 0;
}