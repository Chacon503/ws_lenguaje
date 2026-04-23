/* Variables iniciales */
x int => 5;
y int => 3;

/* Calculo de factorial de x con while */
fact int => 1;
i int => 1;
while (i <= x) {
    fact = fact * i;
    i = i + 1;
}

/* Suma directa */
resultado int => x + y;

print fact;       /* 120 */
print resultado;  /* 8 */

/* Conteo con while */
j int => 0;
while (j < 3) {
    print j;
    j = j + 1;
}

/* Condicional */
if (resultado > 10) {
    print 999;
} else {
    print 111;
}
