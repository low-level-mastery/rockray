# RockRay

### What is this
Rockray is a raycaster engine for pseudo 3d graaphics.

### Build && Run
To build and run this project, make it:
1. Install requirements
2. Clone repository
3. Build by make
4. Run it

`Arch-based Linux`
```
sudo pacman -Syu git make gcc sdl3

git clone https://github.com/low-level-mastery/rockray.git
cd rockray

make
./raycaster
```

---

`Debian-based Linux`
```
sudo apt update && sudo apt upgrade
sudo apt install git make gcc libsdl3

git clone https://github.com/low-level-mastery/rockray.git
cd rockray

make
./raycaster
```

---

`Windows` (powershell!)
```
winget upgrade --all
winget install Git.Git Make.Make LLVM.LLVM
winget install libsdl.libsdl3
winget install Git.Git Make.Make LLVM.LLVM libsdl.libsdl3

git clone https://github.com/low-level-mastery/rockray.git
cd rockray

make
./raycaster
```

### License
License type: MIT
