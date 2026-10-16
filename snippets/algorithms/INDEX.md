# 📖 Índice de Algoritmos — Notebook

> **Última actualización:** 2026-08-27
>
> Cada archivo es autocontenido y compilable con `g++ -std=c++17 -o prog archivo.cpp`.
> Todos usan STL con normalidad. Para estructuras sin STL, ver `snippets/data_structures/`.

---

## Tabla de Contenidos

| # | Archivo | Complejidad | Categoría |
|---|---------|-------------|-----------|
| 1 | [kadane_max_subarray_n.cpp](./kadane_max_subarray_n.cpp) | O(n) | Arrays / DP |
| 2 | [sliding_window_n.cpp](./sliding_window_n.cpp) | O(n) | Arrays / Técnica |
| 3 | [two_pointers_n.cpp](./two_pointers_n.cpp) | O(n) | Arrays / Técnica |
| 4 | [prefix_sum_n.cpp](./prefix_sum_n.cpp) | O(n) build, O(1) query | Arrays / Consultas |
| 5 | [max_difference_n.cpp](./max_difference_n.cpp) | O(n) | Arrays / Greedy |
| 6 | [monotonic_stack_n.cpp](./monotonic_stack_n.cpp) | O(n) | Stack / Técnica |
| 7 | [frequency_majority_n.cpp](./frequency_majority_n.cpp) | O(n) | Arrays / Conteo |
| 8 | [counting_sort_coord_compress_n.cpp](./counting_sort_coord_compress_n.cpp) | O(n+k) / O(n log n) | Sorting / Técnica |
| 9 | [binary_search_logn.cpp](./binary_search_logn.cpp) | O(log n) | Búsqueda |
| 10 | [fast_pow_gcd_logn.cpp](./fast_pow_gcd_logn.cpp) | O(log n) | Matemáticas |
| 11 | [merge_sort_nlogn.cpp](./merge_sort_nlogn.cpp) | O(n log n) | Sorting / D&C |
| 12 | [quick_sort_select_nlogn.cpp](./quick_sort_select_nlogn.cpp) | O(n log n) / O(n) avg | Sorting / Selección |
| 13 | [lis_nlogn.cpp](./lis_nlogn.cpp) | O(n log n) | DP / Subsequence |
| 14 | [sieve_nloglogn.cpp](./sieve_nloglogn.cpp) | O(n log log n) | Matemáticas / Primos |
| 15 | [bfs_dfs_graph_ve.cpp](./bfs_dfs_graph_ve.cpp) | O(V + E) | Grafos |
| 16 | [backtracking_nf.cpp](./backtracking_nf.cpp) | O(n!) / O(2^n) | Backtracking / Brute Force |

---

## 1. Kadane's Algorithm — Máxima Suma de Subarreglo Contiguo

**Archivo:** `kadane_max_subarray_n.cpp`
**Complejidad:** O(n) tiempo, O(1) espacio

### ¿Qué resuelve?
Dado un arreglo de enteros (positivos y negativos), encuentra el subarreglo contiguo cuya suma es máxima.

### ¿Cómo funciona?
Recorre el arreglo manteniendo dos variables:
- `max_ending_here`: suma del mejor subarreglo que termina en la posición actual
- `max_so_far`: mejor suma global encontrada

Si `max_ending_here` se vuelve negativo, se reinicia a 0 (empezar subarreglo nuevo es mejor que cargar una suma negativa).

### Ejemplo
```
Input:  [-2, 1, -3, 4, -1, 2, 1, -5, 4]
Output: 6 (subarreglo [4, -1, 2, 1])
```

### Variantes incluidas
- **Con índices:** retorna también dónde empieza y termina el subarreglo óptimo
- **Subarreglo mínimo:** invertir el signo de todos los elementos y correr Kadane

### Posibles modificaciones
- **Máxima suma circular:** correr Kadane normal + calcular `total_sum - kadane(invertido)`, tomar el máximo
- **2D (máxima submatriz):** fijar dos filas, comprimir a 1D con prefix sums, y aplicar Kadane
- **No vacío vs. vacío:** la versión actual asume subarreglo no vacío; si permites vacío, inicializar `max_so_far = 0`

---

## 2. Sliding Window — Ventana Deslizante

