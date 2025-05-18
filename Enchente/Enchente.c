#include <stdio.h>
#include "pico/stdlib.h"
#include "FreeRTOS.h"
#include "task.h"
#include "ws2812.pio.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "ssd1306.h"
#include "font.h"
#include "queue.h"

#define vermelho 13
#define verde 11
#define azul 12
#define IS_RGBW false
#define NUM_PIXELS 25
#define WS2812_PIN 7
#define PWM_WRAP 4095
#define PWM_CLK_DIV 30.52f
#define buzzer1 10
#define buzzer2 21
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define endereco 0x3C
#define DEADZONE 170
float agua = 45.0f;
float chuva  = 50.0f;
ssd1306_t ssd;
 
volatile uint8_t cor_atual = 0;

typedef struct
{
    uint16_t pos_x;
    uint16_t pos_y;
}joystick_data_t;
QueueHandle_t xQueueJoystickData;
static inline void put_pixel(uint32_t pixel_grb)
{
    pio_sm_put_blocking(pio0, 0, pixel_grb << 8u);
}

static inline uint32_t urgb_u32(uint8_t r, uint8_t g, uint8_t b)
{
    return ((uint32_t)(r) << 8) | ((uint32_t)(g) << 16) | (uint32_t)(b);
}

int i = 0;

double desenho0[25] = {
    0.0, 0.0, 0.2, 0.0, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.2, 0.0, 0.0,
    0.0, 0.0, 0.2, 0.0, 0.0,
    0.0, 0.0, 0.2, 0.0, 0.0
};

void num0(uint8_t r, uint8_t g, uint8_t b){
    
    // Define a cor com base nos parâmetros fornecidos
    uint32_t color = urgb_u32(r, g, b);  
     // Define todos os LEDs com a cor especificada
    for (int i = 0; i < NUM_PIXELS; i++)
    {
        if (desenho0[i])
        {
            put_pixel(color); // Liga o LED com um no buffer
        }
        else
        {
            put_pixel(0);  // Desliga os LEDs com zero no buffer
        }
    }
    
}

