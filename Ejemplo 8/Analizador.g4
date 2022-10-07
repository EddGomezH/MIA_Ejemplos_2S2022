// Analizador
grammar Analizador;

@parser::header{
import fun "main/funciones"
}

// Tokens
CREARDISCO: 'crear_disco';
ESCRIBIR: 'escribir';
MOSTRAR: 'mostrar';
TAMANO: 'tamano';
DIMENSIONAL: 'dimensional';
NOMBRE: 'nombre';
DIRECCION: 'direccion';
TELEFONO: 'telefono';
VECES: 'veces';
GUION: '-';
IGUAL: '=';
TEXTO: '"'([A-Za-z]|WS|[0-9])*'"';
ENTERO: [0-9]+;

// Grammar
start : comandos EOF;

comandos: CREARDISCO GUION TAMANO IGUAL tam=ENTERO GUION DIMENSIONAL IGUAL dim=TEXTO { fun.ValidarCrearDisco($tam.text,$dim.text) }
        | CREARDISCO GUION DIMENSIONAL IGUAL dim=TEXTO GUION TAMANO IGUAL tam=ENTERO { fun.ValidarCrearDisco($tam.text,$dim.text) }
        | ESCRIBIR GUION NOMBRE IGUAL nm=TEXTO GUION DIRECCION IGUAL dir=TEXTO GUION TELEFONO IGUAL tel=ENTERO GUION VECES IGUAL v=ENTERO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION NOMBRE IGUAL nm=TEXTO GUION DIRECCION IGUAL dir=TEXTO GUION VECES IGUAL v=ENTERO GUION TELEFONO IGUAL tel=ENTERO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) } 
        | ESCRIBIR GUION NOMBRE IGUAL nm=TEXTO GUION TELEFONO IGUAL tel=ENTERO GUION DIRECCION IGUAL dir=TEXTO GUION VECES IGUAL v=ENTERO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION NOMBRE IGUAL nm=TEXTO GUION TELEFONO IGUAL tel=ENTERO GUION VECES IGUAL v=ENTERO GUION DIRECCION IGUAL dir=TEXTO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION NOMBRE IGUAL nm=TEXTO GUION VECES IGUAL v=ENTERO GUION DIRECCION IGUAL dir=TEXTO GUION TELEFONO IGUAL tel=ENTERO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION NOMBRE IGUAL nm=TEXTO GUION VECES IGUAL v=ENTERO GUION TELEFONO IGUAL tel=ENTERO GUION DIRECCION IGUAL dir=TEXTO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION DIRECCION IGUAL dir=TEXTO GUION NOMBRE IGUAL nm=TEXTO GUION TELEFONO IGUAL tel=ENTERO GUION VECES IGUAL v=ENTERO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION DIRECCION IGUAL dir=TEXTO GUION NOMBRE IGUAL nm=TEXTO GUION VECES IGUAL v=ENTERO GUION TELEFONO IGUAL tel=ENTERO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION DIRECCION IGUAL dir=TEXTO GUION TELEFONO IGUAL tel=ENTERO GUION NOMBRE IGUAL nm=TEXTO GUION VECES IGUAL v=ENTERO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION DIRECCION IGUAL dir=TEXTO GUION TELEFONO IGUAL tel=ENTERO GUION VECES IGUAL v=ENTERO GUION NOMBRE IGUAL nm=TEXTO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION DIRECCION IGUAL dir=TEXTO GUION VECES IGUAL v=ENTERO GUION NOMBRE IGUAL nm=TEXTO GUION TELEFONO IGUAL tel=ENTERO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION DIRECCION IGUAL dir=TEXTO GUION VECES IGUAL v=ENTERO GUION TELEFONO IGUAL tel=ENTERO GUION NOMBRE IGUAL nm=TEXTO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION TELEFONO IGUAL tel=ENTERO GUION NOMBRE IGUAL nm=TEXTO GUION DIRECCION IGUAL dir=TEXTO GUION VECES IGUAL v=ENTERO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION TELEFONO IGUAL tel=ENTERO GUION NOMBRE IGUAL nm=TEXTO GUION VECES IGUAL v=ENTERO GUION DIRECCION IGUAL dir=TEXTO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION TELEFONO IGUAL tel=ENTERO GUION DIRECCION IGUAL dir=TEXTO GUION NOMBRE IGUAL nm=TEXTO GUION VECES IGUAL v=ENTERO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION TELEFONO IGUAL tel=ENTERO GUION DIRECCION IGUAL dir=TEXTO GUION VECES IGUAL v=ENTERO GUION NOMBRE IGUAL nm=TEXTO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION TELEFONO IGUAL tel=ENTERO GUION VECES IGUAL v=ENTERO GUION NOMBRE IGUAL nm=TEXTO GUION DIRECCION IGUAL dir=TEXTO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION TELEFONO IGUAL tel=ENTERO GUION VECES IGUAL v=ENTERO GUION DIRECCION IGUAL dir=TEXTO GUION NOMBRE IGUAL nm=TEXTO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION VECES IGUAL v=ENTERO GUION NOMBRE IGUAL nm=TEXTO GUION DIRECCION IGUAL dir=TEXTO GUION TELEFONO IGUAL tel=ENTERO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION VECES IGUAL v=ENTERO GUION NOMBRE IGUAL nm=TEXTO GUION TELEFONO IGUAL tel=ENTERO GUION DIRECCION IGUAL dir=TEXTO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION VECES IGUAL v=ENTERO GUION DIRECCION IGUAL dir=TEXTO GUION NOMBRE IGUAL nm=TEXTO GUION TELEFONO IGUAL tel=ENTERO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION VECES IGUAL v=ENTERO GUION DIRECCION IGUAL dir=TEXTO GUION TELEFONO IGUAL tel=ENTERO GUION NOMBRE IGUAL nm=TEXTO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION VECES IGUAL v=ENTERO GUION TELEFONO IGUAL tel=ENTERO GUION NOMBRE IGUAL nm=TEXTO GUION DIRECCION IGUAL dir=TEXTO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }
        | ESCRIBIR GUION VECES IGUAL v=ENTERO GUION TELEFONO IGUAL tel=ENTERO GUION DIRECCION IGUAL dir=TEXTO GUION NOMBRE IGUAL nm=TEXTO { fun.ValidarEscribir($nm.text,$dir.text,$tel.text,$v.text) }   
        | MOSTRAR { fun.Mostrar() };

COMMENT: '#' ( ~[\r\n]+)?->skip;
WS : [ \t\r\n]+ -> skip ;