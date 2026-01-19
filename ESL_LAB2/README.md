* exercise1: Shifter
  
* exercise2: Producer and Consumer
  
* exercise3: Test in SystemC
  
* exercise4: RGB to YUV
  - version1:
    ```math
    Y=0.299*R+0.587*G+0.114*B
    U=-0.169*R-0.331*G+0.5*B+128
    V=0.5*R-0.419*G-0.081*B+128
    ```
  - version2:
  - version3:
---
## Vivado 合成結果
| RGB2YUV | Maximum Absolute Error | Average Absolute Error |
| ------- | ---------------------- | ---------------------- |
| version1 vs version2 | 1 | 0.00 |
| version1 vs version3 | 18 | 3.63 |
| version1 vs version4 | 18 | 3.60 |

