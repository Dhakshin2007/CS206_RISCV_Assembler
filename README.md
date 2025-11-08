# CS206 Project – RISC-V Assembler

This repository contains the **RISC-V Assembler project** built for the  
**CS206 – Foundations of Computer Systems** course at **IIT Ropar**, guided by [T. V. Kalyan](https://sites.google.com/view/kalyantv).

The project includes both **offline** and **web-based** RISC-V assemblers.

---

## 📂 Repository Structure

```
CS206_Project/
├── Project_Main/     # Offline RISC-V Assembler
├── Project_Web/      # Web-based RISC-V Assembler
```

---

## 🚀 Quick Start

### For Offline Use:
```bash
cd Project_Main
g++ assembler.cpp -o assembler
./assembler
```

### For Web Use:
```bash
cd Project_Web
g++ -std=c++17 -O2 Assembler.cpp main.cpp -o assembler_runtime
node server.js
```

---

## 🧠 Project Overview

This assembler translates **RISC-V assembly instructions** into **machine code**.  
- Offline mode: Runs directly in a terminal.  
- Web mode: Runs via Node.js and serves a frontend for easier interaction.

---

## 👥 Contributors
- **K Dhakshin** – [Portfolio](https://dhakshin-portfolio.vercel.app/) – Roll No: 2024AIB1009  
- **J Yeswanth** – [Portfolio](https://yeswanth-portfolio-weld.vercel.app/) – Roll No: 2024AIB1008  

---

## 📘 Course Details
**CS206 – Foundations of Computer Systems**  
**Instructor:** [T. V. Kalyan](https://sites.google.com/view/kalyantv)  
**Institute:** IIT Ropar
