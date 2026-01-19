#define SC_INCLUDE_FX
#include <systemc.h>
#include <iostream>
#include <fstream>
#include <vector>


struct RGBPixel {
    sc_fixed<9,9,SC_RND,SC_SAT> B;
    sc_fixed<9,9,SC_RND,SC_SAT> G;
    sc_fixed<9,9,SC_RND,SC_SAT> R;
};

struct YUVPixel {
    sc_fixed<9,9,SC_RND,SC_SAT> Y;
    sc_fixed<9,9,SC_RND,SC_SAT> U;
    sc_fixed<9,9,SC_RND,SC_SAT> V;
};

SC_MODULE(rgb2yuv_fx) {
    sc_in<bool> clock;

    SC_CTOR(rgb2yuv_fx) {
        SC_THREAD(compute);
        sensitive << clock.pos();
        dont_initialize();
    }

    void compute() {
        const int width = 256;
        const int height = 256;
        const int row_padded = (width * 3 + 3) & (~3); // Align 4 byte every row

        std::ifstream inputImage("mountain256.bmp", std::ios::binary);
        if (!inputImage.is_open()) {
            std::cerr << "Error: Unable to open input image file." << std::endl;
            return;
        }

        std::ofstream outputY("mountain256Y_fx.bmp", std::ios::binary);
        std::ofstream outputU("mountain256U_fx.bmp", std::ios::binary);
        std::ofstream outputV("mountain256V_fx.bmp", std::ios::binary);
        if (!outputY.is_open() || !outputU.is_open() || !outputV.is_open()) {
            std::cerr << "Error: Unable to create output image files." << std::endl;
            return;
        }

        // Read and Write BMP Header(54 bytes)
        char header[54];
        inputImage.read(header, 54);
        outputY.write(header, 54);
        outputU.write(header, 54);
        outputV.write(header, 54);

        std::vector<unsigned char> row(row_padded);

        for (int y = 0; y < height; ++y) {
            inputImage.read(reinterpret_cast<char*>(row.data()), row_padded);

            for (int x = 0; x < width; ++x) {
                RGBPixel rgbPixel;
                rgbPixel.B = row[x * 3 + 0];
                rgbPixel.G = row[x * 3 + 1];
                rgbPixel.R = row[x * 3 + 2];

                YUVPixel yuvPixel = RGB2YUV(rgbPixel);
                /*
                unsigned char Y_byte = static_cast<unsigned char>(std::min(std::max(yuvPixel.Y.to_double(), 0.0), 255.0));
                unsigned char U_byte = static_cast<unsigned char>(std::min(std::max(yuvPixel.U.to_double(), 0.0), 255.0));
                unsigned char V_byte = static_cast<unsigned char>(std::min(std::max(yuvPixel.V.to_double(), 0.0), 255.0));
                */
                unsigned char imageY = static_cast<unsigned char>(yuvPixel.Y);
                unsigned char imageU = static_cast<unsigned char>(yuvPixel.U);
                unsigned char imageV = static_cast<unsigned char>(yuvPixel.V);
                
                outputY.write(reinterpret_cast<char*>(&imageY), 1);
                outputY.write(reinterpret_cast<char*>(&imageY), 1);
                outputY.write(reinterpret_cast<char*>(&imageY), 1);

                outputU.write(reinterpret_cast<char*>(&imageU), 1);
                outputU.write(reinterpret_cast<char*>(&imageU), 1);
                outputU.write(reinterpret_cast<char*>(&imageU), 1);

                outputV.write(reinterpret_cast<char*>(&imageV), 1);
                outputV.write(reinterpret_cast<char*>(&imageV), 1);
                outputV.write(reinterpret_cast<char*>(&imageV), 1);
            }
            // Write padding
            unsigned char padding[3] = {0, 0, 0};
            int pad = row_padded - width * 3;
            outputY.write(reinterpret_cast<char*>(padding), pad);
            outputU.write(reinterpret_cast<char*>(padding), pad);
            outputV.write(reinterpret_cast<char*>(padding), pad);
        }

        inputImage.close();
        outputY.close();
        outputU.close();
        outputV.close();

        std::cout << "Image conversion completed successfully." << std::endl;
        sc_stop();
    }

    YUVPixel RGB2YUV(const RGBPixel& rgbPixel) {
        YUVPixel yuvPixel;
        yuvPixel.Y =       0.299 * rgbPixel.R + 0.587 * rgbPixel.G + 0.114 * rgbPixel.B;
        yuvPixel.U = 128 - 0.169 * rgbPixel.R - 0.331 * rgbPixel.G + 0.500 * rgbPixel.B;
        yuvPixel.V = 128 + 0.500 * rgbPixel.R - 0.419 * rgbPixel.G - 0.081 * rgbPixel.B;
        return yuvPixel;
    }
};

int sc_main(int argc, char* argv[]) {
    sc_clock clock("clock", 1, SC_NS);
    rgb2yuv_fx rgb2yuv_fx("rgb2yuv_fx");
    rgb2yuv_fx.clock(clock);
    sc_start();
    return 0;
}
