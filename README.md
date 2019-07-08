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
### Autores
- Angel J. España B.
- Adriana P. Daboin M.