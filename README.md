# Gestor de incidencias

Aplicación de consola en C para registrar y gestionar incidencias técnicas: alta,
listado, cambio de estado y recuento. Proyecto personal escrito para practicar
estructuras, funciones y paso de parámetros por referencia.

## Funcionalidades

- **Alta de incidencias** con identificador, departamento y prioridad (alta, media, baja).
- **Control de identificadores duplicados**: rechaza un ID que ya exista.
- **Listado completo** con el estado de cada incidencia.
- **Cambio de estado** entre abierta y cerrada, buscando por identificador.
- **Resumen** con el total de incidencias y el recuento de abiertas y cerradas.
- **Filtro de incidencias abiertas**.
- **Validación de todas las entradas**: si el usuario escribe algo que no es un número,
  el programa lo detecta, limpia el búfer de entrada y vuelve a preguntar.

## Compilación y ejecución

Requiere únicamente un compilador de C. No usa librerías externas.

```bash
gcc -Wall -Wextra -std=c11 -pedantic gestor_incidencias.c -o gestor
./gestor
```

En Windows:

```cmd
gcc -Wall -Wextra -std=c11 -pedantic gestor_incidencias.c -o gestor.exe
gestor.exe
```

Compila sin ningún aviso con las opciones anteriores.

## Ejemplo de uso

```
Bienvenid@ al gestor de incidencias
Elige un numero para acceder
1. Introducir incidencia
2. Listado de la incidencia
3. Modificar estado de la incidencia
4. Resumen de incidencias totales
5. Incidencias abiertas
6. Salir
> 1

Ingrese el id de la incidencia
> 101
Introduce el departamento:
> Sistemas
Introduce el nivel de prioridad que desea aplicar a la incidencia
1-ALTA, 2-MEDIA, 3-BAJA
> 1

Incidencia numero 101 insertada correctamente
```

Y el listado:

```
-ID Incidencia: 101
-Departamento: Sistemas
-Prioridad: 1
Estado incidencia: ABIERTA
```

## Decisiones técnicas

**Estructura de datos.** Las incidencias se guardan en un array de `struct Incidencia`
de tamaño fijo (50). Se pasa a las funciones junto con un contador `total`, que viaja
por referencia (`int *total`) porque las funciones que dan de alta necesitan
modificarlo y que el cambio se vea desde `main`.

**Inicialización explícita de los campos.** Antes de pedir cada dato, los campos del
registro se ponen a cero. En C, un array local no se inicializa automáticamente:
contiene lo que hubiera antes en esa zona de memoria. Sin esa inicialización, una
lectura fallida dejaba el campo con un valor basura que la validación daba por bueno.

**Validación de la entrada.** `scanf` devuelve el número de datos leídos
correctamente. Cuando no consigue leer un entero, no modifica la variable y deja el
texto en el búfer de entrada, lo que provoca que las siguientes lecturas fallen en
cadena. El programa comprueba ese valor de retorno y, si falla, vacía el búfer antes
de volver a preguntar:

```c
if (scanf("%d", &destino) != 1) {
    destino = 0;
    while ((basura = getchar()) != '\n' && basura != EOF) { }
}
```

**Valor centinela fuera del rango válido.** El valor que se asigna cuando la lectura
falla tiene que ser uno que la propia validación rechace. Para el identificador y la
prioridad sirve el 0; para el estado no, porque 0 significa ABIERTA y es un valor
legítimo, así que ahí se usa -1.

**Lectura del departamento con `fgets`.** Se usa `fgets` en lugar de `scanf("%s")`
para poder limitar el número de caracteres leídos y evitar un desbordamiento del
array. El tamaño se pasa con `sizeof` sobre el propio campo, de forma que si el array
cambia de tamaño el límite se ajusta solo.

## Mejoras pendientes

- Persistencia en fichero: ahora las incidencias se pierden al cerrar el programa.
- Campo de descripción de texto en cada incidencia.
- Búsqueda y filtrado por departamento o por prioridad.
- Reserva dinámica de memoria para no depender de un máximo fijo de incidencias.

