# Solucion de la recurrencia

$T(n) = \sqrt{n}\ T(\sqrt{n}) + n$

## Tarea

Demostrar, usando el metodo de "suponer y confirmar", que la solucion a la recurrencia es $T(n) = \Theta(n\log \log n)$.

Puntos a considerar:

- Realiza un análisis iterativo (o recursivo) para ver cómo se reduce el tamaño del problema en cada llamada.
- Justifica por qué otras conjeturas (como $\Theta(n) \ o \ \Theta(n\log n)) $ no se ajustan a la recurrencia.
- Detalla el proceso inductivo para establecer cotas superior e inferior.

## Solución

### Analisis iterativo

Primero, debemos notar que no podemos aplicar el método maestro directamente, ya que la recurrencia no tiene la forma $T(n) = aT(n/b) + f(n)$, donde $a \geq 1$, $b > 1$ y $f(n)$ es una función asintóticamente positiva.

Entonces, queda usar el método de "suponer y confirmar". Para ello, vamos a analizar cómo se reduce el tamaño del problema en cada llamada.

$T(n) = \sqrt{n}\ T(\sqrt{n}) + n$

$T(\sqrt{n}) = \sqrt[4]{n}\ T(\sqrt[4]{n}) + \sqrt{n} $

$\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \vdots$

Si expandimos la recurrencia, podemos ver que el tamaño del problema se reduce de la siguiente manera:

$T(n) = \sqrt n (\sqrt[4]n T(\sqrt[4] n) + \sqrt n)) + n$

Simplificando la expresion:

$T(n) = \sqrt n \sqrt[4]n T(\sqrt[4] n) + 2n$

Asi, para k iteraciones, tendremos:

$T(n) = \sqrt n \sqrt[4]n \sqrt[8]n \ldots \sqrt[2^k]n T(\sqrt[2^k] n) + kn$

Para que el tamaño del problema sea 1, necesitamos que $\sqrt[2^k]n = n^\frac{1}{2^k} =O(1)$

Aplicando logaritmos:

$\frac {\log n}{2^k} = O(1)$

$\log n = O(2^k) \rightarrow 2^k = O(\log n) $

$k = O(\log \log n)$

Finalmente, la recurrencia se reduce a:

$T(n) = \sqrt n \sqrt[4]n \sqrt[8]n \ldots \sqrt[2^k]n T(\sqrt[2^k] n) + kn$

Remmplazando $k = O(\log \log n)$:

$T(n) \approx O(n \log\log n)+ n T(1)$

Ademas:

$\Omega(n) = n\log \log n$

Entonces : $T(n) = \Theta(n\log \log n)$

## Justificación

Para justificar que $T(n) = \Theta(n\log \log n)$, vamos a analizar por qué otras conjeturas no se ajustan a la recurrencia.

- Para $\Theta(n) = n\log n$

**Cota superior:**

Si asumimos que $T(n) \leq cn \log n$

Si reemplazamos en la recurrencia:

$T(n) = \sqrt{n}\ T(\sqrt{n}) + n \leq \sqrt n [c\sqrt n\log \sqrt n] + n$

$\hspace{3.6cm}\leq cn\log \sqrt n$

$\hspace{3.6cm}\leq \frac {1}{2}cn\log n\rightarrow c^\prime n \log n$

Sigue siendo una cota superior de la recurrencia.

**Cota inferior:**

Debemos probar que $T(n) \geq kn \log n$

Sin embargo:

$T(n) = \sqrt{n}\ T(\sqrt{n}) + n \geq \sqrt n [k\sqrt n\log \sqrt n] + n$

$kn \frac{1}{2}\log n  + n \geq kn\log n$ (contradicción para valores de n suficientemente grandes)

Se cumple que, respecto a cotas:

$T(n) = O(n\log n)$

$T(n) \not = \Omega(n \log n)$

Por lo tanto $T(n) \not = \Theta(n\log n)$

**Para $\Theta(n) = n$**

**Cota superior:**

Para que \( T(n) \in O(n) \), debe existir \( c \) tal que:

\[
T(n) \leq c \cdot n, \quad \forall n \geq n_0
\]

Pero como \( T(n) = \Theta(n \log \log n) \), sabemos que:

\[
T(n) \geq c_1 n \log \log n
\]

Para valores suficientemente grandes de \( n \), \( \log \log n \to \infty \), lo que implica que \( T(n) \) crece **más rápido** que \( O(n) \).  
Por lo tanto, **\( T(n) \notin O(n) \)**.

## Proceso para establecer cotas superior e inferior

Para establecer las cotas superior e inferior, vamos a realizar un análisis inductivo.

Veamos porque \( T(n) = \Theta(n \log \log n) \):

**Cota superior:**

$ T(n) \leq cn \log \log n $

Paso inductivo:

$ T(n) = \sqrt{n} T(\sqrt{n}) + n \leq \sqrt{n} [c \sqrt{n} \log \log \sqrt{n}] + n $

$\hspace{3.5cm} \leq cn\log (\frac{1}{2}\log n) + n$

Para un valor de $n$ suficientemente grande, el valor de $\frac{1}{2}$ puede ser abosorbido por la constante $c$.

$cn\log (\frac{1}{2}\log n) + n \leq c^\prime n\log \log n$

Entonces tenemos que $T(n) = O(n\log \log n)$

**Cota inferior:**

$ T(n) \geq kn \log \log n $

Paso inductivo:

$ T(n) = \sqrt{n} T(\sqrt{n}) + n \geq \sqrt{n} [k \sqrt{n} \log \log \sqrt{n}] + n $

$\hspace{3.5cm} \geq kn \log(\frac{1}{2} \log n) +n$

$\hspace{3.5cm} \geq kn [\log(\frac{1}{2}) + \log n] + n$

Podemos absorber el valor de $\frac{1}{2}$ en la constante $k$ para valores de $n$ suficientemente grandes.

$kn [\log(\frac{1}{2}) + \log n] + n \geq k^\prime n \log \log n$

Finalmente, tenemos que $T(n) = \Omega(n\log \log n)$

Es decir, tenemos las cotas superior e inferior:

$ k^\prime n \log \log n \leq T(n) \leq c^\prime n \log \log n$

Por lo tanto :  $T(n) = \Theta(n\log \log n)$
