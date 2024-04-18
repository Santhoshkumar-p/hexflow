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

**[Progress]**

The current ability is to run the **Baby Llama2 15M model** on a DSP simulator at a rate of 0.03 tokens per second.
<img width="1148" alt="image" src="https://github.com/Santhoshkumar-p/hexflow/assets/24734488/3668f2dd-603f-48df-a453-3724523c9b39">
<img width="1148" alt="image" src="https://github.com/Santhoshkumar-p/hexflow/assets/24734488/1e151234-d3f9-466c-be33-3080c6685eec">

And **260K model** is producing at a rate of 0.3 tokens per second which is a huge improvement and obvious one.
The target is to achieve a processing rate of at least 10 tokens per second for the Baby Llama2 15M model running on the DSP simulator.

