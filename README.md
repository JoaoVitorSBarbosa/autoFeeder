# AutoFeeder

Alimentador automático de animais controlado via bot do Telegram, desenvolvido com ESP8266 (NodeMCU v2) e servo motor.

## Como funciona

O firmware sincroniza o horário via NTP e aciona um servo motor nos horários configurados. A configuração e o controle são feitos inteiramente pelo Telegram — sem precisar de app ou interface web.

Os horários são persistidos via NVS (Non-Volatile Storage), sobrevivendo a reinicializações do dispositivo.

## Hardware

| Componente | Modelo |
|---|---|
| Microcontrolador | ESP8266 NodeMCU v2 |
| Mecanismo | Servo motor |

## Comandos do Bot

| Comando | Descrição |
|---|---|
| `/start` ou `/help` | Exibe todos os comandos disponíveis |
| `/inicio` | Define o horário da primeira refeição (0–23h) |
| `/intervalo` | Define o intervalo entre refeições em meia horas (Ex: `3` → 1h30) |
| `/porcoesDiarias` | Define quantas refeições por dia |
| `/salvar` | Salva a configuração e gera os horários automaticamente |
| `/verHorarios` | Exibe os horários configurados |
| `/cancelar` | Cancela a próxima refeição |
| `/agora` | Aciona o alimentador imediatamente |

## Configuração

Copie `include/defines.example` para `include/defines.h` e preencha com suas credenciais:

```cpp
#define NOME       "Nome_da_Rede_WiFi"
#define SENHA      "Senha_WiFi"
#define BOTtoken   "TOKEN_DO_BOT_TELEGRAM"
#define CHAT_ID    "SEU_CHAT_ID"

#define SERVO_PIN      0      // Pino do servo
#define SERVO_TEST     false  // true para testar o servo na inicialização
#define SERVO_INIT_POS 0      // Posição inicial do servo
```

> Para obter o token do bot, use o [@BotFather](https://t.me/BotFather) no Telegram.
> Para obter seu chat ID, use o [@userinfobot](https://t.me/userinfobot).

## Setup

**Pré-requisitos:** PlatformIO (extensão VS Code ou CLI)

```bash
git clone <url-do-repo>
cd autoFeeder
cp include/defines.example include/defines.h
# edite defines.h com suas credenciais
pio run --target upload
pio device monitor  # 115200 baud
```
