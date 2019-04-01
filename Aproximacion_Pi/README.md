
## Aproximación Estadística de Pi

#### Variables de Entrada
El algoritmo como tal no recibe variables de entrada. Pero se define con anterioridad la cantidad de puntos que serán
utilizados para la aproximación.

#### Explicación de Algoritmo
Se planea una cuadrícula de área 1 en donde se dispone un círculo de radio 0.5. Siguiente a eso se generan puntos de
forma aleatoria, donde los valores de X y Y estarán entre 0 y 1.

Para cada uno de los puntos, se calcula la distancia hacia el origen del plano (0,0) a través de la fórmula:

f = (x * x) + (y * y)

Si el valor de f es menor o igual a 1, se dice que el punto se encuentra dentro del círculo, y se incrementa el contador
de puntos dentro del círculo, en caso contrario no. Indiferente de eso siempre se incrementará el contador de puntos
dentro del cuadrado. 

Durante cada iteración se procede a realizar el cálculo aproximado del valor de Pi con la fórmula:

Pi = (4 * puntos_dentro_círculo) / puntos_totales

A medida que más puntos vayan siendo desplegados en el plano, el valor de Pi se irá acercando al valor real.
