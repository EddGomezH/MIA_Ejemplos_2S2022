# Instalacion y Uso de la herramienta

## 1) Instalacion de GO

- Descargar go https://go.dev/doc/install
- Se accede a Descargas y se descomprime el archivo mediante el siguiente comando <b>sudo tar -C /usr/local -xvf go1.16.7.linux-amd64.tar.gz</b>
- <b>sudo nano ~/.profile</b>
- <b>go version</b>

## 2) Instalacion de AntLR

- Tener instalada una version de Java
- <b>sudo apt-get install antlr4</b>

## 3) Configuracion inicial y dependencias

- <b>go mod init main</b>
- <b>go get github.com/antlr/antlr4/runtime/Go/antlr@4.7.2</b>
- <b>wget http://www.antlr.org/download/antlr-4.7-complete.jar</b>

## 4) Construccion del archivo.g4

## 5) Compilacion de archivo.g4

- java -jar antlr-4.7-complete.jar -Dlanguage=Go -o parser Analizador.g4