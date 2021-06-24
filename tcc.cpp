// Inclui a Biblioteca Servo.h
#include <Servo.h> 

//Inclui a biblioteca LiquidCrystal
#include <LiquidCrystal.h>

// set pinos relacionados a rotina de ligar o programa
// número do pino pushbutton para ligar o programa
const int buttonPin = 2; 
// número do pino LED que sinaliza que está pronto para iniciar o programa
const int ledPin = 3; 

// set variaveis relaionadas a presença da bolinha no lançador
// variável para leitura do pushbutton
int estado = 0; 
// variável para armazenar valores do pushbutton
int guarda_estado = LOW; 
//variável relacionda a bolinha
int bola = 0; 

// pinos do sensor da bola
// led que avisa se há uma bolinha
int pinoLed = 4; 
//sensor de luminosidade dedicado a presença da bolinha
int pinoSensorLuz = A5;  
// vairável destinada ao sensor de luminosidade
int valorLuz = 0;    

//pinos e variáveis relacionados ao motor e ao disparo da bolinha
// número do pino pushbutton para disparo da bolinha
const int buttonPin2 = 6; 
// variável para leitura do pushbutton de disparo
int estado2 = 0; 
// Inicializa o servo no modo de teste
Servo meuservo; 
// Ajusta o ângulo inicial do Servo
int angulo = 0; 
// Inicializa o pino analógico para o potenciômetro
int potencio = A4; 

// Pinos e variaveir relacionadas ao sensor
// pino do led do sensor de presença em frente ao lançador
int ledPin2 = 8; 
// pino do sensor de presença
const int inputPin = 7; 
// o sensor inicia assumindo que não ha nada em frente a ele
int pirState = LOW; 
// variavel relacionada ao sensor
int val = 0; 
// Speaker relacionada ao aviso do disparo ou de presença em frente ao sensor (digital 9, 10, ou 11)
int pinSpeaker = 9; 
// variavel 2 do sensor de presença
int sensor2 = 0;  

//Portas analogicas     A0 A1 A2 A3 A4 A5
//Portas Digitais 12 13 14 15 16 17 18 19

//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(17, 16, 15, 14, 11, 10);

// número do pino pushbutton para disparo automatico da bolinha
const int buttonPin3 = 12; 
// número do pino LED que sinaliza que o programa esta rodando no automático
const int ledPin3 = 13; 
// variável para leitura do pushbutton
int estado3 = 0; 
// variável para armazenar valores do pushbutton3
int guarda_estado3 = LOW; 

//Função resposavel pelo lançamento automatico da bolinha
void autoplay(){
  	//pausa de segurança
  	pausa();
	// le o estado pushbutton
  	estado3 = digitalRead(buttonPin3);
  	// verifica se o botão está pressionado
  	if (estado3 == HIGH) {
    	// inverte valor da variável variable_buttonEstado
    	guarda_estado3 = !guarda_estado3;
    	//esperera o tempo meio segundo para evitar que haja várias vezes alterações
    	delay(500);
    }
  	if (guarda_estado3 == HIGH) {
    	// liga o led
    	digitalWrite(ledPin3, HIGH);
    }
  	else {
    	// desliga o led
    	digitalWrite(ledPin3, LOW);
    }
}

// Função de ligar o programa pelo botão
void ligarprograma(){
  	pausa();
	// le o estado pushbutton
  	estado = digitalRead(buttonPin);
  	// verifica se o botão está pressionado
  	if (estado == HIGH) {
    	// inverte valor da variável variable_buttonEstado
    	guarda_estado = !guarda_estado;
    	//esperera o tempo meio segundo para evitar que haja várias vezes alterações
    	delay(500);
    }
  	if (guarda_estado == HIGH) {
    	// liga o led
    	digitalWrite(ledPin, HIGH);
    }
  	else {
    	// desliga o led
    	digitalWrite(ledPin, LOW);
    }
}

