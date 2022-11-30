# cin - CLI interpreter for C


## How it works

All inputs given are stored and added to a file in /tmp directory. It is then compiled by gcc. If input results in error, that line is removed. The program currently supports C code (with macros) written in one line.

## How to install

cin uses the following packages:
```
gcc
```

To run cin:
```
git clone https://github.com/Carricossauro/cin --branch v1.2.2
cd cin
make all
./bin/cin
```

To install cin system wide:
```
git clone https://github.com/Carricossauro/cin --branch v1.2.2
cd cin
make all
sudo cp bin/cin /bin/cin
cd ..
rm -rf cin
```

To start cin:
```
cin
```

To remove cin system wide:
```
sudo rm -f /bin/cin
```

## For developers (for me basically)

To install git hook for naming convention:
```
cp git/hooks/pre-commit .git/hooks/pre-commit
```

Naming convention:
```
[keyword]/[Issue number]-[branch name]
```

Keywords:
```
feature
bugfix
doc
dev
code
```

Example:
```
feature/29-add-macro-support
```
