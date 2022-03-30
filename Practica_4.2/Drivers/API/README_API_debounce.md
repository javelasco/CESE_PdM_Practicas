# API Delay

Autor   : Ing. Jhonny Velasco
mail    : javelasco1992@gmail.com
Curso   : Programación de Microcontroladores
Profesor: Ing. Patricio Bos


Esta API implementa un código para hacer uso de antirebotes por sotfware.

1.- void debounceFSM_init(Led_TypeDef Led);
Recibe el Led a oscilar e inicializa la función antirebote del FSM

2.- void debounceFSM_update(bool buttonState);	
Recibe el valor boleano del pulsador, analiza y resuelve la logica de transición de estados

3.- void buttonPressed(void);	
Esta función hace Togglear LED a 500ms

4.- void buttonReleased(void);
Esta función hace Togglear LED a 100ms

