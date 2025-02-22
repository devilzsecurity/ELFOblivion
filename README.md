# ELFOblivion
ELFOblivion is a cutting-edge anti-reversing tool designed to make ELF binaries nearly impossible to analyze. By strategically corrupting critical ELF structures—such as the ELF header, section headers, and symbol table—this tool disrupts static analysis while still allowing the binary to execute under normal conditions.



# Features
🔥 ELF Header Corruption – Subtly modifies the magic bytes and offsets to break ELF parsing.
💀 Section Table Erasure – Overwrites key sections, making static analysis ineffective.
🔒 Symbol Table Destruction – Eliminates function and symbol references, making reverse engineering painful.
🕵️ Preserves Executability – The binary remains functional, but nearly impossible to analyze.
⚡ Lightweight & Fast – Processes ELF binaries in seconds with minimal dependencies.

Usage:
./elfoblivion <binary> <mod 1 or 2>
mod 1: basic destruction
mod 2: hard destruction



![image](https://github.com/user-attachments/assets/3dd9b531-66f2-482d-930d-2dbf7b6d8a4e)
