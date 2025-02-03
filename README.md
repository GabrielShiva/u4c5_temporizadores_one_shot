# Resolução da Atividade 2 (Parte 2) - Aula Síncrona 29/01 - Temporizador One Shot

Este código é a solução para a atividade 2, parte 2, referente a aula síncrona do dia 29/01 do Embarcatech que envolve o controle de LEDs utilizando um botão no Raspberry Pi Pico W. O programa aciona três LEDs em uma sequência específica quando o botão é pressionado, utilizando temporizadores de hardware de um disparo para controlar os intervalos (definidos como 3 segundos).

## Descrição do Código

- **Hardware Utilizado**:
  - Raspberry Pi Pico.
  - LEDs conectados aos GPIOs 13 (vermelho), 11 (verde) e 12 (azul).
  - Botão conectado ao GPIO 5 (com resistor de pull-up interno habilitado).

- **Funcionamento**:
  1. Ao pressionar o botão, todos os LEDs são ligados.
  2. Após 3 segundos, o LED vermelho é desligado, mantendo verde e azul.
  3. Após mais 3 segundos, o LED verde é desligado, mantendo apenas o azul.
  4. Após 3 segundos finais, todos os LEDs são desligados.
  - O botão possui debounce (atraso de 60 ms) para evitar leituras incorretas durante a execução da sequência dos LEDs.
  - A flag `leds_are_active` impede a ativação múltipla dos alarmes.

## Como Executar o Código

### Pré-requisitos
- Raspberry Pi Pico.
- Ambiente de desenvolvimento, como o VsCode.
- Ambiente de desenvolvimento configurado com o [Pico SDK](https://github.com/raspberrypi/pico-sdk). 
    - Pode ser obitida com a instalação da extensão `Raspberry Pi Pico W` (VsCode).
- Ferramentas de compilação: `CMake`, `GCC` e `make`.

### Configuração do Hardware
1. Conecte os LEDs aos pinos GPIO:
   - LED Vermelho: GPIO 13.
   - LED Verde: GPIO 11.
   - LED Azul: GPIO 12.
   - Utilize resistores em série com os LEDs (ex: 330Ω).
2. Conecte o botão ao GPIO 5 e ao GND (fiação pull-down interna habilitada via código).

* Alternativamente, pode-se realizar a simulação com utilização do Wokwi.

### Compilação e Upload
1. Clone o repositório utilizando o comando abaixo.
```
git clone https://github.com/GabrielShiva/u4c5_temporizadores_one_shot.git
```
2. No VsCode, clique na extensão `Raspberry Pi Pico W`, depois em *Importar Projeto*, selecione a pasta do projeto, escolha a versão do SDK (2.1.0) e, por fim, em *Importar*.