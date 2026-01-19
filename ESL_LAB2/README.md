# SystemC
* exercise1: Shifter
  
* exercise2: Producer and Consumer
  
* exercise3: Test in SystemC
  
* exercise4: RGB to YUV
  - version1: Complete the C program of RGB to YUV with the formula
    ```math
    Y = 0.299R + 0.587G + 0.114B
    ```
    ```math
    U = -0.169R - 0.331G + 0.5B + 128
    ```
    ```math
    V = 0.5R - 0.419G - 0.081B + 128
    ```
  - version2: Complete the C program of RGB to YUV with the formula
    ```math
    Y = 0.2568R + 0.5041G + 0.0979B + 16
    ```
    ```math
    U = -0.1482R - 0.2910G + 0.4392B + 128
    ```
    ```math
    V = 0.4392R - 0.3678G - 0.0714B + 128
    ```
  - version3: Complete the C program of RGB to YUV with the formula
    ```math
    Y = ((66R + 129G + 25B + 128) >> 8) +16
    ```
    ```math
    U = ((-38R - 74G + 25B + 128) >> 8) + 128
    ```
    ```math
    V = ((112R - 94G - 18B + 128) >> 8) + 128
    ```
  - version4: Complete the SystemC program of RGB to YUV with sc_fixed or sc_ufixed data type with the formula
    ```math
    Y = 0.299R + 0.587G + 0.114B
    ```
    ```math
    U = -0.169R - 0.331G + 0.5B + 128
    ```
    ```math
    V = 0.5R - 0.419G - 0.081B + 128
    ```
---
## Y value 誤差表格
| RGB2YUV | Maximum Absolute Error | Average Absolute Error |
| ------- | ---------------------- | ---------------------- |
| version1 vs version2 | 1 | 0.00 |
| version1 vs version3 | 18 | 3.63 |
| version1 vs version4 | 18 | 3.60 |

