# Recreación del juego de la serpiente en conjunto al uso de archivos

Proyecto creado por Alejandro Aleman y Alejandro Alvarez del GR9SW de la Escuela Politécnica Nacional como Proyecto de Finalización de Semestre.

## Enlace de GitHub

<https://github.com/Alejololer/Proyecto-2do-Bimestre>

### Descripción

Este proyecto empezó siendo una recreación sencilla del juego de la serpiente para servir de introducción básica a la programación de videojuegos, eventualmente terminó evolucionando en un proyecto que encapsularía varios temas observados en el aula de clase, como son los vectores y la escritura/lectura en archivos binarios, esto mediante la implementación de una tabla de puntajes altos la cual se actualiza automáticamente y se guarda de forma segura en un archivo .dat para que se evite la modificación no permitida de esta tabla, esto también nos ayuda a acercarnos más a una experiencia de una máquina arcade o "maquinita", esto también ayuda a aumentar el interés por el programa ya que la competitividad es naturaleza humana.

Se hace uso extensivo de los procedimientos gotoxy() para lograr quer funcione tanto la interacción del usuario como la simulación de la GUI que se intenta lograr, otros nuevos procedimientos que se usaron son kbhit() y getch() para leer los inputs del teclado del usuario.