**Archivo:** `sliding_window_n.cpp`
**Complejidad:** O(n) tiempo

### ¿Qué resuelve?
Problemas sobre subarreglos/substrings contiguos donde puedes evaluar eficientemente al "deslizar" una ventana.

### ¿Cómo funciona?

**Ventana Fija (tamaño k):**
1. Calcular la suma/propiedad de los primeros k elementos
2. Por cada nueva posición: sumar el nuevo elemento, restar el que sale

**Ventana Variable:**
1. Expandir `right` para incluir más elementos
2. Contraer `left` cuando la condición se excede
3. Mantener un invariante (ej: "la suma de la ventana es < target")

### Variantes incluidas
- **Fija:** Máxima suma de k elementos contiguos
- **Variable (suma):** Subarreglo más corto con suma ≥ target
- **Variable (string):** Substring más largo sin caracteres repetidos
- **Sliding Window Maximum:** máximo en cada ventana de tamaño k usando deque

### Posibles modificaciones
- **Minimum en ventana:** cambiar la lógica del deque (mantener orden creciente en vez de decreciente)
- **Contar subarreglos con propiedad:** usar la técnica "at most K" minus "at most K-1"
- **K caracteres distintos:** mantener un mapa de frecuencias y contraer cuando `map.size() > k`

---

## 3. Two Pointers — Dos Punteros

**Archivo:** `two_pointers_n.cpp`
**Complejidad:** O(n) tiempo, O(1) espacio

### ¿Qué resuelve?
Problemas sobre arreglos (generalmente ordenados) donde se buscan pares o combinaciones que cumplan una condición.

### ¿Cómo funciona?
Se colocan dos punteros (usualmente `left` al inicio y `right` al final) y se mueven según la comparación con el target:
- Si la suma es muy chica → mover `left` a la derecha
- Si la suma es muy grande → mover `right` a la izquierda

### Variantes incluidas
- **Two Sum Sorted:** par con suma exacta
- **Container With Most Water:** maximizar área entre dos líneas
- **Remove Duplicates:** eliminar duplicados in-place
- **3Sum:** encontrar todas las tripletas que suman target
- **Merge Sorted Arrays**

### Posibles modificaciones
- **4Sum:** agregar otro loop externo a 3Sum
- **Two Sum con arreglo no ordenado:** usar hash map O(n) en vez de sort + two pointers
- **Closest pair:** en vez de buscar exacto, trackear el mínimo `|sum - target|`

---

## 4. Prefix Sum — Suma de Prefijos

**Archivo:** `prefix_sum_n.cpp`
**Complejidad:** O(n) build, O(1) por consulta

### ¿Qué resuelve?
Consultas de suma en rangos `[l, r]` sobre un arreglo estático, y actualizaciones en rango.

### ¿Cómo funciona?
- **Prefix Sum:** `prefix[i] = arr[0] + arr[1] + ... + arr[i-1]` → `sum(l, r) = prefix[r+1] - prefix[l]`
- **Difference Array:** opuesto; permite sumar un valor a todo un rango en O(1), reconstruir en O(n)
- **2D:** extensión a matrices con inclusión-exclusión

### Variantes incluidas
- **Prefix Sum 1D** (struct encapsulado)
- **Difference Array 1D** (actualizaciones en rango O(1))
- **Prefix Sum 2D** (suma de submatrices)

### Posibles modificaciones
- **Prefix XOR:** cambiar `+` por `^` para consultas de XOR en rangos
- **Prefix GCD / max / min:** no se puede restar como con sumas, pero sí usar Sparse Table
- **Difference Array 2D:** para actualizaciones en subrectángulos
- **Offline queries:** si necesitas actualizaciones Y consultas, considerar BIT o Segment Tree

---

## 5. Máxima Diferencia — Buy and Sell Stock

**Archivo:** `max_difference_n.cpp`
**Complejidad:** O(n) tiempo, O(1) espacio

### ¿Qué resuelve?
Dado un arreglo de precios, encontrar el máximo `a[j] - a[i]` donde `j > i` (comprar antes de vender).

### ¿Cómo funciona?
Mantener el mínimo visto hasta ahora (`min_so_far`). Para cada posición, calcular la ganancia si vendiéramos ahí. Actualizar el máximo global.

