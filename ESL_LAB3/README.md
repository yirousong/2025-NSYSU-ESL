# HW/SW Co-Design of RGB2YUV and YUV2RGB
* version1: Use **Vivado HLS** to implement the **C program** (with integer data type) and the circuit of RGB to YUV.
  
* version2: Use **Vivado HLS** to implement the **SystemC program** (with sc_fixed data type) and the circuit of RGB to YUV.
  
* version3: Use **Verilog code** implement the circuit of RGB to YUV with **one multiplier and one adder**.
  
---
## 結果分析
| RGB2YUV |  DSP | LUT | FF | Clock Freq. | Execution Time |
| ------- | ---- | --- | -- | ----------- | -------------- |
| version1 | 25  | 2581 | 3025 | 105 MHz | 13.281702 sec |
| version2 | 4 | 1140 | 1432 | 115 MHz | 11.020362 sec |
| version3 | 0 | 657 | 726 | 108 MHz | 9.343563 sec |


