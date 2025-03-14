
On **Linux**, you can compile as usual:
```bash
g++ -o anim animation.cpp
```

On **Windows**, you may need a compiler that supports Windows API calls like **MinGW** or **Visual Studio**. For MinGW:
```bash
g++ -o anim.exe animation.cpp -lstdc++ -lgdi32
```

