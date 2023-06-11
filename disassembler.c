#include <stdio.h>
#include <stdlib.h>
#include "Dissassemble8080op.h"

/* 
fread(ptr, size, nmemb, stream)
    READS the data from the file to the memory at the pointer
    1. ptr: Pointer to the memory which will store the data read
    2. size: Size or the amount of data in bytes to read
    3. nmemb: Number of chunks of size to read
    4. stream: file pointer from where to read
    RETURNS: the number of items of size read.
fseek(file_ptr, offset, position)
    moves the file pointer to the specific location
    1. ptr: File Pointer to a file
    2. offset: (long int) Number of bytes to offset from the position
    3. position:  (int) From where to apply the offset
    RETURNS: 0 if successful else non-zero
ftell(file_ptr)
    Tells the current position of the file pointer
    RETURNS: position of file pointer else -1 if an error occurs
*/

int main(int argc, char **argv)
{
    FILE *hex_file = fopen(argv[1], "rb");
    if (hex_file == NULL)
    {
        printf("Error: Could Not Open %s\n", argv[1]);
        return 1;
    }
    
    // Sets the file pointer position to the end of the file 
    // offset amount is zero, moves file pointer to the EOF
    fseek(hex_file, 0L, SEEK_END);
    // returns the current position of the file
    int file_size = ftell(hex_file);
    // Sets the file pointer back to the beginning of the file
    fseek(hex_file, 0L, SEEK_SET);

    // allocates memory equal to the size of the file
    unsigned char *buffer = malloc(file_size);

    // It reads the whole file into memory
    fread(buffer, file_size, 1, hex_file);
    fclose(hex_file);

    /* 
    pc: program counter or the current offset from the start of the file.
    Basically tells us how far into the file we have come.
    */
    int pc = 0;

    // Since pc starts at zero
    while (pc < file_size)
    {
        // Disassemble8080op returns the amount to offset pc by 
        pc += Disassemble8080op(buffer, pc);
    }
    free(buffer);
    return 0;
}