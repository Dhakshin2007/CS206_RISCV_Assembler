// script.js - minimal UI logic

document.addEventListener('DOMContentLoaded', () => {
  const runBtn = document.getElementById('run');
  const exampleBtn = document.getElementById('example');
  const codeArea = document.getElementById('code');
  const output = document.getElementById('output');

  runBtn.addEventListener('click', async () => {
    output.textContent = "Assembling... (please wait)\n";
    try {
      fetch("https://cs206-riscv-assembler.onrender.com/assemble", {
  method: "POST",
  headers: { "Content-Type": "application/json" },
  body: JSON.stringify({ code }),
});
      const text = await res.text();
      output.textContent = text;
    } catch (e) {
      output.textContent = 'ERROR: ' + e.message;
    }
  });

  exampleBtn.addEventListener('click', () => {
    codeArea.value = [
      ".text",
      "addi x1, x0, 5",
      "addi x2, x0, 3",
      "add x3, x1, x2",
      "sw x3, 0(x0)"
    ].join("\n");
  });
});
