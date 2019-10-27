#define GAS_PIN1 A4
#define GAS_PIN2 A5
#define CAMBIO_SIGNIFICATIVO 3
int Resultado=0;

void setup()
{
  
  Serial.begin(9600);    
}
 int analogValue1 = -1;
 int analogValue2 = -1;
 
void loop(){

   int analogNew1 = analogRead(GAS_PIN1);         //reading analog port values
   int analogNew2 = analogRead(GAS_PIN2);         //reading analog port values

   if (abs(analogNew1-analogValue1) >= (10.23*CAMBIO_SIGNIFICATIVO)) {     //Correction Factor
    analogValue1 = analogNew1;
  }
  
   if (abs(analogNew2-analogValue2) >= (10.23*CAMBIO_SIGNIFICATIVO)) {     //Correction Factor
    analogValue2 = analogNew2;
  }

    Resultado=analogValue1-analogValue2;           //Calculation of purified air approximation

     delay(5000);
     Serial.write("");      // Start sending data to bluetooth
     Serial.println(String(analogValue1) + " A");
     delay(4000);                                             //Send data via bluetooth with identifier
     Serial.println(String(analogValue2) + " B");
     delay(4000);
     Serial.println(String(Resultado) + " C");
     

    //Send data to bluetooth
    if(Serial.available()>0){
     int dato = Serial.read();  
     Serial.write(dato);  
    }
  
}
