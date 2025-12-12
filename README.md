# Tetris en C++

Implementación del juego clásico de Tetris en C++ con interfaz gráfica usando SDL2.

## Descripción

Este es mi proyecto de Tetris desarrollado en C++.  El juego incluye dos modos de juego, sistema de puntuaciones, música y 20 niveles de dificultad. 

## Características

- Modo de juego normal
- Modo test para probar secuencias específicas
- Sistema de puntuaciones con historial
- 20 niveles de dificultad
- Música y efectos de sonido
- Pausa durante la partida

## Controles

- Flechas izquierda/derecha:  mover pieza
- Flecha arriba:  girar en sentido horario
- Flecha abajo: girar en sentido antihorario
- W: bajar pieza
- Espacio: bajar pieza rápidamente
- P: pausar
- E: mostrar tablero al finalizar
- ESC: salir al menú

## Sistema de puntuación

- Colocar figura: 10 puntos
- Eliminar 1 fila: 100 puntos
- Eliminar 2 filas: 150 puntos
- Eliminar 3 filas: 175 puntos
- Eliminar 4 filas: 200 puntos

Empiezas en el nivel 1 y subes de nivel cada 1000 puntos.  Si llegas al nivel 20 ganas. 


## Estructura

El proyecto contiene las siguientes clases principales:
- `Tetris`: clase principal del juego
- `Partida`: gestiona cada partida
- `Tauler`: gestiona el tablero
- `Figura`: representa las piezas
- `GraphicManager`: maneja los gráficos
- `LlistaJugadors`: sistema de puntuaciones

## Archivos necesarios

El juego necesita una carpeta `./data/Games/` con:
- Archivos de audio
- `PuntuacionsHistoriques.txt` para guardar puntuaciones
- Archivos de configuración para el modo test

## Modos de juego

**Modo normal**: el modo clásico donde las piezas aparecen aleatoriamente y la velocidad aumenta progresivamente.

**Modo test**: permite cargar partidas desde archivos para probar situaciones específicas. 
