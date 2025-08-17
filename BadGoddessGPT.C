/*Programming BadGoddessGPT
*incomplete bot, i wanna see if i can program an AI
*i'm too beginner
*if you enter learn, it will learn
*
*warGoddess300
*
*assembly language is king
*
*/


#include <stdio.h> //adding standard input output header file
#include <string.h> //adding string header file
#include <stdbool.h> //adding boolean header file
#include <openssl/sha.h> //adding openssl header file for sha256 hashing

/*to connect this program to the internet, i will have to include these header files (sockets)
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
*/

#define FILENAME "password.txt"  //defining a macro for password.txt file
#define FILENAME2 "username.txt" //defining a macro for username.txt file
#define FILENAME3 "commands.txt" //defining a macro for commands.txt file
#define FILENAME_h "hostname.txt" //defining a macro for hostname file
#define FILENAME_Knowledge "knowledge.txt" //defining a macro for knowledge.txt file

// Ajoute cette fonction dans ton fichier
void sha256_string(const char *str, char *outputBuffer) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)str, strlen(str), hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    outputBuffer[64] = 0;
}

int main() {

char username[50]; //declaring a type char variable to store username value
char user_password[50]; //declaring a type char variable to store password value
char user_input[50]; //declaring a type char variable to store user input value
char hostname[50]; //declaring a type char variable to store hostname from user input


//setting username if no username found in file

FILE *user_n = fopen(FILENAME2, "r");
if (user_n == NULL) {
    // File does not exist, ask for username and save it
    printf("No username found. Please set your username: ");
    fgets(username, 50, stdin);
    username[strcspn(username, "\n")] = 0;
    user_n = fopen(FILENAME2, "w");
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

//setting hostname if no hostname found in file

FILE *user_h = fopen(FILENAME_h, "r");
if (user_h == NULL) {
    // File does not exist, ask for username and save it
    printf("No hostname found. Please set your hostname: ");
    fgets(hostname, 50, stdin);
    hostname[strcspn(hostname, "\n")] = 0;
    user_h = fopen(FILENAME_h, "w");
    if (user_h == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }
    fprintf(user_h, "%s\n", hostname);
    printf("hostname saved successfully.\n");
    fclose(user_h);
} else {
    // File exists, load hostname
    fgets(hostname, 50, user_h);
    hostname[strcspn(hostname, "\n")] = 0;
    printf("hostname loaded from file.\n");
    fclose(user_h);
}

//setting password if no password found in file

FILE *user_p = fopen(FILENAME, "r");
if (user_p == NULL) {
    // File does not exist, ask for password and save it
    printf("No password found. Please set your password: ");
    fgets(user_password, 50, stdin);
    user_password[strcspn(user_password, "\n")] = 0;
    char hashed_password[65];
    sha256_string(user_password, hashed_password);
    user_p = fopen(FILENAME, "w");
    if (user_p == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }
    fprintf(user_p, "%s\n", hashed_password);
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
printf("(not a linux shell) %s@%s$ ", username, hostname);
fgets(user_input, 50, stdin);
user_input[strcspn(user_input, "\n")] = 0; // Remove newline character

if(strcmp(user_input, "quit") == 0) {
    printf("Program is terminating.\n");
    break;           
}
else if(strcmp(user_input, "add password") == 0) {
    printf("Enter new password: ");
    fgets(user_password, 50, stdin);
    user_password[strcspn(user_password, "\n")] = 0;
    char hashed_password[65];
    sha256_string(user_password, hashed_password);
    FILE *user_p = fopen(FILENAME, "w");
    if (user_p == NULL) {
        printf("Error opening password file for writing.\n");
    } else {
        fprintf(user_p, "%s\n", hashed_password);
        printf("New password saved successfully.\n");
        fclose(user_p);
    }
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
        else if(strcmp(user_input, "learn") == 0) {
        char question[100], answer[200];
        printf("Enter the question: ");
        fgets(question, 100, stdin);
        question[strcspn(question, "\n")] = 0;
        printf("Enter the answer: ");
        fgets(answer, 200, stdin);
        answer[strcspn(answer, "\n")] = 0;

        FILE *knowledge = fopen(FILENAME_Knowledge, "a");
        if (knowledge == NULL) {
            printf("Error opening knowledge file.\n");
            continue;
        }
        fprintf(knowledge, "%s|%s\n", question, answer); // format: question|answer
        fclose(knowledge);
        printf("Learned: \"%s\" → \"%s\"\n", question, answer);
    }
    else {
        // Try to find an answer in knowledge.txt
        FILE *knowledge = fopen(FILENAME_Knowledge, "r");
        if (knowledge != NULL) {
            char line[2000];
            int found = 0;
            while (fgets(line, sizeof(line), knowledge)) {
                char *sep = strchr(line, '|');
                if (sep) {
                    *sep = 0; // split question/answer
                    char *question = line;
                    char *answer = sep + 1;
                    answer[strcspn(answer, "\n")] = 0;
                    if (strcmp(user_input, question) == 0) {
                        printf("BadGoddessGPT: %s\n", answer);
                        found = 1;
                        break;
                    }
                }
            }
            fclose(knowledge);
            if (!found) {
                printf("I don't know the answer yet.\n");
            }
        } else {
            printf("No knowledge file found.\n");
        }
    }



}
return 0;
} // End of main function
