# 📘 Baekjoon Problem Solving Log

This repository is a personal archive of solved problems from [Baekjoon Online Judge](https://www.acmicpc.net/).  
Each folder contains the source code and a detailed thought process written in Markdown format.

---

## 📁 Directory Structure

baekjoon-log/  
├── 1991_트리_순회/  
│ ├── main.cpp ← C++ source code  
│ └── README.md ← Thought process, implementation notes, review  
├── 11724_연결_요소_구하기/  
│ ├── main.cpp  
│ └── README.md  
├── ...  
└── README.md ← This file  


---

## ✍️ Logging Format

Each problem folder contains:
- `main.cpp` – the actual C++ solution
- `README.md` – a structured log including:
  - Problem summary
  - Step-by-step thought process
  - Implementation details
  - Review and reflection
  - Related problems (optional)

---

## 🧠 Why Keep This Log?

- Reinforces understanding by writing down the **thought process**
- Helps spot patterns and **common techniques**
- Serves as a **review archive** before contests or interviews
- Makes it easier to reuse or explain solutions later

---

## 🧪 Sample Entry (README.md per problem)

```markdown
# [BOJ 1991] 트리 순회

## 🧾 Problem Summary
Given a binary tree, print its preorder, inorder, and postorder traversal results.

## 💡 Thought Process
- Used a `Node` struct to store left and right children.
- Preorder traversal means visiting root → left → right.
- Implemented three separate recursive functions.
- Input parsed by mapping characters A–Z to index 0–25.

## ✅ Review
- Learned to trust recursion's natural flow for tree traversal.
- Need to revisit tree construction problems like BOJ 2263.

🛠️ Setup & Compile

If you're testing locally:

g++ -std=c++17 -O2 main.cpp -o main
./main

🚀 Goals

    Solve problems consistently (at least 1–2 daily)

    Focus on depth-first learning, not just quantity

    Aim for gradual mastery from Silver → Gold → Platinum

Feel free to fork or reference this structure for your own logs!


---
