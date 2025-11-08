# RISC-V Assembler (Offline Version)

This is the **offline RISC-V Assembler**, developed as part of the **CS206 – Foundations of Computer Systems** course at **IIT Ropar** under **Dr. T. V. Kalyan**.  
This assembler converts RISC-V assembly instructions into machine code.

---

## 📂 Project Structure

```
Project_Main/
├── Assembler.cpp
├── assembler.exe
├── input.asm
├── output.mc
├── README.md
└── ReadMe.txt
```
---
##Before running the file makesure that the ouput.mc file is cleared
 
---
---

## 🧰 Tech Stack
- **C++**

---

## ⚙️ How to Run (Offline)

1. **Download the ZIP file** and extract it.  
2. Open a terminal inside the extracted folder (`Project_Main`).
3. **Compile the assembler** using:
   ```bash
   g++ assembler_required_format.cpp -o assembler
   ```
4. Place your RISC-V assembly code in `input.asm`.
5. **Run the assembler:**
   ```bash
   ./assembler
   ```
6. Output will be generated in the file:
   ```
   output.mc
   ```
   This file contains the **machine codes** corresponding to your RISC-V instructions.

---

## 👥 Project Contributors
- **K Dhakshin** – [Portfolio](https://dhakshin-portfolio.vercel.app/) – Roll No: 2024AIB1009  
- **J Yeswanth** – [Portfolio](https://yeswanth-portfolio-weld.vercel.app/) – Roll No: 2024AIB1008  

---

## 📘 Course Details
**CS206 – Foundations of Computer Systems**  
**Instructor:** [T. V. Kalyan](https://sites.google.com/view/kalyantv)  
**Institute:** IIT Ropar
