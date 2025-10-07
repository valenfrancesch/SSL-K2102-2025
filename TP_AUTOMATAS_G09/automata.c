#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

// Punto 1 -----

int esLetraValida(char c)
{
    c = toupper(c);
    return (c >= 'A' && c <= 'F');
}

int columnaHexa(int c)
{
    if (c == '0') return 0;
    if (c == 'x' || c == 'X') return 1;
    if ((isdigit(c) && c != '0') || esLetraValida(c)) return 2;
    return 3;
}

int esHexa(char *cadena)
{
    static int tt[6][4] = {
        {1, 5, 5, 5},
        {5, 2, 5, 5},
        {4, 5, 3, 5},
        {3, 5, 3, 5},
        {5, 5, 5, 5},
        {5, 5, 5, 5}
    };

    int e = 0, i = 0, c = cadena[i];
    while (c != '\0' && e != 5)
    {
        e = tt[e][columnaHexa(c)];
        i++;
        c = cadena[i];
    }

    return (e == 3 || e == 4);
}

int columnaOctal(int c)
{
    if (isdigit(c) && c != '0') return 1;
    if (c == '0') return 0;
    return 2;
}

int esOctal(char *cadena)
{
    static int tt[5][3] = {
        {1, 4, 4},
        {3, 2, 4},
        {2, 2, 4},
        {4, 4, 4},
        {4, 4, 4}
    };

    int e = 0, i = 0, c = cadena[i];
    while (c != '\0' && e != 4)
    {
        e = tt[e][columnaOctal(c)];
        i++;
        c = cadena[i];
    }

    return (e == 2 || e == 3);
}

int columnaDecimal(int c)
{
    if (c == '0') return 0;
    if (isdigit(c) && c != '0') return 1;
    if (c == '+') return 2;
    if (c == '-') return 3;
    return 4;
}

int esDecimal(char *cadena)
{
    static int tt[5][5] = {
        {3, 2, 1, 1, 4},
        {3, 2, 4, 4, 4},
        {2, 2, 4, 4, 4},
        {4, 4, 4, 4, 4},
        {4, 4, 4, 4, 4}
    };

    int e = 0, i = 0, c = cadena[i];
    while (c != '\0' && e != 4)
    {
        e = tt[e][columnaDecimal(c)];
        i++;
        c = cadena[i];
    }

    return (e == 2 || e == 3);
}

void verificar(char *cadena)
{
    int contador[3] = {0};
    int i = 0;
    int c = cadena[i];

    while (c != '\0')
    {
        char aux[MAX] = {0};
        int j = 0;
        while (c != '#' && c != '\0')
        {
            aux[j++] = cadena[i++];
            c = cadena[i];
        }
        aux[j] = '\0';

        if (esDecimal(aux))
            contador[0]++;
        else if (esOctal(aux))
            contador[1]++;
        else if (esHexa(aux))
            contador[2]++;
        else
            printf("El valor %s no aplica a ningún caso\n", aux);

        if (c == '#') { i++; c = cadena[i]; }
    }

    printf("Cantidad de decimales: %d\n", contador[0]);
    printf("Cantidad de octales: %d\n", contador[1]);
    printf("Cantidad de hexadecimales: %d\n", contador[2]);
}

// Punto 2 -----
int charANumero(char c)
{
    return c - '0';
}

// Punto 3 -----

int esOperador(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int esCadenaValidaOperacion(const char *cadena)
{
    int estado = 0; // 0 = espero número, 1 = espero operador
    int i = 0;

    while (cadena[i] != '\0') {
        if (estado == 0) {
            char num[MAX];
            int j = 0;
            while (cadena[i] != '\0' && !esOperador(cadena[i])){
                num[j] = cadena[i];
                j++;
                i++;
            }
            num[j] = '\0';

            if (j == 0 || !esDecimal(num)){
                return 0; // Número no válido
            }

            estado = 1;
        } else {
            char c = cadena[i];
            if (esOperador(c) == 1) {
                estado = 0;
                i++;
            } else {
                return 0; // Carácter no válido
            }
        }
    }

    return (estado == 1); // Termina correctamente en número
}


int evaluarOperacion(const char *cadena)
{
    int numeros[MAX];
    char operadores[MAX];
    int nNum = 0, nOp = 0;
    int i = 0;

    while (cadena[i] != '\0') {
       
        char numStr[MAX];
        int j = 0;
        while (cadena[i] != '\0' && !esOperador(cadena[i])) {
            numStr[j] = cadena[i];
                j++;
                i++;
        }
        numStr[j] = '\0';

        if (j > 0 && esDecimal(numStr))
        {
            int num = 0;
            for (int k = 0; numStr[k] != '\0'; k++)
            {
                num = num * 10 + charANumero(numStr[k]);
            }
            numeros[nNum] = num;
            nNum++;
        }

        if (esOperador(cadena[i])){
            operadores[nOp] = cadena[i];
            nOp++;
            i++;
        }
    }

    // 1. Resolver multiplicaciones y divisiones
    for (int i = 0; i < nOp; i++)
    {
        if (operadores[i] == '*' || operadores[i] == '/')
        {
            int a = numeros[i];
            int b = numeros[i + 1];
            int res = (operadores[i] == '*') ? a * b : a / b;
            numeros[i] = res;

            for (int j = i + 1; j < nNum - 1; j++){
                numeros[j] = numeros[j + 1];
            }
                
            for (int j = i; j < nOp - 1; j++){
                operadores[j] = operadores[j + 1];
            }
            
            nNum--;
            nOp--;
            i--;
        }
    }

    // 2. Resolver sumas y restas
    int resultado = numeros[0];
    for (int i = 0; i < nOp; i++)
    {
        if (operadores[i] == '+'){
            resultado += numeros[i + 1];
        }else{
            resultado -= numeros[i + 1];
        }
    }

    return resultado;
}


int main()
{
    char cadena[MAX];
    int opcion;

    printf("Seleccione el modo:\n");
    printf("1. Reconocer constantes enteras (Punto 1)\n");
    printf("2. Evaluar operación aritmética (Punto 3)\n");
    printf("Opción: ");
    scanf("%d", &opcion);
    getchar();

    if (opcion == 1)
    {
        int fuente;
        printf("Fuente de la cadena:\n");
        printf("1. Ingresar por teclado\n");
        printf("2. Leer desde archivo\n");
        printf("Opción: ");
        scanf("%d", &fuente);
        getchar();

        if (fuente == 1)
        {
            printf("Ingrese la cadena (números separados por #):\n");
            scanf("%99s", cadena);
            verificar(cadena);
        }
        else if (fuente == 2)
        {
            FILE *archivo = fopen("datos.txt", "r");
            if (!archivo)
            {
                printf("No se pudo abrir el archivo.\n");
                return 1;
            }
            if (fscanf(archivo, "%99s", cadena) == 1)
            {
                printf("Cadena leída: %s\n", cadena);
                verificar(cadena);
            }
            else
            {
                printf("El archivo está vacío.\n");
            }
            fclose(archivo);
        }
        else
        {
            printf("Opción inválida.\n");
        }
    }
    else if (opcion == 2)
    {
        printf("Ingrese la expresión aritmética (ej: 3+4*7+3-8/4):\n");
        scanf("%99s", cadena);

        if (!esCadenaValidaOperacion(cadena))
        {
            printf("Error: la expresión no es válida.\n");
            return 1;
        }

        int resultado = evaluarOperacion(cadena);
        printf("Resultado: %d\n", resultado);
    }
    else
    {
        printf("Opción inválida.\n");
    }

    printf("Presione ENTER para salir.\n");
    getchar();
    return 0;
}
