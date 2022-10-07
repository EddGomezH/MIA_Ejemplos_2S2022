package funciones

import (
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

func MsgError(err error) {
	fmt.Println("Error: ", err)
}

func ValidarCrearDisco(tam string, dim string) {
	if tam != "" && dim != "" {
		strtam := tam
		strtam = strings.Replace(strtam, "\"", "", 2)
		strtam = strings.Replace(strtam, "\r", "", 1)
		inttam, err := strconv.Atoi(strtam)
		if err != nil {
			MsgError(err)
		} else {
			CrearDisco(inttam, dim)
		}
	} else {
		fmt.Println("Error: Parametros incompletos")
	}
}

func ValidarEscribir(nm string, dir string, tel string, v string) {
	if nm != "" && dir != "" && tel != "" && v != "" {
		inttel, err := strconv.Atoi(tel)
		if err != nil {
			MsgError(err)
		} else {
			intv, err := strconv.Atoi(v)
			if err != nil {
				MsgError(err)
			} else {
				Escribir(nm, dir, inttel, intv)
			}
		}
	} else {
		fmt.Println("Error: Parametros incompletos")
	}
}

// crear_disco -tamaño=numero -dimensional=dimension/"dimension"
func CrearDisco(tam int, dim string) {
	tamano := tam
	dimensional := dim
	tamano_archivo := 0
	limite := 0
	bloque := make([]byte, 1024)

	// Calculo de tamaño del archivo
	if strings.Contains(dimensional, "k") {
		tamano_archivo = tamano
	} else if strings.Contains(dimensional, "m") {
		tamano_archivo = tamano * 1024
	} else if strings.Contains(dimensional, "g") {
		tamano_archivo = tamano * 1024 * 1024
	}

	// Preparacion del bloque a Escribir en archivo
	for j := 0; j < 1024; j++ {
		bloque[j] = 0
	}

	// Creacion, escritura y cierre de archivo
	disco, err := os.Create("Ejemplo8.dk")
	if err != nil {
		MsgError(err)
	}
	for limite < tamano_archivo {
		_, err := disco.Write(bloque)
		if err != nil {
			MsgError(err)
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
func Escribir(name string, dir string, tel int, v int) {
	ejm := ejemplo{}

	nombreejemplo := name
	nombreejemplo = strings.Replace(nombreejemplo, "\"", "", 2)
	nombreejemplo = strings.Replace(nombreejemplo, "\r", "", 1)

	direjemplo := dir
	direjemplo = strings.Replace(direjemplo, "\"", "", 2)
	direjemplo = strings.Replace(direjemplo, "\r", "", 1)

	telejemplo := strconv.Itoa(tel)
	telejemplo = strings.Replace(telejemplo, "\"", "", 2)
	telejemplo = strings.Replace(telejemplo, "\r", "", 1)

	strveces := strconv.Itoa(v)
	strveces = strings.Replace(strveces, "\"", "", 2)
	strveces = strings.Replace(strveces, "\r", "", 1)

	veces, err := strconv.Atoi(strveces)
	if err != nil {
		MsgError(err)
	}

	// Apertura del archivo
	disco, err := os.OpenFile("Ejemplo8.dk", os.O_RDWR, 0660)
	if err != nil {
		MsgError(err)
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
		ejmbyte := StructToBytes(ejm)
		// Cambio de posicion de puntero dentro del archivo
		newpos, err := disco.Seek(int64(k*len(ejmbyte)), os.SEEK_SET)
		if err != nil {
			MsgError(err)
		}
		// Escritura de struct en archivo binario
		_, err = disco.WriteAt(ejmbyte, newpos)
		if err != nil {
			MsgError(err)
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
func Mostrar() {
	fin_archivo := false
	var emptyid [100]byte
	ejm_empty := ejemplo{}
	cont := 0
	// Apertura de archivo
	disco, err := os.OpenFile("Ejemplo8.dk", os.O_RDWR, 0660)
	if err != nil {
		MsgError(err)
	}
	// Calculo del tamano de struct en bytes
	ejm2 := StructToBytes(ejm_empty)
	sstruct := len(ejm2)
	for !fin_archivo {
		// Lectrura de conjunto de bytes en archivo binario
		lectura := make([]byte, sstruct)
		_, err = disco.ReadAt(lectura, int64(sstruct*cont))
		if err != nil && err != io.EOF {
			MsgError(err)
		}
		// Conversion de bytes a struct
		ejm := BytesToStruct(lectura)
		sstruct = len(lectura)
		if err != nil {
			MsgError(err)
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

func StructToBytes(p interface{}) []byte {
	// Codificacion de Struct a []Bytes
	buf := bytes.Buffer{}
	enc := gob.NewEncoder(&buf)
	err := enc.Encode(p)
	if err != nil && err != io.EOF {
		MsgError(err)
	}
	return buf.Bytes()
}

func BytesToStruct(s []byte) ejemplo {
	// Decodificacion de [] Bytes a Struct ejemplo
	p := ejemplo{}
	dec := gob.NewDecoder(bytes.NewReader(s))
	err := dec.Decode(&p)
	if err != nil && err != io.EOF {
		MsgError(err)
	}
	return p
}
