# Integrantes
- Fernandez Enrique
- Ferreyra Nicolás
- Forlino Lucas
- Altamirano Kiara
# Link https://github.com/Fenrique1995/Parcial-SPD-Parte-uno/tree/main
# Proyecto: Contador Display 7 Segmentos con Multiplexación
![Tinkercad](./imágen/circuito.png)
![Tinkercad](./imágen/circuito02.png)
# Descripción
Codigo de la parte uno del parcial, esto permite que mediante botones se pueda manipular los segmentos.
```
// Definición de pines para los segmentos y botones
#define A 10
#define B 11
#define C 5
#define D 6
#define E 7
#define F 9
#define G 8
#define SUBE 4
#define BAJA 3
#define RESET 2
#define UNIDAD A4
#define DECENA A5
#define APAGADO 0
#define TIMEDISPLAYON 10

// Declaración de variables globales
int countDigit = 0;         // Almacena el número actual a mostrar en el display
int Sube = 1;               // Estado del botón SUBE
int subePrevia = 1;         // Estado previo del botón SUBE
int baja = 1;               // Estado del botón BAJA
int bajaPrevia = 1;         // Estado previo del botón BAJA
int reset = 1;              // Estado del botón RESET
int resetPrevia = 1;        // Estado previo del botón RESET

// Configuración inicial de pines y estado inicial
void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(UNIDAD, OUTPUT);
  pinMode(DECENA, OUTPUT);
  printDigit(0);  // Inicializa el display con el valor 0
}

// Bucle principal del programa
void loop() {
  // Detección de botones y actualización del número a mostrar en el display
  int pressed = keypressed();
  printDigit(countDigit);  // Muestra el nuevo número en el display
  if (pressed == SUBE) {
    countDigit++;
    if (countDigit > 99) {
      countDigit = 0;
    }
    delay(TIMEDISPLAYON);    // Espera un tiempo para mostrar el número
  }

  if (pressed == BAJA) {
    countDigit--;
    if (countDigit < 0) {
      countDigit = 99;
    }
    delay(TIMEDISPLAYON);    // Espera un tiempo para mostrar el número
  }

  if (pressed == RESET) {
    countDigit = 0;
    delay(TIMEDISPLAYON);    // Espera un tiempo para mostrar el número
  }
}

// Función para detectar el botón presionado (con detección de flancos)
int keypressed() {
  Sube = digitalRead(SUBE);
  baja = digitalRead(BAJA);
  reset = digitalRead(RESET);

  if (Sube != subePrevia) {
    delay(10);
    subePrevia = Sube;
    if (Sube == LOW) {
      return SUBE;  // Retorna SUBE si el botón se ha presionado
    }
  }
  if (baja != bajaPrevia) {
    delay(10);
    bajaPrevia = baja;
    if (baja == LOW) {
      return BAJA;  // Retorna BAJA si el botón se ha presionado
    }
  }
  if (reset != resetPrevia) {
    delay(10);
    resetPrevia = reset;
    if (reset == LOW) {
      return RESET;  // Retorna RESET si el botón se ha presionado
    }
  }
  return APAGADO;  // Retorna APAGADO si ningún botón se ha presionado
}

// Función para mostrar un dígito en el display
void printDigit(int number) {
  int decena = number / 10;
  int unidad = number % 10;

  digitalWrite(UNIDAD, LOW);
  digitalWrite(DECENA, LOW);
  display(decena);// Muestra la unidad en el display
  digitalWrite(DECENA, HIGH);
  delay(10);

  digitalWrite(UNIDAD, LOW);
  digitalWrite(DECENA, LOW);
  display(unidad);// Muestra la decena en el display
  digitalWrite(UNIDAD, HIGH);
  delay(10);
}


void display(int digit) {
  switch (digit) {
    case 0:
      // Apagar todos los segmentos excepto G para mostrar "0".
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, HIGH);
      break;
    case 1:
      // Configurar segmentos A y D para mostrar "1".
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 2:
      // Configurar segmentos B y C para mostrar "2".
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, HIGH);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
      break;
    case 3:
      // Configurar segmentos A, B, C y D para mostrar "3".
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, LOW);
      break;
    case 4:
      // Configurar segmentos A, D, E y F para mostrar "4".
      digitalWrite(A, HIGH);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
    case 5:
      // Configurar segmentos B, E y F para mostrar "5".
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
    case 6:
      // Configurar segmentos B, C, E y F para mostrar "6".
      digitalWrite(A, LOW);
      digitalWrite(B, HIGH);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
    case 7:
      // Configurar segmentos A, B y D para mostrar "7".
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
    case 8:
      // Apagar todos los segmentos para mostrar "8".
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, LOW);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
    case 9:
      // Configurar segmentos E para mostrar "9".
      digitalWrite(A, LOW);
      digitalWrite(B, LOW);
      digitalWrite(C, LOW);
      digitalWrite(D, LOW);
      digitalWrite(E, HIGH);
      digitalWrite(F, LOW);
      digitalWrite(G, LOW);
      break;
    default:
      // Apagar todos los segmentos para cualquier otro valor.
      digitalWrite(A, HIGH);
      digitalWrite(B, HIGH);
      digitalWrite(C, HIGH);
      digitalWrite(D, HIGH);
      digitalWrite(E, HIGH);
      digitalWrite(F, HIGH);
      digitalWrite(G, HIGH);
      break;
  }
}
```
Codigo parte dos del parcial, se incorporo un motor, un switch reemplazando los botones y un sensor de temperatura.
```
// Definición de pines para segmentos y otros valores constantes
#define A 10
#define B 11
#define C 5
#define D 6
#define E 7
#define F 9
#define G 8
#define CLAVIJA 2
#define UNIDAD A4
#define DECENA A5
#define APAGADO 0
#define TIMEDISPLAYON 10
#define MOTOR_PIN 3

const int sensorPin = A0; // Pin analógico para el sensor

int countDigit = 1;       // Contador para los dígitos en el display
int isArduinoOn = 1;      // Control de encendido/apagado del Arduino
int motorIsOn = 0;        // Control de encendido/apagado del motor

// Función para verificar si un número es primo
int esPrimo(int numero) {
    if (numero <= 1) {
        return 0;
    }
    for (int i = 2; i * i <= numero; i++) {
        if (numero % i == 0) {
            return 0;
        }
    }
    return 1;
}

// Función para verificar si el interruptor está presionado
int keypressed() {
    int interruptor = digitalRead(CLAVIJA);
    delay(10);
    if (interruptor == 1) {
        return interruptor;
    }
    return APAGADO;
}

// Configuración inicial del Arduino
void setup() {
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(UNIDAD, OUTPUT);
    pinMode(DECENA, OUTPUT);
    pinMode(MOTOR_PIN, OUTPUT);
    Serial.begin(9600);
    printDigit(0);  
}

// Bucle principal del programa
void loop() {
    int sensorValue = analogRead(sensorPin); // Lectura del valor del sensor
    float voltage = (sensorValue / 1023.0) * 5.0; // Conversión del valor del sensor a voltaje
    float temperatureC = (voltage - 0.5) * 100.0; // Conversión del voltaje a temperatura en grados Celsius

    // Comprobar si la temperatura es igual o mayor a 30 grados Celsius
    if (temperatureC >= 30.0) {
        isArduinoOn = 0; // Apagar Arduino
        digitalWrite(MOTOR_PIN, 0); // Apagar motor
        digitalWrite(UNIDAD, LOW);  // Apagar segmento de unidades
        digitalWrite(DECENA, LOW); // Apagar segmento de decenas
    } else {
        isArduinoOn = 1; // Encender Arduino
        motorIsOn = 0;   // Apagar motor
        if (isArduinoOn == 1) {
            // Controlar el motor
            if (!motorIsOn) {
                analogWrite(MOTOR_PIN, 150); // Encender motor
                motorIsOn = 1;
            }
            int interruptor = keypressed(); // Comprobar si el interruptor está presionado
            printDigit(countDigit); // Mostrar el dígito actual en el display
            if (interruptor == APAGADO) {
                countDigit++; // Incrementar el contador de dígitos
                if (countDigit > 99) {
                    countDigit = 0; // Volver a cero cuando se llega a 99
                }
                delay(TIMEDISPLAYON);
            } else {
                for (int i = 0; i < 100; i++) {
                    if (esPrimo(i)) {
                        countDigit = i;
                        printDigit(countDigit);
                        delay(TIMEDISPLAYON);
                    }
                }
            }
            Serial.print("Temperatura: ");
            Serial.print(temperatureC);
            Serial.println(" °C");
        }
    }
}

// Función para mostrar un dígito en el display de 7 segmentos
void printDigit(int number) {
    int decena = number / 10;
    int unidad = number % 10;

    digitalWrite(UNIDAD, LOW);
    digitalWrite(DECENA, LOW);
    display(decena);
    digitalWrite(DECENA, HIGH);
    delay(150);

    digitalWrite(UNIDAD, LOW);
    digitalWrite(DECENA, LOW);
    display(unidad);
    digitalWrite(UNIDAD, HIGH);
    delay(150);
}

// Función para controlar los segmentos del display de 7 segmentos
void display(int digit) {
    switch (digit) {
        case 0:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            digitalWrite(D, LOW);
            digitalWrite(E, LOW);
            digitalWrite(F, LOW);
            digitalWrite(G, HIGH);
            break;
        case 1:
            digitalWrite(A, HIGH);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            digitalWrite(D, HIGH);
            digitalWrite(E, HIGH);
            digitalWrite(F, HIGH);
            digitalWrite(G, HIGH);
            break;
        case 2:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(C, HIGH);
            digitalWrite(D, LOW);
            digitalWrite(E, LOW);
            digitalWrite(F, HIGH);
            digitalWrite(G, LOW);
            break;
        case 3:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            digitalWrite(D, LOW);
            digitalWrite(E, HIGH);
            digitalWrite(F, HIGH);
            digitalWrite(G, LOW);
            break;
        case 4:
            digitalWrite(A, HIGH);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            digitalWrite(D, HIGH);
            digitalWrite(E, HIGH);
            digitalWrite(F, LOW);
            digitalWrite(G, LOW);
            break;
        case 5:
            digitalWrite(A, LOW);
            digitalWrite(B, HIGH);
            digitalWrite(C, LOW);
            digitalWrite(D, LOW);
            digitalWrite(E, HIGH);
            digitalWrite(F, LOW);
            digitalWrite(G, LOW);
            break;
        case 6:
            digitalWrite(A, LOW);
            digitalWrite(B, HIGH);
            digitalWrite(C, LOW);
            digitalWrite(D, LOW);
            digitalWrite(E, LOW);
            digitalWrite(F, LOW);
            digitalWrite(G, LOW);
            break;
        case 7:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            digitalWrite(D, HIGH);
            digitalWrite(E, HIGH);
            digitalWrite(F, HIGH);
            digitalWrite(G, HIGH);
            break;
        case 8:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            digitalWrite(D, LOW);
            digitalWrite(E, LOW);
            digitalWrite(F, LOW);
            digitalWrite(G, LOW);
            break;
        case 9:
            digitalWrite(A, LOW);
            digitalWrite(B, LOW);
            digitalWrite(C, LOW);
            digitalWrite(D, LOW);
            digitalWrite(E, HIGH);
            digitalWrite(F, LOW);
            digitalWrite(G, LOW);
            break;
        default:
            digitalWrite(A, HIGH);
            digitalWrite(B, HIGH);
            digitalWrite(C, HIGH);
            digitalWrite(D, HIGH);
            digitalWrite(E, HIGH);
            digitalWrite(F, HIGH);
            digitalWrite(G, HIGH);
            break;
    }
}
```
# Función principal
# Diagrama de circuito