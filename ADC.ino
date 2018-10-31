/*
 * UTILIZANDO ARDUINO COMO CONVERTIDOR ANALOGICO DIGITAL
 * El numero 3 es mi favorito.
 * Se toma una medicion de diferencia de potencial en un puente de Wheatstons.
 * Arduino considera 10 bits en sus entradas analogicas.
 * El valor leido es convertido a un equivalente de nBits declarado al inicio del programa.
 * Se muestra el equivalente en binario natural segun ledArray[nBits].
 *  
 * Programa realizado con Arduino Nano - Andres Garcia 31-10-2018
 * Para estudiantes de Programacion I - EIE FIA UES
 */
const int nBits = 4; //numero de bits a utilizar
const int analogIn_0 = A0;
const int analogIn_1 = A1;
bool ledArray[nBits];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  for( int i = 0; i <= nBits - 1; i++){
     ledArray[i] = i + 2;
     pinMode(ledArray[i], OUTPUT);
  } //inicializacion de ledArray[] como vector de bits
}

void loop() {
  // put your main code here, to run repeatedly:
  int measure_1 = analogRead(analogIn_1); //lectura en puente de Wheatstone
  int measure_0 = analogRead(analogIn_0); //lectura en puente de Wheatstone
  int dif = measure_1 - measure_0; //diferencia de potencial 
  // Se monitorea mediante Serial Port par verificar funcionalidad del programa y circuito
  Serial.print(measure_1);
  Serial.print("\t");
  Serial.print(measure_0);
  Serial.print("\t");
  Serial.print(dif);
  Serial.print("\t");
  
  dif = map(dif, 0, 511, 0, pow(2, nBits)-1); //map convierte a un equivalente de 10 bits a uno de nBits
  Serial.println(dif);
  decToBin(dif, nBits); //funcion para convertir el numero decimal 'dif' a binario
  delay(1500);  
}

  //funcion para convertir numero N base decimal a binario natural de n bits
void decToBin(int N, int n){
  int N_bin[nBits];
  for (int i = 0; i <= n - 1; i++){
    N_bin[i] =  N%2;
    N = N/2;
  } //Se convierte a binario natural segun algoritmo aritmetico (divisiones sucesivas)
  
  for (int i = n - 1; i >= 0; i--){
    Serial.print(N_bin[i]);
    if(N_bin[i] == 1){
      digitalWrite(ledArray[i], HIGH);
    }else{
      digitalWrite(ledArray[i], LOW);
    }
  } //Se imprime al revez, segun el algoritmo de divisiones sucesivas.
  Serial.println();
}
