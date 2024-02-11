#include <stdio.h>
#include <string.h>

// Function to encrypt a character using the Caesar cipher
char encryptChar(char ch, int key) {
    // Encrypt uppercase letters
    if (ch >= 'A' && ch <= 'Z')
        return ((ch - 'A' + key) % 26) + 'A';
    // Encrypt lowercase letters
    else if (ch >= 'a' && ch <= 'z')
        return ((ch - 'a' + key) % 26) + 'a';
    else
        return ch;  // Leave non-alphabetic characters unchanged
}

// Function to decrypt a character using the Caesar cipher
char decryptChar(char ch, int key) {
    // Decrypt uppercase letters
    if (ch >= 'A' && ch <= 'Z') {
        int decrypted = ch - 'A' - key;
        if (decrypted < 0)
            decrypted += 26; // Handle wrap-around
        return decrypted + 'A';
    }
    // Decrypt lowercase letters
    else if (ch >= 'a' && ch <= 'z') {
        int decrypted = ch - 'a' - key;
        if (decrypted < 0)
            decrypted += 26; // Handle wrap-around
        return decrypted + 'a';
    } else
        return ch;  // Leave non-alphabetic characters unchanged
}

// Function to handle input file name by adding ".txt" extension if not provided
int handleInputFileName(char *fileName) {
    int length = strlen(fileName);
    if (length < 4 || strcmp(&fileName[length - 4], ".txt") != 0) {
        strcat(fileName, ".txt");
        return length; // Return length of filename without extension
    }
    return length - 4; // Return length of filename without extension
}

// Function to encrypt the encryption key
int encryptKey(int key) {
    // Fixed encryption key for encrypting the encryption key
    int encryptionKey = 5;
    return (key + encryptionKey) % 26; // Use a simple Caesar cipher for encryption
}

// Function to decrypt the encryption key
int decryptKey(int encryptedKey) {
    // Fixed encryption key for encrypting the encryption key
    int encryptionKey = 5;
    return (encryptedKey - encryptionKey + 26) % 26; // Use a simple Caesar cipher for decryption
}

int main() {
    char inputFileName[100], outputFileName[100];
    int key, encryptedKey, choice;

    printf("Welcome to File Encryption/Decryption Tool\n");

    // Prompt the user to enter the input file name
    printf("Please enter the input file name: ");
    scanf("%s", inputFileName);
   
    // Handle input file name by adding ".txt" extension if not provided
    int fileNameLength = handleInputFileName(inputFileName);

    printf("Select operation:\n");
    printf("1. Encryption\n");
    printf("2. Decryption\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Use fileNameLength as the encryption/decryption key
    key = fileNameLength;
    
    // Determine output file name based on operation choice
    if (choice == 1) {
        strcpy(outputFileName, "encrypted.txt");
        // Encrypt the encryption key and store it
        encryptedKey = encryptKey(key);
    }
    else if (choice == 2)
        strcpy(outputFileName, "decrypted.txt");
    else {
        printf("Invalid choice.\n");
        return 1;
    }

    // Open the input file for reading
    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    // Open the output file for writing the encrypted/decrypted data
    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        printf("Error creating output file.\n");
        fclose(inputFile);
        return 1;
    }

    // Write the encrypted key to the output file if performing encryption
    if (choice == 1)
        fprintf(outputFile, "%d", encryptedKey);

    // Perform decryption if the choice is 2
    if (choice == 2) {
        // Read the encrypted key from the input file
        fscanf(inputFile, "%d", &encryptedKey);
        // Decrypt the encryption key
        key = decryptKey(encryptedKey);
    }

    // Perform encryption or decryption based on user choice
    char ch;
    while ((ch = fgetc(inputFile)) != EOF) {
        char processedChar;
        if (choice == 1)
            processedChar = encryptChar(ch, key);
        else if (choice == 2)
            processedChar = decryptChar(ch, key);
        else {
            printf("Invalid choice.\n");
            fclose(inputFile);
            fclose(outputFile);
            return 1;
        }
        fputc(processedChar, outputFile);
    }

    // Close input and output files
    fclose(inputFile);
    fclose(outputFile);

    if (choice == 1)
        printf("File encrypted successfully.\nPlease check 'encrypted.txt'.");
    else if (choice == 2)
        printf("File decrypted successfully.\nPlease check 'decrypted.txt'");

    printf("\n\t**Press a valid key to exit.\n");
    getch();
    return 0;
}
