
---

## 📋 Visão Geral

Este projeto demonstra o controle de um **servomotor** utilizando o módulo **PWM** do microcontrolador **RP2040** (Raspberry Pi Pico W). Ele gera sinais PWM para posicionar o servomotor em ângulos específicos e realizar uma varredura suave entre 0° e 180°.  

Além disso, um LED RGB conectado à **GPIO 12** pisca periodicamente, indicando a execução simultânea de múltiplas tarefas. O projeto pode ser testado tanto em hardware real quanto em simuladores como **Wokwi** e **BitDogLab**.  

---

## 🚀 Funcionalidades

### 🔹 Controle do PWM
- O sinal PWM opera a **50 Hz** (período de **20 ms**) na **GPIO 22**.  
- O divisor de clock é ajustado para que cada **tick represente 1 µs**, permitindo precisão nos pulsos.  

### 🔹 Posicionamento do Servomotor
- **180° → Pulso de 2400 µs**  
- **90° → Pulso de 1470 µs**  
- **0° → Pulso de 500 µs**  
Cada posição é mantida por **5 segundos** antes da transição.  

### 🔹 Varredura Suave
- O servo realiza uma varredura contínua entre **0° e 180°**, aumentando ou diminuindo **5 µs** a cada **10 ms**, garantindo um movimento gradual e fluido.  

### 🔹 Indicação com LED  
- O LED RGB na **GPIO 12** pisca periodicamente (~100 ms) para sinalizar que o sistema está ativo.  

---

## 🔧 Instalação e Execução

### 1️⃣ Configuração do Ambiente
- Instale e configure o [Pico SDK](https://github.com/raspberrypi/pico-sdk).  
- Utilize um ambiente como **VS Code** com extensões para C/C++.  

### 2️⃣ Clonando o Repositório
```bash
git clone https://github.com/brunoschumacherf/PWM-Servo-Control
cd PWM-Servo-Control
```

### 3️⃣ Compilação e Upload  
Execute os seguintes comandos:  
```bash
mkdir build
cd build
cmake ..
make
```
Isso gerará um arquivo **.uf2** ou **.hex**.  

#### ▶️ Teste no Raspberry Pi Pico W:
- Conecte o Pico em **modo bootloader** e copie o arquivo compilado para o dispositivo.  

#### 🖥️ Simulação no Wokwi/BitDogLab:
- Importe o projeto no simulador e configure as conexões:  
  - **GPIO 22:** Controle do servomotor  
  - **GPIO 12:** LED RGB  

---

## 📁 Entregáveis  

- **Código-Fonte:** Todo o código está disponível neste repositório.  
- **Vídeo Demonstrativo:** [Adicionar link](https://drive.google.com/file/d/1xheecxIxhoxraP3RAJNPTQlgTh7RUu12/view?usp=sharing)  

---

🚀 _Desenvolvido por Bruno Schumacher_  

---

