# include "shell_config.h"

int command_cd(char** args , char* initial_path)
{
    (void)initial_path; // Suppress unused parameter warning

    if(args[1] == NULL) printf("expected path after cd\n");

    else if(chdir(args[1])==0) printf("The directory has been changed to %s\n", args[1]);

    else perror("cd");

    return 0;
}


int command_pwd()
{
    char* cwd = NULL;

    cwd = getcwd(NULL,0);

    if(cwd != NULL) {printf("%s \n",cwd); free(cwd);}

    else perror("getcwd");

    return 0;
}

int command_echo(char** args , char** env)
{
    int new_line = 1;

    size_t i = 1;

    if(args[1] != NULL && strcmp(args[1], "-n")==0)
    {
        new_line = 0;
        i++;
    }
    for (; args[i] ; i++)
    {
        if(args[i][0] == '$')
        {
            char* env_var = getenv(args[i]+1);

            if(env_var) printf("%s", env_var);

            else printf("Not Found ");
        }
        else printf("%s", args[i]);

        if(args[i+1] != NULL) 
        {
            new_line = 0;
            printf(" ");
        }
        if(new_line) printf("\n");
        new_line = 1;
        
    }
    return 0;

}

int command_env(char** env)
{
    size_t i = 0;
    
    while(env[i] != NULL)
    {
        printf("%s\n" , env[i]);
        i++;
    }
    return 0;
}