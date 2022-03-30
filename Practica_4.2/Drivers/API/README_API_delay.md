# API Delay

Autor   : Ing. Jhonny Velasco
mail    : javelasco1992@gmail.com
Curso   : Programación de Microcontroladores
Profesor: Ing. Patricio Bos


Esta API implementa un código para hacer uso de retarnos no bloqueantes. Está compuesta por 3 funciones principales:

1.- delayInit(delay_t * delay, tick_t duration);
Permite inicializar la API, recibe como parametros la structura delay y la duración en milisegundos del retardo que necesitamos.

2.- delayRead(delay_t * delay);
Esta función hace la validación si el retardo ya culminó, devulve true si el retardo ya pasó o false cuando aun no se cumple el tiempo de retardo.

3.- delayWrite(delay_t * delay, tick_t duration);
Esta función actualiza el retardo a un nuevo valor.