//Função sensor de presença da bolinha
void sensorbola(){
  pausa();
  // verifica o estado do sensor
  valorLuz = analogRead(pinoSensorLuz);
  // caso esteja bloqueado por algo ele sinaliza que há uma bolinha e liga o led
  if(valorLuz<750){                
    digitalWrite(pinoLed,HIGH);
  	bola = 1;
  	delay(100);
  	}
  //caso não haja nada ele desliga o led e avisa que não há bolinha
  else{                    
    digitalWrite(pinoLed,LOW);
  	bola = 0;
  	}
  	delay(100);                   
}

//Função motor
void motor(){
  	pausa();
  	// Faz a leitura do valor do potenciômetro
	angulo = analogRead(potencio); 
  	// Associa o valor do potenciômetro ao valor do ângulo
	angulo = map(angulo, 0, 1023, 0, 179); 
	// Comando para posicionar o servo no ângulo especificado
  	meuservo.write(angulo); 
	delay(100);
}

// Função de disparo do programa
void disparo(){
  	// le o estado pushbutton
		estado2 = digitalRead(buttonPin2);
		//Se botão de automatico estiver pressionado, o estado2 é considerado como ativo
  		estado3 = digitalRead(buttonPin3);
  		if(val == 1){
    		pausa();
        }
  else {
  		if (guarda_estado3 == HIGH){
          estado2 = HIGH;
        }
		// verifica se o botão está pressionado
  		if (estado2 == HIGH){
          	//aviso de lançamento da bolinha
			tone(pinSpeaker,1500); 
          	lcd.clear();
            lcd.setCursor(0, 0);
          	//Aviso de ue é necessario se afastar para o lançamento
    		lcd.print("Afaste se do");
            lcd.setCursor(0, 1);
    		lcd.print("lancador!");
  			delay(500);
  			//Desligando o buzzer.
  			noTone(pinSpeaker);
  			delay(500);
          	//lança a bolinha posicionando o motor no valor inicial
          	angulo = 0;
          	// Comando para posicionar o servo no ângulo especificado
    		meuservo.write(angulo); 
      		//esperera 5 segundos para evitar que ocorra acidentes
			delay(500);
		}
  		else {
          	// Faz a leitura do valor do potenciômetro
    		angulo = analogRead(potencio);
          	// Associa o valor do potenciômetro ao valor do ângulo
			angulo = map(angulo, 0, 1023, 0, 179);
 	        // Comando para posicionar o servo no ângulo especificado
			meuservo.write(angulo); 
			delay(100);
    	}	
}
}

// Função do sensor de presença
void sensor(){
	// Le o balor do sensor
   	val = digitalRead(inputPin);
  	// Verifica se o sensor esta ativo atravez da variavel
  	if (val == HIGH) {     
      	//variavel avisando que o sensor de presença esta ativo
   		sensor2 = 1;
    	// Liga o led avisando que ha alguem em frente
    	digitalWrite(ledPin2, HIGH);  
    	// liga o speaker avisando que ha alguem na frente
    	playTone(300, 160);
      	delay(150);
    	// caso sensor não esteja ativo
    	if (pirState == LOW) {
    		Serial.println("Motion detected!");
      		pirState = HIGH;
      		sensor2 = 0;
    	}
    }
  	else {
		//desliga led
	    digitalWrite(ledPin2, LOW); 
      	//desliga speaker
      	playTone(0, 0);
      	delay(300);
      	lcd.clear();
      	if (pirState == HIGH){
      		Serial.println("Motion ended!");
      		pirState = LOW;
      		sensor2 = 0;
    	}
  	}  
}

// Função relacionda ao speaker
void playTone(long duration, int freq) {
    duration *= 1000;
    int period = (1.0 / freq) * 1000000;
    long elapsed_time = 0;
    while (elapsed_time < duration) {
        digitalWrite(pinSpeaker,HIGH);
        delayMicroseconds(period / 2);
        digitalWrite(pinSpeaker, LOW);
        delayMicroseconds(period / 2);
        elapsed_time += (period);
    }
}

