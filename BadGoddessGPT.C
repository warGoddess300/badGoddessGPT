#include <stdio.h> // For printf, fopen, fgets, fclose, fprintf
#include <string.h> // For strcmp, strcpy, strlen, fgets, strcspn
#include <stdlib.h> // For malloc, free, realloc
#include <stdbool.h> //boolean header file, to check if a condition is true or false
#include <openssl/sha.h> //to encrypt passwords, used with SHA256() function
#include <ctype.h> // For tolower() function

#define FILENAME "password.txt" //FILENAME represents passord.txt
#define FILENAME2 "username.txt" //FILENAME2 represents username.txt
#define FILENAME3 "commands.txt" //FILENAME3 represents commands.txt
#define FILENAME_h "hostname.txt" // FILENAME_h represents hostname.txt
#define FILENAME_Knowledge "knowledge.txt" // FILENAME_Knowledge represents knowledge.txt

// function to encrypt password 
void sha256_string(const char *str, char *outputBuffer) { 
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256((unsigned char*)str, strlen(str), hash);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        sprintf(outputBuffer + (i * 2), "%02x", hash[i]);
    outputBuffer[64] = 0;
}

// function to convert a string to lowercase
// This function iterates through each character in the string and converts it to lowercase.
// It uses the tolower() function from the ctype.h library, which is designed to
// handle character case conversion in a locale-independent manner.
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

// Function to read a dynamic line from a file
char* read_dynamic_line(FILE* fp) {
    size_t buffer_size = 50;
    char* line = (char*)malloc(buffer_size);
    if (!line) return NULL;

    int c;
    size_t current_len = 0;

    while ((c = fgetc(fp)) != EOF && c != '\n') {
        if (current_len + 1 >= buffer_size) {
            buffer_size *= 2;
            char* new_line = (char*)realloc(line, buffer_size);
            if (!new_line) {
                free(line);
                return NULL;
            }
            line = new_line;
        }
        line[current_len++] = (char)c;
    }

    if (current_len > 0 || c == '\n') {
        line[current_len] = '\0';
        return line;
    } else {
        free(line);
        return NULL;
    }
}


int main() {

char username[50];
char user_password[50];
char user_input[50];
char hostname[50];


// Check if the files exist and read/write username, password, and hostname
FILE *user_n = fopen(FILENAME2, "r");
if (user_n == NULL) {
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
    fgets(username, 50, user_n);
    username[strcspn(username, "\n")] = 0;
    printf("username loaded from file.\n");
    fclose(user_n);
}

FILE *user_h = fopen(FILENAME_h, "r");
if (user_h == NULL) {
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
    fgets(hostname, 50, user_h);
    hostname[strcspn(hostname, "\n")] = 0;
    printf("hostname loaded from file.\n");
    fclose(user_h);
}

FILE *user_p = fopen(FILENAME, "r");
if (user_p == NULL) {
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
    fgets(user_password, 50, user_p);
    user_password[strcspn(user_password, "\n")] = 0;
    printf("Password loaded from file.\n");
    fclose(user_p);
}


while(true) {
    printf("(not a linux shell) %s@%s$ ", username, hostname);
    fgets(user_input, 50, stdin);
    user_input[strcspn(user_input, "\n")] = 0;

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
            char *line;
            int found = 0;

            // Convert user input to lowercase for case-insensitive comparison
            char user_input_lower[50];
            strcpy(user_input_lower, user_input);
            to_lowercase(user_input_lower);
            
            while ((line = read_dynamic_line(knowledge)) != NULL) {
                char *sep = strchr(line, '|');
                if (sep) {
                    *sep = 0; // split question/answer
                    char *question = line;
                    char *answer = sep + 1;

                    // Convert question to lowercase for case-insensitive comparison
                    char *question_lower = (char*)malloc(strlen(question) + 1);
                    if (question_lower) {
                        strcpy(question_lower, question);
                        to_lowercase(question_lower);

                        // 
                        if (strcmp(user_input_lower, question_lower) == 0) {
                            printf("BadGoddessGPT: %s\n", answer);
                            found = 1;
                        }
                        // free the memory allocated for question_lower
                        free(question_lower);
                    }
                    if (found) {
                        free(line);
                        break;
                    }
                }
                // free the memory allocated for line
                free(line);
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
}
