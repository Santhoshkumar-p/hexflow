# hexflow 
Low level Hexagon DSP Neural Network Library [WIP] 

**Hexagon DSP Gotchas:**

- The Hexagon DSP is a 32-bit mobile processor with its own ISA (VLIW), primarily designed for Audio, Video, and Image
processing.
- Functioning as a general-purpose CPU, it is optimized for handling compute tasks with a low clock frequency,
addressing power concerns for various workloads.
- Communication between the CPU and DSP is facilitated through IOCTL/Driver based.
- Using native interface we can call DSP driver which will establish a remote session on DSP side for inferencing.

**Target Platform:** The intended platform for Hexagon DSP is predominantly Android.

It is mainly built for tinygrad (https://github.com/tinygrad/tinygrad) development environment and eventually can run as an independendent library. 