//configurações do PWM
void pwm_init_gpio(uint gpio, uint wrap, float clkdiv) {
    gpio_set_function(gpio, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(gpio);
    pwm_config config = pwm_get_default_config();
    pwm_config_set_wrap(&config, wrap);
    pwm_config_set_clkdiv(&config, clkdiv);
    pwm_init(slice_num, &config, true);
}
void vJoystickTask(void *params){

    adc_gpio_init(27);
    adc_gpio_init(26);
    adc_init();
    joystick_data_t joydata;

    while (true) {
        adc_select_input(0);                  // Y axis
        joydata.pos_y = adc_read();           // 0 a 4095
        adc_select_input(1);                  // X axis
        joydata.pos_x = adc_read();
        // Y nivel da água
        // X chuva
        // Calcular desvios
        int16_t diff_y = 2048 - (int16_t)joydata.pos_y;
        int16_t diff_x = (int16_t)joydata.pos_x - 2048;

        // Ajustar água com base no eixo Y
        if (abs(diff_y) > DEADZONE) {
            agua += (diff_y > 0) ? -2.0f : 2.0f;
            if (agua < 0.0f) agua = 0.0f;
            if (agua > 100.0f) agua = 100.0f;
        }

        // Ajustar chuva com base no eixo X
        if (abs(diff_x) > DEADZONE) {
            chuva += (diff_x > 0) ? 2.0f : -2.0f;
            if (chuva < 0.0f) chuva = 0.0f;
            if (chuva > 100.0f) chuva = 100.0f;
        }

        xQueueSend(xQueueJoystickData, &joydata, 0);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void vMatrizTask(){
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);
    ws2812_program_init(pio, sm, offset, WS2812_PIN, 800000, IS_RGBW);
    joystick_data_t joydata;
    while(true){
        if(xQueueReceive(xQueueJoystickData, &joydata, portMAX_DELAY) == pdTRUE){
            if(agua > 70.0f || chuva > 80.0f){
                vTaskDelay(pdMS_TO_TICKS(10));
                num0(255,80,0);
                vTaskDelay(pdMS_TO_TICKS(10));
            }
            else{
                num0(0,0,0);
            }
        }
    }
}

void vLedTask(){
    //inicializa os pinos LED RBG
    gpio_init(vermelho);
    gpio_set_dir(vermelho, GPIO_OUT);
    gpio_init(verde);
    gpio_set_dir(verde, GPIO_OUT);
    joystick_data_t joydata;
    while(true){
        if(xQueueReceive(xQueueJoystickData, &joydata, portMAX_DELAY) == pdTRUE){
            if(agua > 70.0f || chuva > 80.0f){
                gpio_put(vermelho, true);
                gpio_put(verde, false);
            }
            else{
                gpio_put(vermelho, false);
                gpio_put(verde, true);
            }
        }
    }
}

void vBuzzerTask(){
    pwm_init_gpio(buzzer1, 500, 125.0f);
    pwm_init_gpio(buzzer2, 500, 125.0f);
    joystick_data_t joydata;
    while(true){
        if(xQueueReceive(xQueueJoystickData, &joydata, portMAX_DELAY) == pdTRUE){
            if(agua > 70.0f || chuva > 80.0f){
                pwm_set_gpio_level(buzzer1, 125); // 50%
                pwm_set_gpio_level(buzzer2, 125); // 50%
                vTaskDelay(pdMS_TO_TICKS(500));
                pwm_set_gpio_level(buzzer1, 0);   // silencia
                pwm_set_gpio_level(buzzer2, 0);   // silencia
                vTaskDelay(pdMS_TO_TICKS(1000));
            }
            else{
                pwm_set_gpio_level(buzzer1, 0);   // silencia
                pwm_set_gpio_level(buzzer2, 0);   // silencia
            }
        }
    }
}
void vMensagemTask(){
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);                    // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);                    // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA);                                        // Pull up the data line
    gpio_pull_up(I2C_SCL);                                        // Pull up the clock line
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, endereco, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd);                                         // Configura o display
    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);
    bool cor = true;
    char str_A[5]; 
    char str_C[5];
    joystick_data_t joydata;
    while(true){
        ssd1306_fill(&ssd, !cor);                          // Limpa o display

        ssd1306_rect(&ssd, 5, 5, 123, 59, cor, false);
        ssd1306_line(&ssd, 5, 20, 123, 20, cor);
        ssd1306_line(&ssd, 5, 40, 123, 40, cor);
        ssd1306_line(&ssd, 64, 5, 64, 40, cor);
        ssd1306_draw_string(&ssd, "Agua", 10, 8);  // Desenha uma string 
        ssd1306_draw_string(&ssd, "Chuva", 67, 8);  // Desenha uma string 
        sprintf(str_A, "%1.0f", agua);
        sprintf(str_C, "%1.0f", chuva);
        ssd1306_draw_string(&ssd, str_A, 10, 31);  // Desenha uma string 
        ssd1306_draw_string(&ssd, str_C, 67, 31);  // Desenha uma string 
        if(xQueueReceive(xQueueJoystickData, &joydata, portMAX_DELAY) == pdTRUE){
            if(agua > 70.0f || chuva > 80.0f){
                ssd1306_draw_string(&ssd, "ALERTA", 40, 48);  // Desenha uma string 
            }
            else{
                ssd1306_draw_string(&ssd, " ", 40, 48);  // Desenha uma string 
            }
        }
        ssd1306_send_data(&ssd);
    }
}

int main(){

    stdio_init_all();
    xQueueJoystickData = xQueueCreate(6, sizeof(joystick_data_t));
    xTaskCreate(vJoystickTask, "Joystick Task", 512, NULL, 1, NULL);
    xTaskCreate(vLedTask, "RGB Task", 512, NULL, 1, NULL);
    xTaskCreate(vMatrizTask, "Matriz Task", 512, NULL, 1, NULL);
    xTaskCreate(vBuzzerTask, "Buzzer Task", 512, NULL, 1, NULL);
    xTaskCreate(vMensagemTask, "Mensagem Task", 512, NULL, 1, NULL);
    vTaskStartScheduler();
    panic_unsupported();
}   