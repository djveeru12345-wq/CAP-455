# Food Truck Location and Menu Planner — CA2

**Course:** CAP455 — Object-Oriented Programming using C++  
**Phase:** CA2 - Persist & Search (Unit III, 14 days)

## Overview
Default, parameterized and copy constructors; destructor; fixed-size binary records in foodtruck.dat; Add, Display, Search (seekg/tellg) and Update (seekp). The data file is compiler/platform-layout dependent.

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
- `main.cpp`: full CA2 C++ source code
- `.github/workflows/build.yml`: automated build check
- `.gitignore`: excludes generated executables
- `foodtruck.dat`: sample binary records (keep in the working directory when running)
- `test_evidence.txt`: recorded CA2 tests
- `CA2_Project_Report.docx`: editable CA2 report
- `CA2_Proposal.pdf`: CA2 proposal

**Note:** `foodtruck.dat` uses a fixed-size C++ structure and may not be portable across compilers/platforms. If the supplied file is incompatible, rename it before testing and let the program create a new file by adding records.
