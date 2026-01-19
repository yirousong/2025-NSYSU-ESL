#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define WIDTH 256
#define HEIGHT 256
#define HEADER_SIZE 54

unsigned char header[HEADER_SIZE];
unsigned char rgb_image[HEIGHT][WIDTH][3];
unsigned char y_image[HEIGHT][WIDTH];
unsigned char ref_y_image[HEIGHT][WIDTH];

void read_bmp(const char *filename, unsigned char image[HEIGHT][WIDTH][3])
{
    FILE *f = fopen(filename, "rb");
    if (!f)
    {
        perror("Cannot open BMP file");
        exit(1);
    }

    fread(header, sizeof(unsigned char), HEADER_SIZE, f); // BMP header
    for (int i = 0; i < HEIGHT; ++i)
        for (int j = 0; j < WIDTH; ++j)
            fread(image[i][j], sizeof(unsigned char), 3, f); // BGR order

    fclose(f);
}

void read_y_bmp(const char *filename, unsigned char y_img[HEIGHT][WIDTH])
{
    FILE *f = fopen(filename, "rb");
    if (!f)
    {
        perror("Cannot open Y BMP file");
        exit(1);
    }

    fread(header, sizeof(unsigned char), HEADER_SIZE, f); // Skip header
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            fread(&y_img[i][j], sizeof(unsigned char), 1, f); // Read Y only
            // printf("%3d ", y_img[i][j]);
        }
        // printf("\n");
    }
    fclose(f);
}

void rgb_to_y()
{
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            unsigned char R = rgb_image[i][j][2];
            unsigned char G = rgb_image[i][j][1];
            unsigned char B = rgb_image[i][j][0];
            float y_val = ((66 * R + 129 * G + 25 * B + 128) >> 8) + 16;
            if (y_val > 255)
                y_val = 255;
            if (y_val < 0)
                y_val = 0;
            y_image[i][j] = (unsigned char)(round(y_val));
        }
    }
}

void write_y_bmp(const char *filename, unsigned char y_img[HEIGHT][WIDTH])
{
    FILE *f = fopen(filename, "wb");
    if (!f)
    {
        perror("Cannot write BMP file");
        exit(1);
    }

    fwrite(header, sizeof(unsigned char), HEADER_SIZE, f); // 寫入原始 header

    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            unsigned char y = y_img[i][j];
            fwrite(&y, sizeof(unsigned char), 1, f);
            fwrite(&y, sizeof(unsigned char), 1, f);
            fwrite(&y, sizeof(unsigned char), 1, f);
        }
    }

    fclose(f);
}
void compute_error()
{
    int sum = 0;
    int max_error = 0;
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            int diff = abs(y_image[i][j] - ref_y_image[i][j]);
            sum += diff;
            if (diff > max_error)
                max_error = diff;
        }
    }
    double avg = (double)sum / (WIDTH * HEIGHT);
    printf("Maximum Absolute Error: %d\n", max_error);
    printf("Average Absolute Error: %.2f\n", avg);
    printf("Sum Absolute Error: %d\n", sum);
}

int main()
{
    read_bmp("mountain256.bmp", rgb_image);
    rgb_to_y();
    write_y_bmp("version3_y.bmp", y_image);
    read_y_bmp("version3_y.bmp", y_image);
    read_y_bmp("mountain256Y_fx.bmp", ref_y_image);
    compute_error();
    return 0;
}
