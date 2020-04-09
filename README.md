# GEARSystem


This repository is a collaboration of UFPE Maracatronics and USP-CAASO Warthog. It contains the software developed by Warthog Robotics Team of USP-CAASO University.

Their repository can be found 
[here](https://warthog.assembla.com/spaces/warthog-dia/wiki)

## Instaling

```bash
git clone https://github.com/maracatronics/GEARSystem.git
cd GEARSystem
rm -r branches
rm -r tags

 
cd trunk
sh InstallUbuntuDependencies.sh

sh build/corba_skeletons.sh
qmake install_path=/usr/lib/
make -j4
sudo sh install.sh
```

![Warthog Robotics](img/warthog.png?raw=true "Warthog Robotics")

![Armorial Project](img/armorialproject.png?raw=true "Maracatronics Armorial Project")
![Maracatronics](img/maracatronics.png?raw=true "Maracatronics")
