
On **Linux**, you can compile as usual:
```bash
g++ -o anim anim.cpp
```

On **Windows**, you may need a compiler that supports Windows API calls like **MinGW** or **Visual Studio**. For MinGW:
```bash
g++ -o anim.exe anim.cpp -lstdc++ -lgdi32
```

