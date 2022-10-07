// example.go
package main

import (
	"bufio"
	"fmt"
	"main/parser"
	"os"
	"strings"

	"github.com/antlr/antlr4/runtime/Go/antlr"
)

type analizadorListener struct {
	*parser.BaseAnalizadorListener

	stack []int
}

func (l *analizadorListener) push(i int) {
	l.stack = append(l.stack, i)
}

func (l *analizadorListener) pop() int {
	if len(l.stack) < 1 {
		return 0
	}
	// Get the last value from the stack.
	result := l.stack[len(l.stack)-1]
	// Pop the last element from the stack.
	l.stack = l.stack[:len(l.stack)-1]
	return result
}

func Analizar(input string) int {
	// Setup the input
	is := antlr.NewInputStream(input)

	// Create the Lexer
	lexer := parser.NewAnalizadorLexer(is)
	stream := antlr.NewCommonTokenStream(lexer, antlr.TokenDefaultChannel)

	// Create the Parser
	p := parser.NewAnalizadorParser(stream)

	// Finally parse the expression (by walking the tree)
	var listener analizadorListener
	antlr.ParseTreeWalkerDefault.Walk(&listener, p.Start())

	return listener.pop()
}

func main() {
	//crear_disco -tamano=5 -dimensional="m"
	//escribir -nombre="analizador" -direccion="antlr go" -telefono=123 -veces=10
	//mostrar
	finalizar := false
	fmt.Println("MIA - Ejemplo 8, Analizador con AntLR en Go (exit para salir...)")
	reader := bufio.NewReader(os.Stdin)
	//  Ciclo para lectura de multiples comandos
	for !finalizar {
		fmt.Print("<Ejemplo_8>: ")
		comando, _ := reader.ReadString('\n')
		if strings.Contains(comando, "exit") {
			finalizar = true
		} else {
			if comando != "" && comando != "exit\n" {
				Analizar(comando)
			}
		}
	}
}
