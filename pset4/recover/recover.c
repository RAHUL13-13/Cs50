#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>
#include<cs50.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    int file_number = 0;                                               //first file name(number)

    if (argc != 2)
    {
        return 1;
    }

    char *input_file =  argv[1];

    FILE *inputed_file_pointer = fopen(input_file, "r");               //file containg jpeg (sd card file.)

    FILE *outputed_file_pointer = NULL;                                //file inside which jpeg will be put.

    BYTE arr_ofBYTES[512];
    char filewrite[8];

    //checking if there is initialisation of jpeg.
    while (true)
    {
        size_t BYTESsize_read = fread(arr_ofBYTES, sizeof(BYTE), 512, inputed_file_pointer);
        if (BYTESsize_read == 0)
        {
            break;
        }

        if ((arr_ofBYTES[0] == 0xff && arr_ofBYTES[1] == 0xd8 && arr_ofBYTES[2] == 0xff && ((arr_ofBYTES[3] & 0xf0) == 0xe0)) 
            && outputed_file_pointer != NULL)
        {
            fclose(outputed_file_pointer);
            file_number++;
        }

        // if we found a JPEG, we need to open the file for writing
        if ((arr_ofBYTES[0] == 0xff && arr_ofBYTES[1] == 0xd8 && arr_ofBYTES[2] == 0xff && ((arr_ofBYTES[3] & 0xf0) == 0xe0)))
        {
            sprintf(filewrite, "%03i.jpg", file_number);
            outputed_file_pointer = fopen(filewrite, "w");
        }

        // write anytime we have an open file
        if (outputed_file_pointer != NULL)
        {
            fwrite(arr_ofBYTES, sizeof(BYTE), BYTESsize_read, outputed_file_pointer);
        }

    }
    fclose(inputed_file_pointer);
    fclose(outputed_file_pointer);
    return 0;
}