### Variantes incluidas
- **1 transacción:** con índices de compra/venta
- **Múltiples transacciones:** sumar todas las subidas consecutivas

### Posibles modificaciones
- **Máximo k transacciones:** DP con `dp[k][n]`, O(kn) tiempo
- **Con cooldown:** después de vender, esperar 1 día antes de comprar
- **Con fee:** restar una comisión por cada transacción

---

## 6. Monotonic Stack — Stack Monótono

**Archivo:** `monotonic_stack_n.cpp`
**Complejidad:** O(n) tiempo, O(n) espacio

### ¿Qué resuelve?
Para cada elemento, encontrar el siguiente/anterior elemento mayor/menor en O(n) total.

### ¿Cómo funciona?
Se mantiene un stack con los índices de elementos en orden monótono (creciente o decreciente). Al procesar un nuevo elemento, se sacan del stack todos los que no cumplan la propiedad monótona.

### Variantes incluidas
- **Next Greater Element (NGE)**
- **Next Smaller Element (NSE)**
- **Previous Greater Element (PGE)**
- **Previous Smaller Element (PSE)**
- **Largest Rectangle in Histogram** (usando PSE + NSE)
- **Trapping Rain Water** (usando prefix max)

### Posibles modificaciones
- **Circular array:** procesar el arreglo dos veces (índice `i % n`)
- **Stock Span:** equivalente a Previous Greater Element
- **Maximal Rectangle en matrix 0/1:** por cada fila calcular histograma y aplicar Largest Rectangle

---

## 7. Frequency Count + Majority Element

**Archivo:** `frequency_majority_n.cpp`
**Complejidad:** O(n) tiempo

### ¿Qué resuelve?
Contar frecuencias, ordenar por colores (3-way partition), encontrar elementos mayoritarios.

### ¿Cómo funciona?
- **Dutch National Flag:** 3 punteros (lo, mid, hi) que particionan en 3 zonas
- **Boyer-Moore Voting:** mantener un candidato y un contador; si el contador llega a 0, cambiar candidato

### Variantes incluidas
- **Frequency Count** con map
- **Dutch National Flag** (Sort Colors, 3 valores)
- **Majority > n/2** (Boyer-Moore)
- **Majority > n/3** (Boyer-Moore extendido, 2 candidatos)

### Posibles modificaciones
- **k-way partition:** generalizar Dutch National Flag para k valores
- **Majority > n/k:** mantener k-1 candidatos

---

## 8. Counting Sort + Coordinate Compression

**Archivo:** `counting_sort_coord_compress_n.cpp`
**Complejidad:** O(n+k) / O(n log n)

### ¿Qué resuelve?
- **Counting Sort:** ordenar cuando el rango de valores es acotado
- **Coordinate Compression:** mapear valores grandes a un rango compacto `[0, n)` preservando orden

### ¿Cómo funciona?
- **Counting Sort:** contar frecuencias, luego reconstruir
- **Coordinate Compression:** ordenar + unique + binary search para mapear

### Posibles modificaciones
- **Radix Sort:** aplicar counting sort dígito por dígito (MSD o LSD)
- **Compression con offset:** si necesitas mantener los valores originales, guardar el mapeo inverso

---

## 9. Binary Search — Búsqueda Binaria

**Archivo:** `binary_search_logn.cpp`
**Complejidad:** O(log n)

### ¿Qué resuelve?
Búsqueda eficiente en arreglos ordenados. "Binary Search on the Answer" para optimización.

### ¿Cómo funciona?
Dividir el espacio de búsqueda a la mitad en cada paso según una condición monótona.

### Variantes incluidas
- **Búsqueda clásica** (manual)
- **STL:** `lower_bound`, `upper_bound`, `binary_search`
- **Binary Search on the Answer** (dividir arreglo en k partes minimizando la suma máxima)
- **Binary Search on Doubles** (raíz cuadrada)

### Posibles modificaciones
- **Ternary Search:** para funciones unimodales (encontrar máximo/mínimo)
- **Parallel Binary Search:** resolver múltiples queries de BS simultáneamente
- **BS on the answer + greedy check:** el patrón más común en CF div2 C/D

---

## 10. Fast Power + GCD — Aritmética Modular

**Archivo:** `fast_pow_gcd_logn.cpp`
**Complejidad:** O(log n)

