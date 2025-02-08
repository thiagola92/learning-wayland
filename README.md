# learning-wayland

## install
Install Wayland client and Wayland headers file (`.h` files):  
```
sudo apt install libwayland-client0 libwayland-dev
```

## compiling
```
gcc -o main main.c -lwayland-client
```

## references
- https://bugaevc.gitbooks.io/writing-wayland-clients/content/
- https://wayland-book.com/introduction/package.html