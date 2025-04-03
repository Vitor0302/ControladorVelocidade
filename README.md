# Controle de Velocidade de um Motor DC com Arduino Uno

Este projeto implementa um sistema de controle de velocidade para um motor DC utilizando um **Arduino Uno**. A velocidade do motor pode ser ajustada por meio de um **potenciômetro**, e um **encoder óptico** mede a velocidade real para ajuste dinâmico. Além disso, um botão permite inverter o sentido de rotação do motor.

## 📌 Funcionalidades
- **Ajuste de velocidade via potenciômetro** 🎛️
- **Leitura da velocidade real com um encoder óptico** 🔄
- **Inversão do sentido de rotação com um botão** ⏪⏩
- **Controle dinâmico via PWM para compensação de carga** ⚙️

## 🛠️ Componentes Utilizados
- **Arduino Uno**
- **Motor DC**
- **Driver de potência (Ponte H)**
- **Potenciômetro**
- **Encoder óptico**
- **Botão para inversão da rotação**

## 🏗️ Como funciona?
1. O usuário gira o **potenciômetro** para definir a velocidade desejada.
2. O **Arduino** lê esse valor e gera um sinal **PWM** para o motor.
3. O **encoder** mede a velocidade real e o Arduino faz ajustes para mantê-la estável.
4. Se o botão for pressionado, o sentido da rotação do motor é invertido.