### ¿Qué resuelve?
Exponenciación modular, inverso modular, combinaciones, GCD/LCM.

### ¿Cómo funciona?
- **Fast Power:** elevar al cuadrado repetidamente, multiplicar cuando el bit del exponente es 1
- **Inverso modular:** `a^(p-2) mod p` (Fermat)
- **nCr:** precalcular factoriales e inversos de factoriales

### Variantes incluidas
- **Fast Power** con módulo
- **Inverso modular** (Fermat)
- **nCr mod p** con precálculo de factoriales
- **GCD, LCM, GCD extendido**

### Posibles modificaciones
- **Exponenciación de matrices:** reemplazar la multiplicación escalar por multiplicación de matrices → Fibonacci en O(log n)
- **CRT (Chinese Remainder Theorem):** combinar con GCD extendido
- **nCr con Lucas' theorem:** para n muy grande y p primo pequeño

---

## 11. Merge Sort + Conteo de Inversiones

**Archivo:** `merge_sort_nlogn.cpp`
**Complejidad:** O(n log n) tiempo, O(n) espacio

### ¿Qué resuelve?
Ordenamiento estable y conteo de inversiones (pares `(i,j)` con `i < j` y `arr[i] > arr[j]`).

### ¿Cómo funciona?
Divide el arreglo en mitades, ordena recursivamente, y fusiona. Durante la fusión, cada vez que un elemento de la derecha va antes que uno de la izquierda, se cuentan inversiones.

### Posibles modificaciones
- **Count smaller elements after self:** variante del conteo de inversiones
- **Timsort:** merge sort + insertion sort para subarreglos pequeños (lo que usa Python internamente)

---

## 12. Quick Sort + Quick Select

**Archivo:** `quick_sort_select_nlogn.cpp`
**Complejidad:** O(n log n) promedio / O(n) promedio (select)

### ¿Qué resuelve?
Ordenamiento in-place y selección del k-ésimo menor elemento.

### Variantes incluidas
- **Lomuto partition** (más simple)
- **Hoare partition** (menos swaps en la práctica)
- **Quick Select** (k-ésimo menor)
- **STL:** `nth_element`

### Posibles modificaciones
- **Random pivot:** elegir pivote aleatorio para evitar el peor caso O(n²)
- **3-way partition:** para arreglos con muchos duplicados
- **Intro Sort:** Quick Sort + cambiar a Heap Sort si la recursión es muy profunda (lo que usa `std::sort`)

---

## 13. LIS — Longest Increasing Subsequence

**Archivo:** `lis_nlogn.cpp`
**Complejidad:** O(n log n)

### ¿Qué resuelve?
Encontrar la longitud de la subsecuencia estrictamente creciente más larga.

### ¿Cómo funciona?
Mantiene un arreglo `tails` donde `tails[i]` es el menor valor final posible de una subsecuencia creciente de longitud `i+1`. Para cada nuevo elemento, se busca con binary search dónde colocarlo.

### Variantes incluidas
- **LIS estricto** (`lower_bound`)
- **Con reconstrucción** de la secuencia
- **Longest Non-Decreasing** (`upper_bound` en vez de `lower_bound`)

### Posibles modificaciones
- **Longest Decreasing:** invertir el arreglo
- **LIS 2D (envelopes):** ordenar por una dimensión y aplicar LIS en la otra
- **Dilworth's theorem:** mínima cobertura por cadenas = LIS de la secuencia complementaria

---

## 14. Criba de Eratóstenes

**Archivo:** `sieve_nloglogn.cpp`
**Complejidad:** O(n log log n)

### ¿Qué resuelve?
Encontrar todos los primos hasta n. Factorización rápida.

### Variantes incluidas
- **Criba básica** O(n log log n)
- **Criba lineal** O(n) con SPF (Smallest Prime Factor)
- **Factorización** O(log n) usando SPF
- **Euler Totient** con criba

### Posibles modificaciones
- **Segmented Sieve:** para rangos `[L, R]` con L grande (hasta 10^12) pero R-L pequeño
- **Criba de Möbius:** precalcular la función de Möbius
- **Sum of divisors / Count of divisors:** con variantes de la criba

---

## 15. BFS + DFS — Recorrido de Grafos

**Archivo:** `bfs_dfs_graph_ve.cpp`
**Complejidad:** O(V + E)

