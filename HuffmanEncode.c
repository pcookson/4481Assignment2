#include <stdio.h>
#include <stdlib.h>
#include <libpnm.h>

long int *generate_pixel_frequency(struct PGM_Image *input_pgm_image, int *number_of_non_zero_values_in_the_frequency_array)
{

}

struct node *generate_Huffman_nodes(long int *pixel_frequency, int max_gray_value, int number_of_non_zero_values_in_the_frequency_array)
{

}


unsigned char *Huffman_encode(struct PGM_Image *input_pgm_image, struct node *Huffman_node, int number_of_nodes, unsigned long int *length_of_encoded_array)
{

}

void store_Huffman_encoded_data(unsigned char *compressed_file_name_ptr, int image_width, int image_height,
                                int max_gray_value, int number_of_nodes, struct node *Huffman_node, long int length_of_encoded_image, unsigned char *encoded_image)
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

