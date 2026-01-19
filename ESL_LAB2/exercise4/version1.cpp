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
        for (int j = 0; j < WIDTH; ++j)
            fread(&y_img[i][j], sizeof(unsigned char), 1, f); // Read Y only
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
            float y_val = 0.299 * R + 0.587 * G + 0.114 * B;
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

void max_abs_error()
{
    int max_error = 0;
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            int diff = abs(y_image[i][j] - ref_y_image[i][j]);
            if (diff > max_error)
                max_error = diff;
        }
    }
    printf("Maximum Absolute Error: %d\n", max_error);
}

void avg_abs_error()
{
    int sum = 0;
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            int diff = abs(y_image[i][j] - ref_y_image[i][j]);
            sum += diff;
        }
    }
    double avg = (double)sum / (WIDTH * HEIGHT);
    printf("Average Absolute Error: %.2f\n", avg);
    printf("Sum Absolute Error: %d\n", sum);
}

int main()
{
    read_bmp("mountain256.bmp", rgb_image);
    rgb_to_y();
    write_y_bmp("version1_y.bmp", y_image);
    read_y_bmp("version1_y.bmp", y_image);
    read_y_bmp("mountain256Y_fx.bmp", ref_y_image);
    max_abs_error();
    avg_abs_error();
    return 0;
}
