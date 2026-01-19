* exercise1: Shifter
  
* exercise2: Producer and Consumer
  
* exercise3: Test in SystemC
  
* exercise4: RGB to YUV
  - version1:
    $
    Y=0.299*R+0.587*G+0.114*B
    U=-0.169*R-0.331*G+0.5*B+128
    V=0.5*R-0.419*G-0.081*B+128
    $
  - version2:
  - version3:
---
## Vivado 合成結果
| RGB2YUV | DSP | LUT | FF | Clock Freq. | Cycle |
| ------- | --- | --- | -- | ----------- | ----- |
| version1 | 0 | 200 |  93 | 151.9 MHz | 3145960 |
| version2 | 0 | 235 | 105 |  45.8 MHz | 3145960 |
| version3 | 0 | 277 | 132 |  50.5 MHz |  786672 |