//Função responsavel pela LCD
void LCD(){
  	if (guarda_estado3 == HIGH) {
      	lcd.clear();
    	lcd.setCursor(0, 0);
    	lcd.print("Disparo automatico");
    	lcd.setCursor(0, 1);
    	lcd.print("ativo");
      	delay(5000);
    }
  else {
  	if (guarda_estado == HIGH) {
      	lcd.clear();
    	lcd.setCursor(0, 0);
    	lcd.print("Potencia:");
    	lcd.setCursor(10, 0);
    	angulo = analogRead(potencio);
		lcd.print(angulo);
      	if ( bola == 1){
            lcd.setCursor(0, 1);
    		lcd.print("Bolinha carregada");
          	for (int posicao = 0; posicao < 6; posicao++){
              	delay(50);
    			lcd.scrollDisplayLeft();
    			delay(50);
  			}
            delay(100);
            lcd.clear();
            lcd.setCursor(0, 0);
    		lcd.print("Aperte o botao");
            lcd.setCursor(0, 1);
    		lcd.print("de disparo");
            delay(100);
            estado2 = digitalRead(buttonPin2);
        }
      	else {
        	lcd.setCursor(0, 1);
    		lcd.print("Insira uma bolinha");
        	for (int posicao = 0; posicao < 6; posicao++){
    			delay(300);
              	lcd.scrollDisplayLeft();
    			delay(300);
  			}
        }
    }
  	else {
    	//Limpa a tela
  		lcd.clear();
  		//Posiciona o cursor na coluna 1, linha 0;
  		lcd.setCursor(1, 0);
  		//Envia o texto entre aspas para o LCD
  		lcd.print("Aperte o botao");
  		//Posiciona o cursor na coluna 4, linha 1;
  		lcd.setCursor(4, 1);
  		lcd.print("'ligar'");
  		delay(500);
    }
}
}

// Pausa de segurança
void pausa(){
  	if (sensor2 == 1){
    	lcd.clear();
    	lcd.setCursor(0, 0);
		lcd.print("Aviso de presenca em frente ao");
    	lcd.setCursor(0, 1);
   		lcd.print("lancador, por favor se afaste!");
  		for (int posicao = 0; posicao < 6; posicao++){
        	delay(100);
    		lcd.scrollDisplayLeft();
    		delay(100);
    	}
  		// Faz a leitura do valor do potenciômetro
    	angulo = analogRead(potencio);
    	// Associa o valor do potenciômetro ao valor do ângulo
		angulo = map(angulo, 0, 1023, 0, 179);
 		// Comando para posicionar o servo no ângulo especificado
		meuservo.write(angulo); 
		delay(100);
    }
  	else {
    	delay(100);  
    }
}

void setup() {
	// define o pino do Led que sinaliza que esta ligado a energia
	pinMode(ledPin, OUTPUT);
	// define pino do pushbutton que liga o programa
	pinMode(buttonPin, INPUT);
  	// define pino do pushbutton que dispara a bolinha 
  	pinMode(buttonPin2, INPUT);
	//define pino como led do sensor da bola
	pinMode(pinoLed,OUTPUT); 
  	// Define que o Servo está conectado a Porta 5
  	meuservo.attach(5); 
  	// define o led que sinaliza a prenseça
	pinMode(ledPin2, OUTPUT);     
  	// define o pino do sensor
 	pinMode(inputPin, INPUT); 
  	// speaker
  	pinMode(pinSpeaker, OUTPUT);
  	Serial.begin(9600);
  	//Define o número de colunas e linhas do LCD respectivamente
  	lcd.begin(16, 2);
  	// define pino do pushbutton de disparo automático 
  	pinMode(buttonPin3, INPUT);
  	// define o pino do Led que sinaliza o disparo automático
	pinMode(ledPin3, OUTPUT);
 	}
 
void loop(){
  	LCD();
  	ligarprograma();
	if (guarda_estado == HIGH){
      	sensorbola();
      	if (bola == 1) {
      		motor();
          	sensor();
          	if (sensor2 == 1){
              	pausa();
            }
          	else {
            	autoplay();
          		disparo();
            }
        }
	} 
	else {
		digitalWrite(pinoLed,LOW);
	}
}
