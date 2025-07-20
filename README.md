# 2-Bit Comparator using VSDSquadron Mini

## Overview
The program is based on the RISC-V architecture and uses open-source tools to teach people about VLSI chip design and RISC-V. The instructor for this internship is Kunal Ghosh Sir.

**Name:** Mrudu Bhashini CR  
**College:** SRMIST Ramapuram  
**Email ID:** mrudhuramraj@gmail.com  
**GitHub Profile:**  https://github.com/mrudu06


This project involves the implementation of a 2-bit digital comparator using VSDSquadron Mini, a RISC-V based SoC development kit. A 2-bit comparator is a fundamental digital circuit that compares two 2-bit binary numbers and determines their relationship (greater than, less than, or equal to). This project demonstrates the practical application of digital logic and RISC-V architecture in executing comparison operations, reflecting the process of reading binary data through GPIO pins and implementing comparison logic through digital operations.

## Task 1: Install all the essential tools required for this internship

Task is to install all the essential tools required for this internship such as Ubuntu on VMBox, GNU Toolchain, GTKWave, Yosys and iVerilog simulator.

### 1. Install Ubuntu 20.04 LTS on Oracle Virtual Machine Box
*(https://github.com/mrudu06/vsd-riscv/blob/main/Task%201/RISCV%20simulation%20.png.png)*
*(https://github.com/mrudu06/vsd-riscv/blob/main/Task%201/sum1ton.png.png)*

### 2. Install RISC-V GNU ToolChain
The RISC-V GNU Compiler Toolchain is a free and open source cross-compiler for C and C++. It supports two build modes: Generic ELF/Newlib and Linux-ELF/glibc. The toolchain can be used to create assembly instructions and sequences for execution in a simulator and target FPGA.

Use the following command to install GNU Toolchain:
```bash
$ sudo apt install git
$ git clone https://github.com/riscv/riscv-gnu-toolchain
$ sudo apt-get install autoconf automake autotools-dev curl python3 python3-pip libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev ninja-build git cmake libglib2.0-dev libslirp-dev
$ mkdir /opt/riscv
$ ./configure --prefix=/opt/riscv --with-arch=rv64i --with-abi=lp64 --enable-multilib
$ sudo make
```

Now add `/opt/riscv/bin` to PATH:
```bash
$ gedit ~/.bashrc
```
Add the line `export PATH="$PATH:/opt/riscv/bin"` in the end of file and save it. After that run:
```bash
$ source ~/.bashrc
```

### 3. Install Yosys Open SYnthesis Suite
Yosys, or Yosys Open SYnthesis Suite, is a free, open-source framework for Verilog RTL synthesis. It can be used to process almost any synthesizable Verilog-2005 design, and to convert Verilog to BLIF, EDIF, BTOR, SMT-LIB, and more.

```bash
$ git clone https://github.com/YosysHQ/yosys.git
$ cd yosys
$ sudo apt install make
$ sudo apt-get install build-essential clang bison flex \
    libreadline-dev gawk tcl-dev libffi-dev git \
    graphviz xdot pkg-config python3 libboost-system-dev \
    libboost-python-dev libboost-filesystem-dev zlib1g-dev
$ make config-gcc
$ make
$ sudo make install
```

### 4. Install GTKwave
GTKWave is a free, lightweight waveform viewer that's used to display simulation output. It's based on the GTK library and supports VCD and LXT formats for signal dumps.

```bash
$ sudo apt update
$ sudo apt install gtkwave
```


### 5. Install Icarus Verilog
Icarus Verilog is a compiler for the Verilog hardware description language (HDL). It's used to collect Verilog source code, check for errors, and write compiled design files.

```bash
$ sudo apt-get install iverilog
```


## Task 2: Identify instruction type of all the given instructions with exact 32 bits instruction code

RISC-V is an open-source instruction set architecture (ISA) that allows developers to develop processors for specific applications. RISC-V is based on reduced instruction set computer principles and is the fifth generation of processors built on this concept.

There are 6 instruction formats in RISC-V:
- **R-format:** Register-Register operations
- **I-format:** Immediate and Load operations  
- **S-format:** Store operations
- **B-format:** Branch operations
- **U-format:** Upper immediate operations
- **J-format:** Jump operations

### Instruction Analysis:

**1. ADD r6, r2, r1**
- **Type:** R-format
- **Operation:** r6 = r2 + r1
- **Binary:** `0000000_00001_00010_000_00110_0110011`

**2. SUB r7, r1, r2**  
- **Type:** R-format
- **Operation:** r7 = r1 - r2
- **Binary:** `0100000_00010_00001_000_00111_0110011`

**3. AND r8, r1, r3**
- **Type:** R-format
- **Operation:** r8 = r1 & r3
- **Binary:** `0000000_00011_00001_111_01000_0110011`

**4. OR r9, r2, r5**
- **Type:** R-format  
- **Operation:** r9 = r2 | r5
- **Binary:** `0000000_00101_00010_110_01001_0110011`

**5. XOR r10, r1, r4**
- **Type:** R-format
- **Operation:** r10 = r1 ^ r4
- **Binary:** `0000000_00100_00001_100_01010_0110011`

**6. SLT r11, r2, r4**
- **Type:** R-format
- **Operation:** r11 = (r2 < r4) ? 1 : 0
- **Binary:** `0000000_00100_00010_010_01011_0110011`

**7. ADDI r12, r4, 5**
- **Type:** I-format
- **Operation:** r12 = r4 + 5
- **Binary:** `000000000101_00100_000_01100_0010011`

**8. SW r3, r1, 2**
- **Type:** S-format
- **Operation:** Memory[r1 + 2] = r3
- **Binary:** `0000000_00011_00001_010_00010_0100011`

**9. SRL r16, r14, r2**
- **Type:** R-format
- **Operation:** r16 = r14 >> r2
- **Binary:** `0000000_00010_01110_101_10000_0110011`

**10. BNE r0, r1, 20**
- **Type:** B-format
- **Operation:** if(r0 != r1) PC = PC + 20
- **Binary:** `0_000001_00001_00000_001_0100_0_1100011`

**11. BEQ r0, r0, 15**
- **Type:** B-format
- **Operation:** if(r0 == r0) PC = PC + 15
- **Binary:** `0_000000_00000_00000_000_1111_0_1100011`

**12. LW r13, r1, 2**
- **Type:** I-format
- **Operation:** r13 = Memory[r1 + 2]
- **Binary:** `000000000010_00001_010_01101_0000011`

**13. SLL r15, r1, r2**
- **Type:** R-format
- **Operation:** r15 = r1 << r2
- **Binary:** `0000000_00010_00001_001_01111_0110011`


## Task 3: Compile C code using gcc and RISC-V compiler

### C Code Compilation with GCC
First, create a simple C program:

```c
#include<stdio.h>
int main() {
    int sum = 0, n = 5;
    for(int i = 1; i <= n; i++) {
        sum += i;
    }
    printf("Sum of numbers from 1 to %d is %d\n", n, sum);
    return 0;
}
```

Compile and run with GCC:
```bash
$ gcc sum_1ton.c
$ ./a.out
```

(https://github.com/mrudu06/vsd-riscv/blob/main/Task%202/Printnum.png.png)

### C Code Compilation with RISC-V Compiler

```bash
$ cat sum_1ton.c
$ riscv64-unknown-elf-gcc -O1 -mabi=lp64 -march=rv64i -o sum_1ton.o sum_1ton.c
$ riscv64-unknown-elf-objdump -d sum_1ton.o
```

**Compiler Options Explanation:**
- **-mabi=lp64:** Specifies the ABI for 64-bit integer, long and pointer size
- **-march=rv64i:** Specifies 64-bit RISC-V base integer instruction set
- **-O1:** Optimization level 1 for balanced performance and compilation time
- **-Ofast:** Maximum speed optimization
- **-O0:** No optimization (default)

(https://github.com/mrudu06/vsd-riscv/blob/main/Task%202/RISCV%20%20-Ofast%20objdump.png.png)
(https://github.com/mrudu06/vsd-riscv/blob/main/Task%202/RISCV%20-O1%20objdump.png.png)
## Task 4: SPIKE Simulation and Debugging

SPIKE is a RISC-V ISA simulator that enables testing and analysis of RISC-V programs without actual hardware.

### Install SPIKE
```bash
$ git clone https://github.com/riscv/riscv-isa-sim.git
$ cd riscv-isa-sim
$ mkdir build
$ cd build
$ sudo apt-get install device-tree-compiler
$ sudo apt-get install libboost-all-dev
$ ../configure --prefix=/opt/riscv
$ make
$ sudo make install
```

### Install Proxy Kernel (pk)
```bash
$ git clone https://github.com/riscv/riscv-pk.git
$ cd riscv-pk
$ mkdir build
$ cd build
$ ../configure --prefix=/opt/riscv --host=riscv64-unknown-elf --with-arch=rv64gc
$ make
$ sudo make install
```

### Run Simulation
```bash
$ spike pk sum_1ton.o
```

### Interactive Debugging
```bash
$ spike -d pk sum_1ton.o
```


## Task 5: Functional Simulation using Verilog Netlist and Testbench

**Note:** Since designing RISC-V Architecture and writing testbench is not part of this internship, we use pre-designed Verilog code.

### Steps:
1. Create directory: `mkdir <your_name>`
2. Create files: `touch <name>_rv32i.v` and `<name>_rv32i_tb.v`
3. Copy Verilog code from reference repository
4. Run simulation:
   ```bash
   $ iverilog -o <name>_rv32i <name>_rv32i.v <name>_rv32i_tb.v
   $ ./<name>_rv32i
   ```
5. View waveforms:
   ```bash
   $ gtkwave <name>_rv32i.vcd
   ```

### Instruction Comparison Table

| Operation | Standard RISC-V ISA | Hardcoded ISA |
|-----------|-------------------|---------------|
| ADD R6, R2, R1 | 32'h00110333 | 32'h02208300 |
| SUB R7, R1, R2 | 32'h402083b3 | 32'h02209380 |
| AND R8, R1, R3 | 32'h0030f433 | 32'h0230a400 |
| OR R9, R2, R5 | 32'h005164b3 | 32'h02513480 |
| XOR R10, R1, R4 | 32'h0040c533 | 32'h0240c500 |

(https://github.com/mrudu06/vsd-riscv/blob/main/Task%204/Screenshot%202025-06-17%20205435.png)
(https://github.com/mrudu06/vsd-riscv/blob/main/Task%204/Screenshot%202025-06-17%20205628.png)
(https://github.com/mrudu06/vsd-riscv/blob/main/Task%204/Screenshot%202025-06-17%20205929.png)
(https://github.com/mrudu06/vsd-riscv/blob/main/Task%204/Screenshot%202025-06-17%20210015.png)
(https://github.com/mrudu06/vsd-riscv/blob/main/Task%204/Screenshot%202025-06-17%20210023.png)
(https://github.com/mrudu06/vsd-riscv/blob/main/Task%204/Screenshot%202025-06-17%20210053.png)
(https://github.com/mrudu06/vsd-riscv/blob/main/Task%204/Screenshot%202025-06-17%20210041.png)
(https://github.com/mrudu06/vsd-riscv/blob/main/Task%204/Screenshot%202025-06-17%20210108.png)
(https://github.com/mrudu06/vsd-riscv/blob/main/Task%204/Screenshot%202025-06-17%20210123.png)
(https://github.com/mrudu06/vsd-riscv/blob/main/Task%204/Screenshot%202025-06-17%20210140.png)
(https://github.com/mrudu06/vsd-riscv/blob/main/Task%204/Screenshot%202025-06-17%20210152.png)
(https://github.com/mrudu06/vsd-riscv/blob/main/Task%204/Screenshot%202025-06-17%20210321.png)
(https://github.com/mrudu06/vsd-riscv/blob/main/Task%204/Screenshot%202025-06-17%20210330.png)
## Task 6: Final Implementation - 2-Bit Comparator using VSDSquadron Mini

This final task implements a 2-bit digital comparator circuit using VSDSquadron Mini to demonstrate practical RISC-V application.

### About VSDSquadron Mini
VSDSquadron Mini is a RISC-V based development board designed for learning and implementing digital logic circuits. It provides GPIO pins for interfacing with external components and supports programming in C using PlatformIO IDE.

## Components Required
- VSDSquadron Mini development board
- 4 Push buttons (for 2-bit inputs A1, A0, B1, B0)
- 3 LEDs (for outputs: A>B, A<B, A=B)
- Breadboard
- Jumper wires
- Resistors (220Ω for LEDs, 10kΩ for pull-up if needed)
- VS Code with PlatformIO extension

## Pin Configuration
- **Input Pins (GPIO D):**
  - PD1: Input A1 (MSB of first 2-bit number)
  - PD2: Input A0 (LSB of first 2-bit number)  
  - PD3: Input B1 (MSB of second 2-bit number)
  - PD4: Input B0 (LSB of second 2-bit number)

- **Output Pins (GPIO C):**
  - PC4: A>B LED output
  - PC5: A<B LED output
  - PC6: A=B LED output

## Circuit Diagram
(https://github.com/mrudu06/vsd-riscv/blob/main/Task%205/Screenshot%202025-07-20%20095803.png)
## Truth Table
The 2-bit comparator follows this truth table:

| A1 | A0 | B1 | B0 | A>B | A<B | A=B |
|----|----|----|----|----|----|----|
| 0  | 0  | 0  | 0  | 0   | 0   | 1   |
| 0  | 0  | 0  | 1  | 0   | 1   | 0   |
| 0  | 0  | 1  | 0  | 0   | 1   | 0   |
| 0  | 0  | 1  | 1  | 0   | 1   | 0   |
| 0  | 1  | 0  | 0  | 1   | 0   | 0   |
| 0  | 1  | 0  | 1  | 0   | 0   | 1   |
| 0  | 1  | 1  | 0  | 0   | 1   | 0   |
| 0  | 1  | 1  | 1  | 0   | 1   | 0   |
| 1  | 0  | 0  | 0  | 1   | 0   | 0   |
| 1  | 0  | 0  | 1  | 1   | 0   | 0   |
| 1  | 0  | 1  | 0  | 0   | 0   | 1   |
| 1  | 0  | 1  | 1  | 0   | 1   | 0   |
| 1  | 1  | 0  | 0  | 1   | 0   | 0   |
| 1  | 1  | 0  | 1  | 1   | 0   | 0   |
| 1  | 1  | 1  | 0  | 1   | 0   | 0   |
| 1  | 1  | 1  | 1  | 0   | 0   | 1   |

## Working Principle
The 2-bit comparator works by implementing the following logic:
- **A = B**: When both 2-bit numbers are equal
- **A > B**: When the first 2-bit number is greater than the second
- **A < B**: When the first 2-bit number is less than the second

The comparison is done by checking the most significant bits first, and if they are equal, then checking the least significant bits.

## Code Implementation

```c
// 2-Bit Comparator Implementation
// Include required header files
#include<stdio.h>
#include<debug.h>
#include<ch32v00x.h>

// GPIO Configuration Function
void GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};
    
    // Enable clock for GPIOD and GPIOC
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    
    // Configure input pins (PD1-PD4) for 2-bit inputs A and B
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; // Input with pull-up
    GPIO_Init(GPIOD, &GPIO_InitStructure);
    
    // Configure output pins (PC4-PC6) for comparison results
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; // Output push-pull
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

// Main function
int main()
{
    uint8_t A1, A0, B1, B0;
    uint8_t A_greater_B, A_less_B, A_equal_B;
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    SystemCoreClockUpdate();
    Delay_Init();
    GPIO_Config();
    
    while(1)
    {
        // Read input values
        A1 = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_1); // MSB of A
        A0 = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_2); // LSB of A
        B1 = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_3); // MSB of B
        B0 = GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_4); // LSB of B
        
        // 2-bit comparison logic
        // A = B condition
        A_equal_B = ((A1 == B1) && (A0 == B0));
        
        // A > B condition
        A_greater_B = ((A1 > B1) || ((A1 == B1) && (A0 > B0)));
        
        // A < B condition  
        A_less_B = ((A1 < B1) || ((A1 == B1) && (A0 < B0)));
        
        // Set outputs (Active LOW LEDs)
        GPIO_WriteBit(GPIOC, GPIO_Pin_4, A_greater_B ? RESET : SET); // A>B LED
        GPIO_WriteBit(GPIOC, GPIO_Pin_5, A_less_B ? RESET : SET);    // A<B LED
        GPIO_WriteBit(GPIOC, GPIO_Pin_6, A_equal_B ? RESET : SET);   // A=B LED
        
        Delay_Ms(100); // Small delay for debouncing
    }
}
```

## Hardware Setup Images
(https://github.com/mrudu06/vsd-riscv/blob/main/Task%205/Screenshot%202025-07-20%20095803.png)
## Working Video
(https://github.com/mrudu06/vsd-riscv/blob/main/Task%205/WhatsApp%20Video%202025-07-19%20at%2021-VEED.mp4)
## Results and Observations
The 2-bit comparator successfully:
- Compares two 2-bit binary numbers in real-time
- Displays the correct comparison result through LED indicators
- Demonstrates the practical implementation of digital logic using RISC-V architecture
- Shows the effectiveness of GPIO pin configuration and digital I/O operations

## Applications
- Digital arithmetic circuits
- Processor design (ALU units)
- Sorting algorithms implementation
- Decision making circuits
- Multi-bit number comparison systems

## Conclusion
This project successfully demonstrates the implementation of a 2-bit digital comparator using VSDSquadron Mini. The project showcases the practical application of digital logic principles, RISC-V architecture programming, and GPIO interfacing. The real-time comparison functionality validates the effectiveness of the implemented logic and hardware configuration.

## Future Enhancements
- Extend to 4-bit or 8-bit comparator
- Add 7-segment display for numerical representation
- Implement cascaded comparators for larger bit widths
- Add magnitude comparison with signed numbers
- Create a complete ALU with comparison functionality

## Acknowledgments
I would like to thank Kunal Ghosh Sir and the VSD team for providing this excellent opportunity to learn and implement digital logic circuits using RISC-V architecture. This project has enhanced my understanding of digital electronics, embedded programming, and hardware interfacing.

---

