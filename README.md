# 🎯 Mastermind – Console Game in C

Mastermind is a classic code-breaking game where the player must guess a secret 5-digit code made of **distinct digits**.  
This C version includes difficulty levels, colored console output (Windows), scoring, and a special **joker** option.

---

## 🕹️ Features

- Two game modes:
  - **Débutant** – Code is validated to ensure all digits are distinct.
  - **Expert** – Player manually enters the secret code.
- **Feedback after each attempt:**
  - ✔️ *Bien placés* (correct digit & correct position)  
  - ❌ *Mal placés* (correct digit but wrong position)
- **Joker option** (available between attempts 10–17):  
  Reveal one digit of the secret code at the cost of extra attempts.
- **Score saving** into `scores.txt`
- Shows:
  - All saved scores
  - Best score (fewest attempts)

---

## 🔧 Compilation & Execution

### On Windows (MinGW / GCC)
```sh
gcc mastermind.c -o mastermind
./mastermind
