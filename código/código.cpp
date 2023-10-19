// Definición de pines para los displays de 7 segmentos y pines para otros componentes
#define A 10
#define B 11
#define C 5
#define D 6
#define E 7
#define F 9
#define G 8
#define CLAVIJA 2        // Pin del interruptor
#define UNIDAD A4        // Pin para la unidad en el display de 7 segmentos
#define DECENA A5        // Pin para la decena en el display de 7 segmentos
#define APAGADO 0        // Estado de apagado
#define TIMEDISPLAYON 10 // Tiempo de encendido del display
#define MOTOR_PIN 3      // Pin para el motor
#define LDR_PIN A1       // Pin para el fotodiodo

const int sensorPin = A0; // Pin para el sensor de temperatura

int countDigit = 1;
int isArduinoOn = 1;    // Estado del Arduino
int motorIsOn = 0;      // Estado del motor

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

void setup() {
    // Configuración de pines
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
    pinMode(LDR_PIN, INPUT); // Configura el pin del fotodiodo como entrada
    Serial.begin(9600);
    printDigit(0);
}

void loop() {
    int sensorValue = analogRead(sensorPin);
    float voltage = (sensorValue / 1023.0) * 5.0;
    float temperatureC = (voltage - 0.5) * 100.0;
    int intensidadLuz = analogRead(LDR_PIN); // Lee la intensidad de luz del fotodiodo

    if (temperatureC >= 30.0) {
        isArduinoOn = 0;
        digitalWrite(MOTOR_PIN, 0);
        digitalWrite(UNIDAD, LOW);
        digitalWrite(DECENA, LOW);
        digitalWrite(LDR_PIN, LOW);
    } else {
        isArduinoOn = 1;
        motorIsOn = 0;
        if (isArduinoOn == 1) {
            Serial.print("Intensidad de luz: ");
            Serial.println(intensidadLuz);
            // Controlar el motor
            if (!motorIsOn) {
                analogWrite(MOTOR_PIN, 150);
                motorIsOn = 1;
            }
            int interruptor = keypressed();
            printDigit(countDigit);
            if (interruptor == APAGADO) {
                countDigit++;
                if (countDigit > 99) {
                    countDigit = 0;
                }
                delay(TIMEDISPLAYON);
            } else {
                digitalWrite(MOTOR_PIN, 0);//el motor al estar el switch en primos se detendra
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

// Función para mostrar un dígito en el display de 7 segmentos
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