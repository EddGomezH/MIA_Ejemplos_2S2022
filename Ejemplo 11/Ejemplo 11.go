package main

import (
	"bytes"
	"encoding/base64"
	"encoding/gob"
	"encoding/json"
	"fmt"
	"io"
	"io/ioutil"
	"log"
	"net/http"
	"os"
	"strconv"
	"strings"

	"github.com/rs/cors"
)

type ejemplo = struct {
	Id        [100]byte
	Nombre    [100]byte
	Direccion [100]byte
	Telefono  [100]byte
}

type cmdstruct struct {
	Cmd string `json:"cmd"`
}

func main() {
	fmt.Println("MIA - Ejemplo 10, API Rest GO")

	mux := http.NewServeMux()

	mux.HandleFunc("/analizar", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		var Content cmdstruct
		respuesta := ""
		body, _ := io.ReadAll(r.Body)
		json.Unmarshal(body, &Content)
		respuesta = split_comando(Content.Cmd)
		w.WriteHeader(http.StatusOK)
		w.Write([]byte(`{"result": "` + respuesta + `" }`))
	})

	mux.HandleFunc("/reportes", func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "application/json")
		bytes, _ := ioutil.ReadFile("./disk.png")
		var base64Encoding string
		base64Encoding += "data:image/jpg;base64,"
		base64Encoding += toBase64(bytes)
		w.WriteHeader(http.StatusOK)
		w.Write([]byte(`{"result": "` + base64Encoding + `" }`))
	})

	fmt.Println("Server ON in port 5000")
	handler := cors.Default().Handler(mux)
	log.Fatal(http.ListenAndServe(":5000", handler))
}

func msg_error(err error) {
	fmt.Println("Error: ", err)
}

func split_comando(comando string) string {
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
	return ejecucion_comando(commandArray)
}

func ejecucion_comando(commandArray []string) string {
	respuesta := ""
	// Identificacion de comando y ejecucion
	data := strings.ToLower(commandArray[0])
	if data == "crear_disco" {
		respuesta = crear_disco(commandArray)
	} else if data == "escribir" {
		respuesta = escribir(commandArray)
	} else if data == "mostrar" {
		respuesta = mostrar()
	} else {
		fmt.Println("Comando ingresado no es valido")
	}
	return respuesta
}

// crear_disco -tamaño=numero -dimensional=dimension/"dimension"
func crear_disco(commandArray []string) string {
	respuesta := ""
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
	disco, err := os.Create("Ejemplo10.dk")
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
	respuesta = "Creacion de Disco: Tamaño:" + strconv.Itoa(tamano) + " Dimensional:" + dimensional + "\\n"
	return respuesta
}

// escribir -nombre=nombre/"nombre" -direccion=direccion/"direccion" -telefono=numero -veces=numero
func escribir(commandArray []string) string {
	respuesta := ""
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
	disco, err := os.OpenFile("Ejemplo10.dk", os.O_RDWR, 0660)
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
	respuesta = "Escritura en Disco " + strconv.Itoa(veces) + " veces con los siguientes Datos: \\n"
	respuesta += "Nombre:" + string(bytes.Trim(ejm.Nombre[:], "\x00"))
	respuesta += " Direccion:" + string(bytes.Trim(ejm.Direccion[:], "\x00"))
	respuesta += " Telefono:" + string(bytes.Trim(ejm.Telefono[:], "\x00")) + "\\n"
	return respuesta
}

// mostrar
func mostrar() string {
	respuesta := "Datos registrados en Archivo Binario: \\n"
	fin_archivo := false
	var emptyid [100]byte
	ejm_empty := ejemplo{}
	cont := 0
	// Apertura de archivo
	disco, err := os.OpenFile("Ejemplo10.dk", os.O_RDWR, 0660)
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
			respuesta += "Id: " + string(bytes.Trim(ejm.Id[:], "\x00"))
			respuesta += " Nombre: " + string(bytes.Trim(ejm.Nombre[:], "\x00"))
			respuesta += " Direccion: " + string(bytes.Trim(ejm.Direccion[:], "\x00"))
			respuesta += " Telefono: " + string(bytes.Trim(ejm.Telefono[:], "\x00")) + "\\n"
		}
		cont++
	}
	disco.Close()
	return respuesta
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

func toBase64(b []byte) string {
	return base64.StdEncoding.EncodeToString(b)
}
