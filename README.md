# SO-B2018 - Repositorio de proyectos de Sistemas Operativos
Como requisito y aprendizaje necesarios de la asignatura 'Sistemas Operativos' de la Universidad de Los Andes, se realizó una simulación de un cruce de avenidas (4 vías) con autos generados aleatoriamente de acuerdo con una distribución de probabilidad Poisson.

Cada vía genera un número aleatorio de autos que son recibidos por la vía opuesta. 

## Cola de mensajes
Todos los archivos son compilados con make.
En una terminal, se ejecuta el programa 'server.out'.
En otras 4 terminales, se debe ejecutar un programa 'client\*.out', donde (\*) indica el número correspondiente al programa (1, 2, 3 o 4).

La manera de ejecutar cada programa cliente es:

./client\*.out &lt;lambda&gt;

Donde &lt;lambda&gt; es un número entero mayor que cero que representa la tasa promedio de llegadas de autos según la distribución Poisson.

Para terminar la ejecución, desde el servidor se presiona **Ctrl+C**. Esto activa la señal correspondiente y elimina las colas de mensaje.

## Semáforos
En este caso se hace uso de memoria compartida y un semáforo para controlar el acceso a las secciones críticas del programa.

Se tiene un programa que actúa de servidor, cuya función principal es crear e inicializar el espacio de memoria compartida y el semáforo. Éste entra en un bucle infinito que puede romperse con **Ctrl+C**, liberando así todos los recursos y cerrando uno a uno los procesos activos.

La manera de ejecutar cada programa cliente es:

./client\*.out &lt;lambda&gt;

Donde &lt;lambda&gt; es un número entero mayor que cero que representa la tasa promedio de llegadas de autos según la distribución Poisson.

### Autores
- Angel J. España B.
- Adriana P. Daboin M.