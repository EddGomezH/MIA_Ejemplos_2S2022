package main

import (
	"bufio"
	"bytes"
	"encoding/gob"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"
)

type ejemplo = struct {
	Id        [100]byte
	Nombre    [100]byte
	Direccion [100]byte
	Telefono  [100]byte
}

func main() {
	analizar()
}

func msg_error(err error) {
	fmt.Println("Error: ", err)
}

func analizar() {
	finalizar := false
	fmt.Println("MIA - Ejemplo 7, Analizador a Mano con Go (exit para salir...)")
	reader := bufio.NewReader(os.Stdin)
	//  Ciclo para lectura de multiples comandos
	for !finalizar {
		fmt.Print("<Ejemplo_7>: ")
		comando, _ := reader.ReadString('\n')
		if strings.Contains(comando, "exit") {
			finalizar = true
		} else {
			if comando != "" && comando != "exit\n" {
				//  Separacion de comando y parametros
				split_comando(comando)
			}
		}
	}
}

func split_comando(comando string) {
	var commandArray []string
	// Eliminacion de saltos de linea
	comando = strings.Replace(comando, "\n", "", 1)
	comando = strings.Replace(comando, "\r", "", 1)
	// Guardado de parametros
	if strings.Contains(comando, "mostrar") {
		commandArray = append(commandArray, comando)
	} else {
		commandArray = strings.Split(comando, " ")
	}
	// Ejecicion de comando leido
	ejecucion_comando(commandArray)
}

func ejecucion_comando(commandArray []string) {
	// Identificacion de comando y ejecucion
	data := strings.ToLower(commandArray[0])
	if data == "crear_disco" {
		crear_disco(commandArray)
	} else if data == "escribir" {
		escribir(commandArray)
	} else if data == "mostrar" {
		mostrar()
	} else {
		fmt.Println("Comando ingresado no es valido")
	}
}

// crear_disco -tamaño=numero -dimensional=dimension/"dimension"
func crear_disco(commandArray []string) {
	tamano := 0
	dimensional := ""
	tamano_archivo := 0
	limite := 0
	bloque := make([]byte, 1024)

	// Lectura de parametros del comando
	for i := 0; i < len(commandArray); i++ {
		data := strings.ToLower(commandArray[i])
		if strings.Contains(data, "-tamaño=") {
			strtam := strings.Replace(data, "-tamaño=", "", 1)
			strtam = strings.Replace(strtam, "\"", "", 2)
			strtam = strings.Replace(strtam, "\r", "", 1)
			tamano2, err := strconv.Atoi(strtam)
			tamano = tamano2
			if err != nil {
				msg_error(err)
			}
		} else if strings.Contains(data, "-dimensional=") {
			dimensional = strings.Replace(data, "-dimensional=", "", 1)
			dimensional = strings.Replace(dimensional, "\"", "", 2)
		}
	}

	// Calculo de tamaño del archivo
	if strings.Contains(dimensional, "k") {
		tamano_archivo = tamano
	} else if strings.Contains(dimensional, "m") {
		tamano_archivo = tamano * 1024
	} else if strings.Contains(dimensional, "g") {
		tamano_archivo = tamano * 1024 * 1024
	}

	// Preparacion del bloque a escribir en archivo
	for j := 0; j < 1024; j++ {
		bloque[j] = 0
	}

	// Creacion, escritura y cierre de archivo
	disco, err := os.Create("Ejemplo7.dk")
	if err != nil {
		msg_error(err)
	}
	for limite < tamano_archivo {
		_, err := disco.Write(bloque)
		if err != nil {
			msg_error(err)
		}
		limite++
	}
	disco.Close()

	// Resumen de accion realizada
	fmt.Print("Creacion de Disco:")
	fmt.Print(" Tamaño: ")
	fmt.Print(tamano)
	fmt.Print(" Dimensional: ")
	fmt.Println(dimensional)
}

