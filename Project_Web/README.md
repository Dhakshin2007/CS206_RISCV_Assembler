# RISC-V Assembler (Web Version)

This is the **web-based interface** for the RISC-V Assembler.  
It allows users to assemble RISC-V code through a simple local web interface.

---

## 📂 Project Structure

```
Project_Web/
├── public/
├── assembler_runtime.exe
├── Assembler.cpp
├── main.cpp
├── server.js
├── tmp_*_input.s
├── tmp_*_output.txt
└── readme.md
```

---

## 🧰 Tech Stack
- **Frontend:** HTML, CSS, JavaScript  
- **Backend / Runtime:** C++, Node.js  

---

## ⚙️ How to Run (Web Version)

1. **Download the ZIP** and extract it.  
2. Open a terminal inside the `Project_Web` folder.  
3. **Compile the assembler runtime**:
   ```bash
   g++ -std=c++17 -O2 Assembler.cpp main.cpp -o assembler_runtime
   ```
4. Check if **Node.js** is installed:
   ```bash
   node --version
   ```
   If not installed, please install Node.js first.
5. **Run the server:**
   ```bash
   node server.js
   ```
6. Open your browser and go to:
   ```
   http://localhost:3000
   ```
   You’ll be able to upload RISC-V assembly files and get machine code output directly in the browser.

---

## 📘 Note
The `assembler_runtime.exe` is automatically created after compiling.  
Temporary input and output files are stored with names like:
```
tmp_<timestamp>_input.s
tmp_<timestamp>_output.txt
```