### ¿Qué resuelve?
Recorrido de grafos, camino más corto sin pesos, componentes conexos, topological sort, bipartite check.

### Variantes incluidas
- **BFS** con reconstrucción de camino
- **DFS iterativo** y **recursivo**
- **Componentes conexos**
- **Topological Sort** (DFS con detección de ciclo)
- **Bipartite Check** (BFS con coloring)

### Posibles modificaciones
- **0-1 BFS:** para grafos con pesos 0 y 1, usar deque en vez de queue
- **Multi-source BFS:** insertar múltiples fuentes al inicio
- **DFS con tiempos de entrada/salida:** para subtree queries
- **Kosaraju / Tarjan:** para componentes fuertemente conexos en grafos dirigidos
- **Dijkstra:** para camino más corto con pesos (priority queue)

---

## 16. Backtracking — Fuerza Bruta Inteligente

**Archivo:** `backtracking_nf.cpp`
**Complejidad:** O(n!) para permutaciones, O(2^n) para subconjuntos

### ¿Qué resuelve?
Generar todas las permutaciones, subconjuntos, combinaciones, o soluciones que satisfagan restricciones.

### Variantes incluidas
- **Permutaciones** (backtracking manual)
- **Subconjuntos** (backtracking y bitmask)
- **Combinaciones C(n,k)**
- **N-Queens**

### Posibles modificaciones
- **Permutaciones con repetidos:** skip duplicados (ordenar + `if (i > start && arr[i] == arr[i-1]) continue`)
- **Sudoku Solver:** backtracking con constraint propagation
- **Word Search:** backtracking en grilla 2D
- **STL shortcut:** `next_permutation` para generar permutaciones sin backtracking

---

## 🗂️ Algoritmos por Categoría

### Técnicas Generales
- Sliding Window → `sliding_window_n.cpp`
- Two Pointers → `two_pointers_n.cpp`
- Prefix Sum / Difference Array → `prefix_sum_n.cpp`
- Binary Search on the Answer → `binary_search_logn.cpp`
- Coordinate Compression → `counting_sort_coord_compress_n.cpp`

### Sorting
- Merge Sort → `merge_sort_nlogn.cpp`
- Quick Sort → `quick_sort_select_nlogn.cpp`
- Counting Sort → `counting_sort_coord_compress_n.cpp`

### Matemáticas
- Fast Power / Inverse Mod / nCr → `fast_pow_gcd_logn.cpp`
- GCD / LCM / Ext GCD → `fast_pow_gcd_logn.cpp`
- Criba de Eratóstenes / Factorización → `sieve_nloglogn.cpp`

### Grafos
- BFS / DFS / Topo Sort / Bipartite → `bfs_dfs_graph_ve.cpp`

### Stack/Queue
- Monotonic Stack (NGE/NSE/PGE/PSE) → `monotonic_stack_n.cpp`
- Largest Rectangle in Histogram → `monotonic_stack_n.cpp`
- Trapping Rain Water → `monotonic_stack_n.cpp`

### Greedy / Ad-Hoc
- Kadane → `kadane_max_subarray_n.cpp`
- Max Difference / Buy Sell Stock → `max_difference_n.cpp`
- Dutch National Flag → `frequency_majority_n.cpp`
- Boyer-Moore Voting → `frequency_majority_n.cpp`

### DP / Subsequences
- LIS → `lis_nlogn.cpp`

### Brute Force / Complete Search
- Backtracking → `backtracking_nf.cpp`

---

## 📋 Algoritmos Pendientes (TODO)

> Marca con ~~tachado~~ los que vayas agregando.

- [ ] Dijkstra (O(E log V))
- [ ] Bellman-Ford (O(VE))
- [ ] Floyd-Warshall (O(V³))
- [ ] Kruskal / Prim (MST)
- [ ] Union-Find / DSU
- [ ] Segment Tree
- [ ] Binary Indexed Tree (BIT / Fenwick)
- [ ] Sparse Table (RMQ)
- [ ] Trie
- [ ] KMP / Z-Function (string matching)
- [ ] Hashing (Rabin-Karp)
- [ ] DP clásicos (knapsack, LCS, edit distance, coin change)
- [ ] Convex Hull
- [ ] Matrix Exponentiation (Fibonacci O(log n))
