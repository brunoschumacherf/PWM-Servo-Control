#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 22
#define LED_PIN   12

#define PWM_FREQ_HZ     50
#define PWM_PERIOD_US   20000
#define PWM_DIVIDER     125.0f

#define PULSE_180_US 2400
#define PULSE_90_US  1470
#define PULSE_0_US   500

#define PULSE_STEP_US 5
#define STEP_DELAY_MS 10

int main() {
    stdio_init_all(); // Inicializa entrada e saída padrão

    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM); // Configura o pino do servo para a função PWM
    uint pwm_slice = pwm_gpio_to_slice_num(SERVO_PIN); // Obtém o número do slice do PWM
    uint pwm_channel = pwm_gpio_to_channel(SERVO_PIN); // Obtém o canal PWM associado ao pino

    pwm_set_clkdiv(pwm_slice, PWM_DIVIDER); // Define o divisor de clock para ajustar a frequência do PWM
    pwm_set_wrap(pwm_slice, PWM_PERIOD_US - 1); // Define o período do PWM
    pwm_set_chan_level(pwm_slice, pwm_channel, 0); // Define nível inicial do canal PWM
    pwm_set_enabled(pwm_slice, true); // Habilita o PWM

    gpio_init(LED_PIN); // Inicializa o pino do LED
    gpio_set_dir(LED_PIN, GPIO_OUT); // Define o pino do LED como saída

    // Movimentos iniciais do servomotor
    printf("Movendo servo para 180°\n");
    pwm_set_chan_level(pwm_slice, pwm_channel, PULSE_180_US); // Define PWM para posição 180°
    sleep_ms(5000);

    printf("Movendo servo para 90°\n");
    pwm_set_chan_level(pwm_slice, pwm_channel, PULSE_90_US); // Define PWM para posição 90°
    sleep_ms(5000);

    printf("Movendo servo para 0°\n");
    pwm_set_chan_level(pwm_slice, pwm_channel, PULSE_0_US); // Define PWM para posição 0°
    sleep_ms(5000);

    int pulse_width = PULSE_0_US; // Inicializa largura do pulso na posição 0°
    bool increasing = true; // Direção do movimento
    int led_counter = 0; // Contador para alternância do LED

    printf("Iniciando varredura suave entre 0° e 180°...\n");
    while (true) {
        pwm_set_chan_level(pwm_slice, pwm_channel, pulse_width); // Atualiza posição do servo
        
        // Alterna o LED a cada 10 ciclos
        if (++led_counter >= 10) {
            gpio_xor_mask(1u << LED_PIN); // Inverte o estado do LED
            led_counter = 0;
        }
        
        sleep_ms(STEP_DELAY_MS); // Aguarda antes do próximo passo

        // Ajusta o ângulo do servomotor de forma gradual
        if (increasing) {
            pulse_width += PULSE_STEP_US;
            if (pulse_width >= PULSE_180_US) {
                pulse_width = PULSE_180_US;
                increasing = false; // Inverte direção do movimento
            }
        } else {
            pulse_width -= PULSE_STEP_US;
            if (pulse_width <= PULSE_0_US) {
                pulse_width = PULSE_0_US;
                increasing = true; // Inverte direção do movimento
            }
        }
    }
    return 0;
}
