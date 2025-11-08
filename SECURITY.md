# 🔒 Security Policy

## Supported Versions

The CS206 RISC-V Assembler is a student-level educational project.  
Active development focuses only on the **latest commit** in the main and web branches.

| Version | Supported |
|----------|------------|
| main (latest) | ✅ |
| web (Render deployment) | ⚠️ Partial |
| local / older releases | ❌ No security updates |

---

## Reporting a Vulnerability

If you discover a security issue (such as command injection, file exposure, or unsafe process execution):

1. **Do not open a public issue** — this protects everyone using the project.
2. Instead, send a private email to:  
   **`kothadhakshin123@gmail.com`**
3. Include:
   - A clear description of the issue  
   - Steps to reproduce (if possible)  
   - Suggested fixes or mitigations  

You’ll receive an acknowledgement within **1 working day**, and we’ll discuss the resolution privately before public disclosure.

---

## Security Practices

- All web code runs within a **non-privileged Node.js environment**.  
- The backend avoids direct file uploads and executes C++ binaries with limited I/O permissions.  
- Sensitive user data is **not collected** or stored.  
- The offline assembler runs locally — it should be executed only on trusted systems.  

---

## Disclaimer

This project is intended **for educational and research use only**.  
It is **not production-grade software** and carries no guarantee of security, reliability, or data integrity.  
By using this code, you agree to run it **at your own risk**.

---

*Maintained by [K Dhakshin](https://dhakshin-portfolio.vercel.app/) and [J Yeswanth](https://yeswanth-portfolio-weld.vercel.app/) — under CS206, IIT Ropar.*
