# TECHNICAL DOCUMENTATION

## 1.Understanding main.c

### 1.1 The main function :
#### 1.1.1. 'The main(int argc , char** argv , char** env)': 
    - We did put the int argc and char**argv even we dont need them because the main() have two forms to be written
      main(void) and main(int argc , char** argv). The Third parametre env The third parameter is a common Unix/Linux convention, 
      but it isn't guaranteed by ISO C
    - We can write also char *argv[] and char *env[] these just another syntax or way to type argc argv

#### 1.1.2. '(void)argc; (void)argv;':
    - Telling the Compiler that we dont need those 2 arguments Because compilers can generate warnings when function parameters are 
      declared but never used.

#### 1.1.3. 'run_shell(env)' : The main purpose of this function is to keep your shell running and waiting for commands.


### 1.2 The run_shell function :
#### 1.2.1. 'char* input = NULL;': 
    - Means that input will point to a sequence of characters representing the command entered by the user.
    - So for who don't know the difference between "char" and "char*" , char input; creates a variable that stores just one character.
      but char* input; allows you to work with an entire string.
      A shell needs to receive commands containing multiple characters, so a pointer to characters is appropriate.
    - NULL means that the pointer currently points to no valid object.

#### 1.2.2. 'size_t input_size = 0;':
    - "size_t" is a data type in C used to represent the size or number of objects in memory.
    - It is similare to write "int input_size;" But there is an important difference: 
      "int" can represent positive and negative integers and "size_t" represents non-negative integer values (0 and above).
    - "input_size" represents the allocated capacity, not necessarily the number of characters actually read.

#### 1.2.3. 'char** args;':
    - This is another pointer, but this time it points to pointers to characters.
    - For beginners PLZ Remeber : (char = one character) , (char* = a pointer to characters (commonly a string))
      and (char** = a pointer to pointers to characters (commonly an array of strings))
    - The shell need this Because commands contain multiple parts.
    - Important: args is not initialized in the code you provided. We'll come back to why that matters when discussing memory management.

#### 1.2.4. 'char* initial_directory = getcwd(NULL, 0);':
    - "getcwd()" means Get Current Working Directory , It is a POSIX function , not a standard C function that obtains the absolute path 
       of the directory in which your program is currently running.
    - Some people dont get what is POSIX so Quickly POSIX is It is a family of standards that defines interfaces allowing programs to 
      interact with operating-system services in a portable way.
      For example, POSIX provides functions for:
        Working with files and directories.
        Creating and managing processes.
        Interacting with the operating system.
        Managing permissions.
        Handling input and output.
    - (getcwd(NULL, 0);) It asks the implementation to allocate enough memory for the path automatically.The returned pointer refers to 
       that allocated memory.
    - We need "initial_directory" because This can be useful when implementing commands such as cd, particularly if I wants to support 
      returning to the original directory.
    
#### 1.2.5. 'while (1)'/INstruction':
    - This is an infinite loop , Because 1 is always true . A shell needs this because it must continuously wait for commands.

#### 1.2.6. 'printf("[Kinex-Shell]>> ");':
    - This displays the KINEX shell's prompt , The user sees this and knows that the shell is ready to receive a command.

#### 1.2.7. 'if (getline(&input, &input_size, stdin) == -1)':
    - getline() is a function used in C to read an entire line of text from an input stream and store it in a dynamically allocated 
       buffer. It is useful when building our Kinex Shell because you don't know in advance how long the command entered by the user will be. getline() is a POSIX function, not a standard ISO C function. It is declared in <stdio.h> on systems that support it
    - getline() takes 3 Arguments , getline(Argument 1,Argument 2,Argument 3) lets understand each argument :
        - Argument 1 : It's Type is "char **" and the Purposr is an Address of a pointer to the buffer.
          so Why do we pass "&input" instead of "input"?  "input" is a pointer to a character , "&input" is the address of that pointer.
          getline() needs the address because it may need to modify the pointer itself
          SO [ for "char *input = NULL;" There is no allocated buffer yet , When you call: "getline(&input, &input_size, stdin);" getline() can allocate memory and update input to point to that memory.
          for more clarification {Before calling "getline()" "input = NULL"} {After calling "getline()" "input" points to allocated memory} {Allocated buffer : HI\n\0}]
        - Argument 2 : It's Type is "size_t *" and the Purposr is Address of a variable containing the buffer capacity.
          Why &input_size? , Because getline() needs to know the current capacity of the buffer and may update that capacity when it allocates or resizes the buffer.
        - Argument 3 : It's Type is "FILE *" and the purpose is telling getline() where to read the data from.
          Here, stdin means standard input, usually the keyboard.
    - getline() returns the number of characters read , Notice that the return type is ssize_t, not size_t.
      What happens if something goes wrong? getline() returns -1 if it encounters EOF before reading any characters or if an error occurs or Ctrl+D sends an end-of-file indication to the terminal's input stream when used at an empty prompt.
      It tells the shell that no more input is available.
      That's why its return type is ssize_t: unlike size_t, it can represent negative values.
      BTW "EOF" means end-of-file

#### 1.2.8. 'perror("getline"); ':
    - perror() is a standard C library function , Its job is to display an error message based on the current value of errno
      The string "getline" is simply a label added before the error description.

#### 1.2.9. ' args = split_commands(input); ':
    - split_commands() is a seprate function that I will write later , in another file 
      To know what she does , imagine the user type "ls -l /home\n" the shell needs to identify the individual parts
      args[0] = "ls" , args[1] = "-l" , args[2] = "/home" , args[3] = NULL
      It takes one string and creates an array of strings. This is called tokenization.
      That's what split_commands() does with more things than that.
      WE gonna define it like this (char** split_commands(char* input)) so the results is a char** to be as the type of args and the input is a char* as the type of "input"
-----------------------------------------------------------------------------------------------------------------------------------------


## 2.Understanding command_parser.c

For this implementation, spaces, tabs, and certain other whitespace characters separate tokens.
One limitation: this is a simple tokenizer, not a complete shell parser. It doesn't understand quotation marks, escaped spaces, pipes, or redirections yet.
### 2.1 The split_commands function : 
#### 2.1.1. 'size_t buffer_size = MAX_INPUT_SIZE;':
    - We need buffer size Because the shell needs to allocate memory for the array that will contain the tokens.