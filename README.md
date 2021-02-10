![](https://github.com/Perdomo193/webservice_front/blob/main/static/img/logo_vo.png)

<h2 align="center">Vision Online Prueba Tecnica - Pablo Alejandro Perdomo</h2>

<p align="center"><a href="#"><img src="https://opencv-python-tutroals.readthedocs.io/en/latest/_static/opencv-logo-white.png" width="50px" alt="build status"></img></a><a href="#"><img src="https://upload.wikimedia.org/wikipedia/commons/0/0b/Qt_logo_2016.svg" width="50px" alt="build status"></img></a></p>

<p align="center"><a href="#"><img src="http://runbot.odoo.com/runbot/badge/flat/1/master.svg" alt="build status"></img></a><a href="#"><img src="http://img.shields.io/badge/master-docs-875A7B.svg?style=flat&colorA=8F8F8F" alt="tech doc"></img></a><a href="#"><img src="http://img.shields.io/badge/master-help-875A7B.svg?style=flat&colorA=8F8F8F" alt="help"></img></a><a href="#"><img src="http://img.shields.io/badge/master-nightly-875A7B.svg?style=flat&colorA=8F8F8F" alt="builds"></img></a></p> 

<p align="center">
Servicio TCP para aplicar los algoritmos de opencv, en este caso ya unos definidos. 
</p>

## Compilación
## Configuración libraries
```pro
INCLUDEPATH += -I/usr/include \
        -I/<path>/Qt/5.9.0/5.9/gcc_64/include

LIBS += -L/<paht>/Qt/5.9.0/5.9/gcc_64/lib

LIBS += -L/<paht>/Desktop/github/opencv/build/lib \
    -lopencv_core \        
    -lopencv_imgcodecs \
    -lopencv_imgproc \
    -lopencv_highgui \
``` 
## Comunicacion
### input
```json
{
	"user": "<user create image>",
	"name": "<nama file|ejm: hola>",
	"path": "<path image|ejm: /home/<user>/Desktop>",
	"action": "<opencv function|gray|canny>",
	"extension": "<image extension|jpg|png|jpeg>"
}
``` 
### output
```json
{
        "user": "<user create image>",
        "name": "<nama output file|ejm: hola>",
        "path": "<path output image|ejm: /home/<user>/Desktop>",
        "action": "<opencv function|gray|canny>",
	"extension": "<image output extension|jpg|png|jpeg>"
}
``` 
## Compilar
### QT
[Qt 5.9.0](https://download.qt.io/archive/qt/5.9/5.9.0/qt-opensource-linux-x64-5.9.0.run)

### Opencv
Clonar el repositorio de Opencv
```bash
git clone https://github.com/opencv/opencv.git
```
Paquetes para configurar la instalación.
```bash
sudo pacman -S cmake
sudo pacman -S gcc
```   
Construir opencv con soporte a QT.
```bash
mkdir build
cd build
cmake ../
cmake-gui
```
con **cmake-gui** buscar QT y habilitar, con eso poner los folder de configuracion de cmake **[path]/Qt/5.9.0/5.9/gcc_64/lib/cmake**

## Links Back-end y Front-end

Debe ingresar al `webservice-front` en el siguiente link:

https://github.com/Perdomo193/webservice_front

Debe ingresar al `webservice-backend` en el siguiente link:

https://github.com/Perdomo193/webservice_backend
