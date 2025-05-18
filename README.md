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


## 📂 Estrutura do Repositório
```
├── Enchente.c             # Código principal do projeto
└── FreeRTOSConfig       # Configura as tasks
└── ssd1306.c            # Configuração do controle do display
└── ssd1306.h            # Configura a .c como biblioteca
└── ws2812.pio.h         # Configura o controle da matriz de LED
└── font.h               # Configura as letras e números para o dispaly ssd1306
└── ...                  # Demais arquivos necessários
```

## 🖥️ Como Compilar
1. Clone o repositório:
   ```bash
   https://github.com/JPSRaccolto/sistema_alerta.git
   ```
2. Navegue até o diretório do projeto:
   ```bash
   cd sistema_alerta
   ```
3. Compile o projeto com seu ambiente de desenvolvimento configurado para o RP2040.
4. Carregue o código na placa BitDogLab.

## 🖥️ Metodo alternativo:
1. Baixe o repositório com arquivo zip.
2. Extraia para uma pasta de fácil acesso
3. Utilize a extensão raspberry pi pico dentro do VS Code para importar o projeto.
4. Aguarde ate criar o arquivo build
5. Utilize o ícone "_compile_" para compilar.
6. Utilize o "_RUN_" com a BitDogLab em modo boot seel para enviar o programa para a sua RP2040.
7. Agora, interaja com os botões e o teclado para mergulhar nas funcionalidades do projeto.

## 🧑‍💻 Autor
**João Pedro Soares Raccolto**

## 📝 Descrição
Sistema de alerta de inundação utilizando Raspberry Pi Pico que monitora o nível de água e intensidade de chuva através de um joystick analógico. O sistema inclui exibição de dados em um display OLED, alertas visuais através de matriz de LEDs WS2812 e LEDs RGB, e alertas sonoros via buzzer duplo quando condições críticas são detectadas. A arquitetura multitarefa com FreeRTOS permite o monitoramento e alertas em tempo real com tarefas concorrentes.

## 🤝 Contribuições
Este projeto foi desenvolvido por **João Pedro Soares Raccolto**.
Contribuições são bem-vindas! Siga os passos abaixo para contribuir:

1. Fork este repositório.
2. Crie uma nova branch:
   ```bash
   git checkout -b minha-feature
   ```
3. Faça suas modificações e commit:
   ```bash
   git commit -m 'Minha nova feature'
   ```
4. Envie suas alterações:
   ```bash
   git push origin minha-feature
   ```
5. Abra um Pull Request.

## 📽️ Demonstração em Vídeo
- O vídeo de demonstração do projeto pode ser visualizado aqui: [Drive]()

## 💡 Considerações Finais
Este projeto demonstra a implementação de um sistema de monitoramento e alerta de inundações utilizando o Raspberry Pi Pico com FreeRTOS. O sistema é capaz de monitorar o nível de água e a intensidade de chuva, exibindo essas informações em um display OLED e acionando alertas visuais e sonoros quando condições críticas são detectadas.
A arquitetura baseada em tarefas do FreeRTOS permite que o sistema execute múltiplas funções simultaneamente, garantindo que o monitoramento, exibição e alertas funcionem de maneira independente e eficiente. O projeto pode ser expandido para incluir sensores reais de nível de água e chuva, bem como conectividade sem fio para envio de alertas remotos.
