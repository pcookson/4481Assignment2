#include <stdio.h>
#include <stdlib.h>
#include <libpnm.h>

float mean_absolute_error(unsigned char *file_name_1_ptr, unsigned char *file_name_2_ptr)
{

}


int main(int argc, char *argv[])
{

    unsigned char *imageInputName;
    unsigned char *imageOutputName;
    if(argc!=3)
    {
        perror("Invalid command line inputs");
        exit(1);
    }

    imageInputName = strdup(argv[2]);
    imageOutputName = strdup(argv[3]);

    mean_absolute_error(imageInputName, imageOutputName);
}
