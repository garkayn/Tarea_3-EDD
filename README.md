# Simulador de rutas en grafo — Estructuras de Datos

Programa en C++ que modela una red de calles como un grafo y usa búsqueda en anchura (BFS) para calcular rutas y seleccionar el conductor disponible más cercano.

## Compilación y ejecución

Se requiere un compilador compatible con C++11 o posterior.

```bash
g++ -std=c++17 -O2 tarea3.cpp -o tarea3
./tarea3
```

En Windows, ejecuta `tarea3.exe` después de compilar. El programa lee la red y las ubicaciones iniciales de conductores desde `data2.txt`; ejecuta el programa desde esta carpeta. Luego solicita pares de vértices de origen y destino. Ingresa `-1 -1` para terminar.

## Implementación

El repositorio contiene implementaciones propias de lista, cola y grafo, además del algoritmo para reconstruir rutas. La búsqueda en anchura sobre una lista de adyacencia tiene costo `O(V + E)`; el tiempo total también depende de cuántos conductores se evalúan y de cómo se reconstruyen las rutas.

Trabajo universitario. Conserva los créditos del equipo y el contexto de la tarea al reutilizarlo.