// escribir -nombre=nombre/"nombre" -direccion=direccion/"direccion" -telefono=numero -veces=numero
func escribir(commandArray []string) {
	veces := 0
	straux := ""
	ejm := ejemplo{}
	nombreejemplo := ""
	direjemplo := ""
	telejemplo := ""
	// Lectura de parametros del comando
	for i := 0; i < len(commandArray); i++ {
		data := strings.ToLower(commandArray[i])
		if strings.Contains(data, "-nombre=") {
			straux = strings.Replace(data, "-nombre=", "", 1)
			straux = strings.Replace(straux, "\"", "", 2)
			straux = strings.Replace(straux, "\r", "", 1)
			nombreejemplo = straux
		} else if strings.Contains(data, "-direccion=") {
			straux = strings.Replace(data, "-direccion=", "", 1)
			straux = strings.Replace(straux, "\"", "", 2)
			straux = strings.Replace(straux, "\r", "", 1)
			direjemplo = straux
		} else if strings.Contains(data, "-telefono=") {
			straux = strings.Replace(data, "-telefono=", "", 1)
			straux = strings.Replace(straux, "\"", "", 2)
			straux = strings.Replace(straux, "\r", "", 1)
			_, err := strconv.Atoi(straux)
			if err != nil {
				telejemplo = "0"
				msg_error(err)
			} else {
				telejemplo = straux
			}
		} else if strings.Contains(data, "-veces=") {
			straux = strings.Replace(data, "-veces=", "", 1)
			straux = strings.Replace(straux, "\"", "", 2)
			straux = strings.Replace(straux, "\r", "", 1)
			intveces, err := strconv.Atoi(straux)
			if err != nil {
				veces = 0
				msg_error(err)
			} else {
				veces = intveces
			}
		}
	}

	// Apertura del archivo
	disco, err := os.OpenFile("Ejemplo7.dk", os.O_RDWR, 0660)
	if err != nil {
		msg_error(err)
	}

	// Escritura en el archivo utilizando SEEK_SET
	nnombre := ""
	ndir := ""
	for k := 0; k < veces; k++ {
		index := k + 1
		nnombre = string(nombreejemplo) + " " + strconv.Itoa(index)
		ndir = string(direjemplo) + " " + strconv.Itoa(index)
		ntel, _ := strconv.ParseInt(telejemplo, 10, 32)
		ntel = ntel + int64(index)*int64(index)
		copy(ejm.Id[:], strconv.Itoa(index))
		copy(ejm.Nombre[:], nnombre)
		copy(ejm.Direccion[:], ndir)
		copy(ejm.Telefono[:], strconv.Itoa(int(ntel)))
		// Conversion de struct a bytes
		ejmbyte := struct_to_bytes(ejm)
		// Cambio de posicion de puntero dentro del archivo
		newpos, err := disco.Seek(int64(k*len(ejmbyte)), os.SEEK_SET)
		if err != nil {
			msg_error(err)
		}
		// Escritura de struct en archivo binario
		_, err = disco.WriteAt(ejmbyte, newpos)
		if err != nil {
			msg_error(err)
		}
	}
	disco.Close()

	// Resumen de accion realizada
	fmt.Print("Escritura en Disco de Struct con los siguientes datos (")
	fmt.Print(veces)
	fmt.Print(" veces):")
	fmt.Print(" Nombre: ")
	fmt.Print(string(ejm.Nombre[:]))
	fmt.Print(" Direccion: ")
	fmt.Print(string(ejm.Direccion[:]))
	fmt.Print(" Telefono: ")
	fmt.Println(string(ejm.Telefono[:]))
}

// mostrar
func mostrar() {
	fin_archivo := false
	var emptyid [100]byte
	ejm_empty := ejemplo{}
	cont := 0
	// Apertura de archivo
	disco, err := os.OpenFile("Ejemplo7.dk", os.O_RDWR, 0660)
	if err != nil {
		msg_error(err)
	}
	// Calculo del tamano de struct en bytes
	ejm2 := struct_to_bytes(ejm_empty)
	sstruct := len(ejm2)
	for !fin_archivo {
		// Lectrura de conjunto de bytes en archivo binario
		lectura := make([]byte, sstruct)
		_, err = disco.ReadAt(lectura, int64(sstruct*cont))
		if err != nil && err != io.EOF {
			msg_error(err)
		}
		// Conversion de bytes a struct
		ejm := bytes_to_struct(lectura)
		sstruct = len(lectura)
		if err != nil {
			msg_error(err)
		}
		if ejm.Id == emptyid {
			fin_archivo = true
		} else {
			fmt.Print(" Id: ")
			fmt.Print(string(ejm.Id[:]))
			fmt.Print(" Nombre: ")
			fmt.Print(string(ejm.Nombre[:]))
			fmt.Print(" Direccion: ")
			fmt.Print(string(ejm.Direccion[:]))
			fmt.Print(" Telefono: ")
			fmt.Println(string(ejm.Telefono[:]))
		}
		cont++
	}
	disco.Close()
}

func struct_to_bytes(p interface{}) []byte {
	// Codificacion de Struct a []Bytes
	buf := bytes.Buffer{}
	enc := gob.NewEncoder(&buf)
	err := enc.Encode(p)
	if err != nil && err != io.EOF {
		msg_error(err)
	}
	return buf.Bytes()
}

func bytes_to_struct(s []byte) ejemplo {
	// Decodificacion de [] Bytes a Struct ejemplo
	p := ejemplo{}
	dec := gob.NewDecoder(bytes.NewReader(s))
	err := dec.Decode(&p)
	if err != nil && err != io.EOF {
		msg_error(err)
	}
	return p
}
