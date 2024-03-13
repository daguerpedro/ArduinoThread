#include <Thread.h>
#include <StaticThreadController.h>

bool ispressed = false;
bool go = true;

Thread a = Thread();
Thread b = Thread();
Thread c = Thread();

StaticThreadController<3> controller (&a, &b, &c);

// "Game" Thread
void toggleLed()
{
  digitalWrite(8, ispressed);
}

// "Sensor" Thread
void readSensor()
{
  ispressed = digitalRead(2);
}

// "Bluetooth" Thread
void comms()
{
  while(Serial.available() > 0)
  { 
    if(Serial.read() == 's') go = false;
  }  
}


void setup() {
  pinMode(8, OUTPUT);
  pinMode(2, INPUT);
  pinMode(7, OUTPUT);
  
  Serial.begin(9600);
  Serial.setTimeout(0);
  
  a.onRun(toggleLed);
  b.onRun(readSensor);
  c.onRun(comms);

  Serial.println("Usar \"Threads\" no arduino pode ser útil quando manipulamos telas, sensores e módulos de comunicação ao mesmo tempo, esse código (Assim como o wokwi) poderia ter sido útil em meu jogo no Projeto Integrador da primeira fase do curso de Engenharia Eletrônica.\nEnvie 's' no console para parar o programa\nAlterne a posição do switch para ver o led da esquerda acender.");
}

void loop() {
  if(go)
    controller.run();   
  else
    {
      digitalWrite(7, true);
      digitalWrite(8, false);
    }
}
