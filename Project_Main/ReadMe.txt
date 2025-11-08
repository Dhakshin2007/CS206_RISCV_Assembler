~ Compiler Syntax
The syntax of the compiler is defined as follows:

~ Input File
The input should be provided in the file named input.asm in RISC-V assembly language format.


~ Prerequisites
Before providing the assembly code, ensure the following prerequisites are met:
# Including the ".text" segment is mandatory.
# Use space as a delimiter to separate operands; do not use commas.
# Comments are allowed and should start with a hashtag #.
# We are presuming registers from x0 - x31, no other namings like sp, ra are allowed.

*********************************************************************************************************************
~ Supported Instructions
The compiler supports the following RISC-V instructions:

-> R Format
add, and, or, sll, slt, sra, srl, sub, xor, mul, div, rem

-> I Format
addi, andi, ori, lb, ld, lh, lw, jalr

-> S Format
sb, sw, sd, sh

-> SB Format
beq, bne, bge, blt

-> U Format
auipc, lui

-> UJ Format
jal

~ Output
The output will be provided as machine code in the file output.mc. It includes both the Program Counter followed by the machine code.

@ Memory Segment
Memory segment starts at 0x10000000.

Input Format
The format to enter the instructions is as follows:

For R Format: add x1 x2 x3
For I Format: addi x2 x3 100
For Load Instructions: lb x4 0(x9)  Or lb x4 0 x9
For Jump and Link Register (Jalr): jalr x1 x3 100
For Branch Instructions: beq x1 x2 label_name Or beq x1 x2 100
For AUIPC: auipc x4 100
For Jump and Link (Jal): jal x1 100

*************************************************************************************************************************

Team-
&Jakka Yeswanth Teja - 2024AIB1008
&Kotha Dhakshin - 2024AIB1009