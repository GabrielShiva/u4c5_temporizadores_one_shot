#include <stdio.h> // inclui a biblioteca padrão da linguagem c para manipulação de entradas/saídas
#include "pico/stdlib.h" // inclui a biblioteca padrão do pico SDK para manipulação das gpios
#include "hardware/timer.h" // inclui a biblioteca para controle de temporizadores de hardware

// define os pinos associados aos leds e ao botão
#define RED_LED 13
#define GREEN_LED 11
#define BLUE_LED 12
#define BTN 5

// definição e inicialização de contador e de flag para verificar se os leds estão ativos
static uint8_t counter = 0;
static bool leds_are_active = false;

// define o estado de cada led (ligado/desligado)
void set_leds_state(bool r, bool g, bool b) {
    gpio_put(RED_LED, r);
    gpio_put(GREEN_LED, g);
    gpio_put(BLUE_LED, b);
}

// inicialização das gpios associadas aos leds 
void setup() {
    gpio_init(RED_LED);
    gpio_set_dir(RED_LED, GPIO_OUT);

    gpio_init(GREEN_LED);
    gpio_set_dir(GREEN_LED, GPIO_OUT);
    
    gpio_init(BLUE_LED);
    gpio_set_dir(BLUE_LED, GPIO_OUT);

    gpio_init(BTN);
    gpio_set_dir(BTN, GPIO_IN);
    gpio_pull_up(BTN); // habilita o resistor de pull-up interno (garante que o pino 5 seja lido como n´ível lógico alto quando o botão não está pressionado)
}

// função de callback chamada a cada 3 segundos
int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    counter = counter + 1; // incrementa o contador

    if (counter == 1) { // verifica se o valor armazenado no contador é igual à 1
        // apaga o led vermelho e mantém os leds verde e azul acesos
        set_leds_state(0, 1, 1);

        // define um alarme para chamar a função turn_off_callback após 3 segundos
        add_alarm_in_ms(3000, turn_off_callback, NULL, true);
    }

    if (counter == 2) { // verifica se o valor armazenado no contador é igual à 2
        // apaga os leds vermelho e verde e mantém o led azul aceso
        set_leds_state(0, 1, 0);

        // define um alarme para chamar a função turn_off_callback após 3 segundos
        add_alarm_in_ms(3000, turn_off_callback, NULL, true);
    }

    if (counter == 3) { // verifica se o valor armazenado no contador é igual à 3
        // apaga todos os leds
        set_leds_state(0, 0, 0);

        leds_are_active = false;
        counter = 0; // reinicializa o valor do contador para que a rotina no loop inifito possa ser executada quando o botão for pressionado
    }

    return 0;
}

int main() {
    stdio_init_all(); // inicializa a comunicação serial (permite o uso do printf)
    setup(); // configuração inicial dos leds e do botão

    // inicializa um loop infinito que verifica continuamente o estado do botão e do contador
    while (true) {

        // verifica se o botão está pressionado e se os leds estão ativos
        // a flag leds_are_active é utilizada para evitar que múltiplos alarmes sejam criados
        if (!gpio_get(BTN) && !leds_are_active) {
            sleep_ms(60); // adiciona um atraso de 60 milisegundos para implementação do debounce do botão

            // verifica novamente se o botão está pressionado
            if (!gpio_get(BTN)) {
                leds_are_active = true;

                // ativa os três leds
                set_leds_state(1, 1, 1);

                // define um alarme para chamar a função turn_off_callback após 3 segundos
                add_alarm_in_ms(3000, turn_off_callback, NULL, true);
            }
        }

        // adiciona um atraso de 20 milisegundos para reduzir o consumo da cpu
        sleep_ms(20);
    }
}
