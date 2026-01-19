* version1: Implement the RGB to YUV circuit with **one multiplier and one adder** by using structural (FSM+ Datapath) Verilog code.
* version2: Implement the RGB to YUV circuit with **three multipliers and three adders** by using structural (FSM+ Datapath) Verilog code.
* version3: Implement the RGB to YUV circuit with **three multipliers, three adders, and initiation interval = 3** by using structural (FSM+ Datapath) Verilog code.
--
| :RGB2YUV: | :DSP: | :LUT: | :FF: | :Clock Freq.: | :Cycle: |
| :version1:  | :0: | :200: | :93: | :151.9 MHz: | :3145960: |
| :version2:  | :0: | :235: | :105: | :45.8 MHz: | :3145960: |
| :version3:  | :0: | :277: | :132: | :50.5 MHz: | :786672: |
