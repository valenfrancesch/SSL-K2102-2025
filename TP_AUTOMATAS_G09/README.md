# TP2 - Autómatas  

---

## 📘 Enunciado  

1. Reconocer constantes enteras **decimales, octales y hexadecimales**, con o sin signo para el caso de los decimales, separadas por el carácter `#`.  
   - Indicar si hubo errores léxicos.  
   - Contar la cantidad de números válidos de cada tipo.  
   - Diagramar y entregar los autómatas y sus matrices de transición.  
   - La cadena debe ingresarse por línea de comando o por archivo.  

2. Implementar una función que reciba un **carácter numérico** y retorne su valor entero.  

3. Ingresar una **cadena que represente una operación aritmética** con enteros decimales y obtener su resultado.  
   - La operación debe soportar los operadores `+`, `-`, `*` y `/`.  
   - Respetar la precedencia de operadores.  
   - Validar la cadena reutilizando las funciones del punto 1.  
   - La cadena debe poder ingresarse por línea de comando o por archivo.  

---

## 💡 Hipótesis de trabajo  

- La longitud máxima de la cadena es de **100 caracteres**, incluyendo el carácter `#`.  
- Los números hexadecimales aceptan tanto `x` como `X`.  
- Se implementaron **tres autómatas independientes** para los tipos decimal, octal y hexadecimal, en lugar de un único autómata general, priorizando la claridad del diseño.  
- La evaluación aritmética no incluye paréntesis, solo operaciones lineales con precedencia estándar.  
- La función `charANumero()` convierte caracteres numéricos a su valor entero usando su código ASCII.  
- El ingreso puede realizarse por teclado o desde el archivo `datos.txt` ubicado en el mismo directorio que el ejecutable.  

---

## ⚙️ Compilación y ejecución  

### Compilar  
```bash
gcc automata.c -o automata
