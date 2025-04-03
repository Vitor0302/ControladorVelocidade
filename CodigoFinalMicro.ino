#include <PID_v1.h>

#define ENA 9   // PWM para controle da velocidade
#define IN1 6   // Controle de direção
#define IN2 7   // Controle de direção
#define POT A0  // Entrada do potenciômetro
#define BOTAO 10 // Entrada do botão
#define ENC_A 2  // Fio amarelo (Yellow) do encoder
#define ENC_B 3  // Fio verde (Green) do encoder

volatile int pulsos = 0; // Contagem de pulsos
unsigned long tempoAnterior = 0;
bool sentidoHorario = true;

int ppr = 11;
int gr = 4;

double Setpoint, Input, Output;
double Kp = 0.5, Ki = 0.05, Kd = 0.05; 

PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void contarPulsos() {
  if (digitalRead(ENC_A) == digitalRead(ENC_B)) {
    pulsos++;  // Sentido horário 
  } else {
    pulsos--;  // Sentido anti-horário 
  }
}

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(POT, INPUT);
  pinMode(BOTAO, INPUT_PULLUP);
  pinMode(ENC_A, INPUT);
  pinMode(ENC_B, INPUT);

  // Configurar interrupções nos dois canais
  attachInterrupt(digitalPinToInterrupt(ENC_A), contarPulsos, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_B), contarPulsos, CHANGE);

  Serial.begin(9600);

  // Inicializar o PID
  Setpoint = 100;  
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(0, 255);
}

void loop() {
  int potValue = analogRead(POT);
  int velocidadeDesejada = map(potValue, 0, 950, 0, 255);

  if (digitalRead(BOTAO) == LOW) {
    sentidoHorario = !sentidoHorario;
    delay(500);
  }

  // Definir a direção do motor
  digitalWrite(IN1, sentidoHorario ? HIGH : LOW);
  digitalWrite(IN2, sentidoHorario ? LOW : HIGH);

  // Medição da velocidade real
  unsigned long tempoAtual = millis();
  if (tempoAtual - tempoAnterior >= 200) {
    int pps = (pulsos * 5);  // Como medimos em 200ms, multiplicamos por 5 para obter PPS (pulses per seconds)
    double rps = (double)pps / (ppr * gr);
    double rpm = 60.0 * rps;

    Input = abs(pulsos); // Para o PID
    pulsos = 0;
    tempoAnterior = tempoAtual;

    Setpoint = velocidadeDesejada;
    myPID.Compute();

    Serial.print("Velocidade real (RPM): ");
    Serial.print(rpm);
    Serial.print(" | Velocidade desejada: ");
    Serial.print(Setpoint);
    Serial.print(" | PID Output: ");
    Serial.println(Output);
  }
  analogWrite(ENA, Output);
}