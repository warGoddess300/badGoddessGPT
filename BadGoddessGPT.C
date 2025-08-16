/*Programming badGoddessGPT
*incomplete bot, i wanna see if i can program an AI
*i'm too beginner
*
*
*/


#include <stdio.h> //adding standard input output header file
#include <string.h> //adding string header file
#include <stdbool.h> //adding boolean header file

#define FILENAME "password.txt"  //defining a macro for filename
#define FILENAME2 "username.txt" 
#define FILENAME3 "commands.txt" 

int main() {

char username[50]; //declaring a type char variable to store username value
char user_password[50]; //declaring a type char variable to store password value
char user_input[50]; //declaring a type char variable to store user input value

FILE *user_n = fopen(FILENAME, "r");
if (user_n == NULL) {
    // File does not exist, ask for username and save it
    printf("No username found. Please set your username: ");
    fgets(username, 50, stdin);
    username[strcspn(username, "\n")] = 0;
    user_n = fopen(FILENAME, "w");
    if (user_n == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }
    fprintf(user_n, "%s\n", username);
    printf("username saved successfully.\n");
    fclose(user_n);
} else {
    // File exists, load username
    fgets(username, 50, user_n);
    username[strcspn(username, "\n")] = 0;
    printf("username loaded from file.\n");
    fclose(user_n);
}
FILE *user_p = fopen(FILENAME, "r");
if (user_p == NULL) {
    // File does not exist, ask for password and save it
    printf("No password found. Please set your password: ");
    fgets(user_password, 50, stdin);
    user_password[strcspn(user_password, "\n")] = 0;
    user_p = fopen(FILENAME, "w");
    if (user_p == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }
    fprintf(user_p, "%s\n", user_password);
    printf("Password saved successfully.\n");
    fclose(user_p);
} else {
    // File exists, load password
    fgets(user_password, 50, user_p);
    user_password[strcspn(user_password, "\n")] = 0;
    printf("Password loaded from file.\n");
    fclose(user_p);
}


while(true) {
printf("Enter a command: ");
fgets(user_input, 50, stdin);
user_input[strcspn(user_input, "\n")] = 0; // Remove newline character
if(strcmp(user_input, "quit") == 0) {
    printf("Program is terminating.\n");
    break;           
}
else if(strcmp(user_input, "add command") == 0) {
        char new_command[50];
        printf("Learning new command, add a new command: ");
        fgets(new_command, 50, stdin);
        new_command[strcspn(new_command, "\n")] = 0;
        FILE *user_commands = fopen(FILENAME3, "a");
        if (user_commands == NULL) {
            printf("Error opening file for writing.\n");
            continue;
        }
        fprintf(user_commands, "%s\n", new_command);
        printf("Command added successfully.\n");
        fclose(user_commands);
    }
    else if(strcmp(user_input, "delete command") == 0) {
        char del_command[50];
        printf("Enter the command you want to delete: ");
        fgets(del_command, 50, stdin);
        del_command[strcspn(del_command, "\n")] = 0;

        FILE *user_commands = fopen(FILENAME3, "r");
        if (user_commands == NULL) {
            printf("Error opening file for reading.\n");
            continue;
        }
        char commands[100][50];
        int count = 0;
        while (fgets(commands[count], 50, user_commands)) {
            commands[count][strcspn(commands[count], "\n")] = 0;
            count++;
        }
        fclose(user_commands);

        user_commands = fopen(FILENAME3, "w");
        if (user_commands == NULL) {
            printf("Error opening file for writing.\n");
            continue;
        }
        int deleted = 0;
        for (int i = 0; i < count; i++) {
            if (strcmp(commands[i], del_command) != 0) {
                fprintf(user_commands, "%s\n", commands[i]);
            } else {
                deleted = 1;
            }
        }
        fclose(user_commands);
        if (deleted)
            printf("Command deleted successfully.\n");
        else
            printf("Command not found.\n");
    }



}
return 0;
} // End of main function