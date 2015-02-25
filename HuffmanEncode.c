#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <libpnm.h>

struct node
{
    int first_value;
    int second_value;
};

long int *generate_pixel_frequency(struct PGM_Image *input_pgm_image, int *number_of_non_zero_values_in_the_frequency_array)
{
    //long int *frequencyArray = malloc((input_pgm_image->maxGrayValue+1) * sizeof(frequencyArray));
    int i;
    int width;
    int height;
    int greyValue;
    long int *frequencyArray = malloc((input_pgm_image->maxGrayValue + 1) * sizeof(long int));


    //initalize all entries to 0
    for (i=0; i<input_pgm_image->maxGrayValue + 1; i++)
    {
        frequencyArray[i] = 0;
    }

    for(width=0; width<input_pgm_image->width; width++)
    {
        for(height=0; height<input_pgm_image->height; height++)
        {
            greyValue = input_pgm_image->image[height][width];
            frequencyArray[greyValue] = frequencyArray[greyValue] + 1;
        }
    }

    for (i=0; i<input_pgm_image->maxGrayValue + 1; i++)
    {
        greyValue = frequencyArray[i];

        if (greyValue != 0)
        {
            (*number_of_non_zero_values_in_the_frequency_array)++;
        }
    }


    return frequencyArray;

}

struct node *generate_Huffman_nodes(long int *pixel_frequency, int max_gray_value, int number_of_non_zero_values_in_the_frequency_array)
{
    //go through frequency array. Find two smallest, largest of the smallest goes in first value, the other second value. Assign the larger entry in frequency array as 0, store combined value in  seconds place
    int first;
    int second;
    int temp;



    int j;
    int i;
    struct node *nodes = malloc((number_of_non_zero_values_in_the_frequency_array-1) * sizeof(nodes));



    for(i=0; i<number_of_non_zero_values_in_the_frequency_array-1; i++)
    {

        second = -1;
        first = -1;
        //find second
        for(j=0; j<max_gray_value+1; j++)
        {
            if(pixel_frequency[j])
            {
                if(second == -1)
                {
                    second = j;
                }
                else
                {
                    if(pixel_frequency[j] < pixel_frequency[second])
                    {
                        second = j;
                    }
                }
            }
        }

        for(j=0; j<max_gray_value+1; j++)
        {
            if(pixel_frequency[j] && j!=second)
            {
                if(first == -1)
                {
                    first = j;
                }
                else if(j!=second)
                {
                    if(pixel_frequency[j] <=pixel_frequency[first])
                    {
                        first = j;
                    }
                }
            }

        }
        //printf("%lu %lu\n", pixel_frequency[first],pixel_frequency[second]);

        //printf("%lu %lu %d %d\n", pixel_frequency[first], pixel_frequency[second],first, second);

        pixel_frequency[first] = pixel_frequency[second] + pixel_frequency[first];
        pixel_frequency[second] = 0;



        //printf("%d %d\n", first, second);
        //printf("%d\n", second);

        nodes[i].first_value = first;
        nodes[i].second_value = second;

    }





    return nodes;
}





unsigned char *Huffman_encode(struct PGM_Image *input_pgm_image, struct node *Huffman_node, int number_of_nodes, unsigned long int *length_of_encoded_array)
{
    unsigned long int index;
    int val;
    int i;
    int j;
    int width;
    int height;
    *length_of_encoded_array = input_pgm_image->height * input_pgm_image->width;
    unsigned char *encodedImage = malloc(*length_of_encoded_array * sizeof(unsigned char));
    unsigned char *huffmanArray = malloc((input_pgm_image->maxGrayValue + 1) * sizeof(unsigned char));

    for(i=0; i<input_pgm_image->maxGrayValue+1; i++)
    {
        huffmanArray[i] = -1;
    }

    for(i=number_of_nodes-1; i>=0; i--)
    {
        if(huffmanArray[Huffman_node[i].first_value] == -1)
        {
            huffmanArray[Huffman_node[i].first_value] = 0;
        }
        else
        {
            huffmanArray[Huffman_node[i].second_value] = (huffmanArray[Huffman_node[i].first_value] << 1) + 1;
            huffmanArray[Huffman_node[i].first_value] = huffmanArray[Huffman_node[i].first_value] << 1;
        }

        if(huffmanArray[Huffman_node[i].second_value] == -1)
        {
            huffmanArray[Huffman_node[i].second_value] = (huffmanArray[Huffman_node[i].first_value] << 1) + 1;
        }else
        {
            (huffmanArray[Huffman_node[i].second_value] << 1) + 1;
        }



    }

//    for(j=0; j<input_pgm_image->maxGrayValue+1; j++)
//        {
//            if(huffmanArray[j] != -1)
//            {
//                printf("%d %d\n", huffmanArray[j], j);
//            }
//        }



    index = 0;
    for(width=0; width<input_pgm_image->width; width++)
    {
        for(height=0; height<input_pgm_image->height; height++)
        {
            val = input_pgm_image->image[height][width];
            encodedImage[index] = huffmanArray[val];
            index++;
        }
    }

    return encodedImage;
}

void store_Huffman_encoded_data(unsigned char *compressed_file_name_ptr, int image_width, int image_height,
                                int max_gray_value, int number_of_nodes, struct node *Huffman_node, long int length_of_encoded_image, unsigned char *encoded_image)
{
    long int index;
    int i;
    FILE *f = fopen(compressed_file_name_ptr, "w");
    if(f == NULL){
        printf("Error printing file\n");
        exit(1);
    }

//    fprintf(f,"%d\n", image_width);
//    fprintf(f,"%d\n", image_height);
//    fprintf(f,"%d\n", max_gray_value);
//    fprintf(f,"%d\n", number_of_nodes);
//    fprintf(f,"%lu\n", length_of_encoded_image);
//    for(i=0;i<number_of_nodes; i++){
//        fprintf(f,"%d %d\n", Huffman_node[i].first_value, Huffman_node[i].second_value);
//    }
    fprintf(f,"%s\n", encoded_image);
    fclose(f);



}

int main(int argc, char *argv[])
{
    unsigned long int i;
    unsigned long int lengthOfEncodedArray;
    long int *frequencyArray;
    unsigned char *imageInputName;
    unsigned char *encodedImage;
    unsigned char *imageOutputName;

    struct PGM_Image pgmImage;

    int number_of_non_zero_values_in_the_frequency_array = 0;






    if(argc!=3)
    {
        perror("Invalid command line inputs");
        exit(1);
    }

    imageInputName = strdup(argv[1]);
    imageOutputName = strdup(argv[2]);

    load_PGM_Image(&pgmImage, imageInputName);
    frequencyArray = generate_pixel_frequency(&pgmImage, &number_of_non_zero_values_in_the_frequency_array);



    struct node *nodes = generate_Huffman_nodes(frequencyArray, pgmImage.maxGrayValue, number_of_non_zero_values_in_the_frequency_array);

    encodedImage = Huffman_encode(&pgmImage, nodes, number_of_non_zero_values_in_the_frequency_array-1, &lengthOfEncodedArray);
    store_Huffman_encoded_data(imageOutputName, pgmImage.width,pgmImage.height, pgmImage.maxGrayValue, number_of_non_zero_values_in_the_frequency_array-1, nodes, lengthOfEncodedArray, encodedImage);


    free(encodedImage);
    free(imageOutputName);
    free(imageInputName);
    free(frequencyArray);
    return 0;


}

