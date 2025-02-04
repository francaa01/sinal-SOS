#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_2  // Pino do LED
#define DOT_TIME 200        // Tempo do ponto (ms)
#define DASH_TIME (DOT_TIME * 3)  // Tempo do traço (ms)
#define PAUSE_TIME DOT_TIME  // Pausa entre piscadas (ms)
#define LETTER_PAUSE (DOT_TIME * 3) // Pausa entre letras (ms)
#define WORD_PAUSE (DOT_TIME * 7)   // Pausa entre palavras (ms)

// Função para piscar o LED (tempo variável)
void blink_led(int duracao) {
    gpio_set_level(LED_PIN, 1); // Liga o LED
    vTaskDelay(pdMS_TO_TICKS(duracao)); // Mantém aceso
    gpio_set_level(LED_PIN, 0); // Desliga o LED
    vTaskDelay(pdMS_TO_TICKS(PAUSE_TIME)); // Pequena pausa entre sinais
}

// Função para enviar um sinal SOS em código Morse
void send_sos() {
    // Letra 'S' ( ... )
    for (int i = 0; i < 3; i++) {
        blink_led(DOT_TIME);
    }
    
    vTaskDelay(pdMS_TO_TICKS(LETTER_PAUSE)); // Pausa entre letras
    
    // Letra 'O' ( --- )
    for (int i = 0; i < 3; i++) {
        blink_led(DASH_TIME);
    }

    vTaskDelay(pdMS_TO_TICKS(LETTER_PAUSE)); // Pausa entre letras
    
    // Letra 'S' ( ... )
    for (int i = 0; i < 3; i++) {
        blink_led(DOT_TIME);
    }

    vTaskDelay(pdMS_TO_TICKS(WORD_PAUSE)); // Pausa antes de repetir SOS
}

void app_main(void)
{
    // Configurar o pino do LED como saída
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    while (1) {
        send_sos(); // Enviar sinal SOS
    }
}
