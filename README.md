![image](https://github.com/user-attachments/assets/f2a5c9b8-6208-4723-8f46-1d74be421827)

# 🌧️ Projeto: Sistema de Alerta de Inundação com Raspberry Pi Pico

## 📑 Sumário
- [🎯 Objetivos](#-objetivos)
- [📋 Descrição do Projeto](#-descrição-do-projeto)
- [⚙️ Funcionalidades Implementadas](#️-funcionalidades-implementadas)
- [🛠️ Requisitos do Projeto](#️-requisitos-do-projeto)
- [📂 Estrutura do Código](#-estrutura-do-código)
- [🖥️ Como Compilar](#️-como-compilar)
- [🤝 Contribuições](#-contribuições)
- [📽️ Demonstração em Vídeo](#️-demonstração-em-vídeo)
- [💡 Considerações Finais](#-considerações-finais)

## 🎯 Objetivos
- Desenvolver um sistema de alerta de inundação utilizando o Raspberry Pi Pico
- Implementar monitoramento de nível de água e intensidade de chuva
- Apresentar dados em tempo real através de display OLED
- Criar um sistema de alerta visual e sonoro para condições críticas

## 📋 Descrição do Projeto
Este projeto utiliza o Raspberry Pi Pico com os seguintes componentes:
- Display OLED SSD1306 via I2C (GPIO 14 e 15)
- LEDs RGB (GPIO 11, 12, 13)
- Joystick analógico (GPIO 26 e 27)
- Matriz de LED WS2812 (GPIO 7)
- Buzzer duplo (GPIO 10 e 21)
- Sistema de multitarefa utilizando FreeRTOS

## ⚙️ Funcionalidades Implementadas
1. **Monitoramento de Condições:**
   - Leitura do nível de água através do joystick (eixo Y)
   - Leitura da intensidade de chuva através do joystick (eixo X)
   - Simulação de condições ambientais para testes do sistema

2. **Sistema de Alerta:**
   - Notificações visuais através da matriz de LEDs WS2812
   - Alertas sonoros via buzzer para condições críticas
   - Indicação visual por LED RGB (verde para condições normais, vermelho para alerta)

3. **Display OLED:**
   - Exibição em tempo real dos valores de nível de água e intensidade de chuva
   - Interface visual dividida em quadrantes para melhor organização das informações
   - Indicação de alerta quando valores críticos são detectados

4. **Controle Multitarefa:**
   - Implementação de sistema multitarefa utilizando FreeRTOS
   - Tarefas independentes para leitura de sensores, controle de LEDs, matriz e alertas
   - Comunicação entre tarefas através de filas

## 🛠️ Requisitos do Projeto
- **FreeRTOS:** Gerenciamento de tarefas concorrentes
- **Comunicação I2C:** Integração com display OLED SSD1306
- **Manipulação de PWM:** Controle do buzzer
- **Protocolo PIO:** Controle da matriz de LEDs WS2812
- **Conversão ADC:** Leitura de valores analógicos do joystick
- **Gerenciamento de tarefas:** Criação e escalonamento de tarefas independentes
- **Comunicação entre tarefas:** Utilização de filas para troca de informações
