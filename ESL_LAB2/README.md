* exercise1: Shifter
  
* exercise2: Producer and Consumer
  
* exercise3: Test in SystemC
  
* exercise4: RGB to YUV
  - version1:
    $$
    \begin{aligned}
    Y &= 0.299R + 0.587G + 0.114B \\
    U &= -0.169R - 0.331G + 0.5B + 128 \\
    V &= 0.5R - 0.419G - 0.081B + 128
    \end{aligned}
    $$

  - version2:
  - version3:
---
## Y value 誤差表格
| RGB2YUV | Maximum Absolute Error | Average Absolute Error |
| ------- | ---------------------- | ---------------------- |
| version1 vs version2 | 1 | 0.00 |
| version1 vs version3 | 18 | 3.63 |
| version1 vs version4 | 18 | 3.60 |

