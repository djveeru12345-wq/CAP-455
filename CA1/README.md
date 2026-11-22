# Food Truck Location and Menu Planner — CA1

**Course:** CAP455 — Object-Oriented Programming using C++  
**Phase:** CA1 - Design & Create (Units I-II, 7 days)

## Overview
In-memory Create and Read using FoodTruck arr[50], duplicate-ID checking, static/inline/friend functions, object pointers and this pointer. Records are lost when the program closes.

## Requirements
- C++17-compatible compiler such as MinGW g++ on Windows or g++ on Linux
- Terminal or VS Code

## Build and run on Windows (PowerShell)
Open the terminal in this repository's folder:

```powershell
g++ -std=c++17 main.cpp -o FoodTruck.exe
.\FoodTruck.exe
```

## Build and run on Linux/macOS
```bash
g++ -std=c++17 main.cpp -o FoodTruck
./FoodTruck
```

## GitHub Actions
The workflow at `.github/workflows/build.yml` automatically compiles the code on pushes and pull requests. Check the **Actions** tab to see whether the build succeeds. This workflow verifies compilation; it does not host an interactive console program.

## Files
- `main.cpp`: full CA1 C++ source code
- `.github/workflows/build.yml`: automated build check
- `.gitignore`: excludes generated executables
- `CA1_Project_Report.pdf`: original CA1 proposal and code documentation
