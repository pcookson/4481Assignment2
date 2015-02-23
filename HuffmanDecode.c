#include <stdio.h>
#include <stdlib.h>
#include <libpnm.h>

unsigned char *read_Huffman_encoded_data(unsigned char *compressed_file_name_ptr, int *image_width, int *image_height, int *max_gray_value, int *number_of_nodes, struct node **Huffman_node, long int *length_of_encoded_image)
{

}

struct PGM_Image *Huffman_decode_image( int image_width, int image_height, int max_gray_value, int number_of_nodes, struct node *Huffman_node, long int length_of_encoded_image, unsigned char *encoded_image)
{

}

int main(int argc, char *argv[])
{

    unsigned char *imageInputName;
    unsigned char *imageOutputName;
    unsigned char * encodedImage;
    struct PGM_Image pgmImage;

    if(argc!=3)
    {
        perror("Invalid command line inputs");
        exit(1);
    }

    imageInputName = strdup(argv[2]);
    imageOutputName = strdup(argv[3]);



}
