# Lagrange Interpolation with JSON Support

This project demonstrates **Lagrange Polynomial Interpolation** implemented in C++ with optional integration of the [nlohmann/json](https://github.com/nlohmann/json) library for handling JSON input/output.  

It is designed to showcase both mathematical problem-solving and modern C++ development practices.

---

## 📂 Project Structure
.
├── nlhomann/ # Header-only JSON library (nlohmann/json.hpp)
├── README.md # Project documentation
├── input.json # Sample input dataset 1
├── input2.json # Sample input dataset 2
├── lagrange_nojson.cpp # Core interpolation logic in C++
├── lagrange_nojson.exe # Compiled executable (Windows)

yaml
Copy code

---

## ⚡ Features
- Implements **Lagrange Interpolation** to approximate values from given data points.
- Reads input data from **JSON files** using `nlohmann/json`.
- Supports both **manual input** and **file-based input**.
- Clean, modular, and easy-to-read C++ code.
- Portable: header-only JSON library, no external dependencies.

---

## 🚀 Usage
### Compile
```powershell
g++ lagrange_nojson.cpp -o lagrange_nojson.exe
Run with JSON input
powershell
Copy code
./lagrange_nojson.exe input.json
Run with another dataset
powershell
Copy code
./lagrange_nojson.exe input2.json
📊 Example Input (input.json)
json
Copy code
{
  "x": [1, 2, 3],
  "y": [2, 4, 6],
  "interpolate_at": 2.5
}




