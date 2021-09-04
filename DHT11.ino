/* ========================================================================================================
 
   Curso de Arduino e AVR 117
   
   WR Kits Channel


   Medidor de Umidade e Temperatura OLED

    
   Autor: Eng. Wagner Rambo  Data: Maio de 2017
   
   www.wrkits.com.br | facebook.com/wrkits | youtube.com/user/canalwrkits | dailymotion.com/wrkits
   
======================================================================================================== */


// ========================================================================================================
// --- Bibliotecas Auxiliares ---
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <dht.h>   


// ===============================================================================
// --- Mapeamento de Hardware ---
#define    dht_pin    7   //pino de sinal do dht11 


// ========================================================================================================
// --- Definições e Objetos ---
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);   //objeto para o OLED
dht   my_dht;                           //objeto para o DHT11
 
#if (SSD1306_LCDHEIGHT != 64)
#endif


// ========================================================================================================
// --- Protótipo das Funções ---
void disp_temp(); //mostrar a temperatura em Graus Celsius
void disp_umid(); //mostrar a umidade relativa do ar


// ========================================================================================================
// --- Variáveis Globais ---
int    temperatura = 0x00,   //armazena a temperatura
       umidade     = 0x00,   //armazena a umidade
       counter     = 0x00;   //contador auxiliar

boolean control = 0x00;      //flag de controle


// ========================================================================================================
// --- Interrupção ---
ISR(TIMER2_OVF_vect)
{
    TCNT2=100;              //Reinicializa o registrador do Timer2
    counter++;              //incrementa counter
    
    if(counter == 400 )     //counter igual a 400?
    {                       //sim...
    
       counter = 0x00;      //reinicia counter
       
       
       digitalWrite(13, !digitalRead(13)); //Inverte o estado da saída
       control = !control;
    
    } //end if counter
    
} //end ISR


// ========================================================================================================
// --- Configurações Iniciais ---
void setup()   
{    

  Serial.begin(9600);   //serial em 9600 baud rate   

  pinMode(13, OUTPUT);  //saída digital 13 (LED onboard)
 
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  //Inicializa OLED com endereço I2C 0x3C (para 128x64)
  display.clearDisplay();
  display.display();

  TCCR2A = 0x00;   //Timer operando em modo normal
  TCCR2B = 0x07;   //Prescaler 1:1024
  TCNT2  = 100;    //10 ms overflow again
  TIMSK2 = 0x01;   //Habilita interrupção do Timer2
  
} //end setup


// ========================================================================================================
// --- Loop Infinito ---
void loop() 
{
   

   my_dht.read11(dht_pin);

   temperatura = my_dht.temperature;
   umidade     = my_dht.humidity;


   //Serial.print(temperatura);
   //Serial.print(" ");
   //Serial.println(umidade);


   if(control) disp_temp(); //se control é verdadeiro, mostra temperatura
   else        disp_umid(); //senão, mostra a umidade relativa do ar
   
    display.clearDisplay(); //limpa o display OLED
  
} //end loop


// ========================================================================================================
// --- Desenvolvimento das Funções ---
void disp_temp()
{
   display.setTextSize(2);
   display.setTextColor(WHITE);
   display.setCursor(0,0);
   display.print("Temp.");
   display.setTextSize(4);
   display.setCursor(6,24);
   display.setTextColor(WHITE);
   display.print(temperatura);
   display.print(" C");
   display.display();
  
} //end disp_temp


void disp_umid()
{
   display.setTextSize(2);
   display.setTextColor(WHITE);
   display.setCursor(0,0);
   display.print("Umid.");
   display.setTextSize(4);
   display.setTextColor(WHITE);
   display.setCursor(6,24);
   display.print(umidade);
   display.print(" %");
   display.display();
  
 
} //end umid_temp












 
 
