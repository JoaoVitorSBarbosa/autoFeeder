#include "../include/telegramBot.h"
#include "../include/defines.h"
#include "../include/funcsAux.h"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
NVS nvs = NVS();

FuncsAux fn = FuncsAux();

String inicio = DEFAULT_INIT;
String intervalo = DEFAULT_INTERVAL;
String quantidade = DEFAULT_QUANTIDY;
String horarios = "";

TelegramBot::TelegramBot() {
    client.setTrustAnchors(&cert);
}

String TelegramBot::meiaConverter(String meiasHoras) {
    String result = "";
    int meias = atoi(meiasHoras.c_str());
    int horas = meias / 2;
    result = String(horas) + ":" + ((meias % 2) == 0 ? "00" : "30");
    return result;
}

String TelegramBot::newResp() {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
        for (int i = 0; i < numNewMessages; i++) {
            // Chat id of the requester
            String chat_id = String(bot.messages[i].chat_id);
            if (chat_id != CHAT_ID) {
                bot.sendMessage(chat_id, "Unauthorized user", "");
                continue;
            }

            // Print the received message
            String text = bot.messages[i].text;
            return text;
        }
    }
    return "";
}

void TelegramBot::startMessage(String from_name, String chat_id) {
    String welcome = "Bem vindo(a), " + from_name + ".\n";
    welcome += "\n ";
    welcome += "/inicio Para selecionar o primeiro horario de entrega de comida do pet (Ex: 16)\n";
    welcome += "/intervalo Para selecionar o intervalo entre refeições do pet em meia horas (Ex: 3, que dará 1 hora e meia de intervalo) \n";
    welcome += "/porcoesDiarias Para selecionar a quantidade de refeições diárias do pet (Ex: 2, ou seja 2 refeições por dia) \n";
    welcome += "/salvar Para salvar as alterações \n";
    welcome += "/verHorarios Para ver os horarios de refeições do pet \n";
    welcome += "/cacelar Para cancelar a proxima refeição do pet \n";
    welcome += "/agora Para alimentar o pet agora";
    bot.sendMessage(chat_id, welcome, "");
}
void TelegramBot::initMessage(String chat_id) {
    bot.sendMessage(chat_id, "Digite o horário (numero inteiro de 0 a 23)", "");
    while (inicio == "") {
        inicio = newResp();
    }
    bot.sendMessage(chat_id, "O primeiro horário selecionado foi " + inicio + " horas", "");
}
void TelegramBot::intervalMessage(String chat_id) {
    bot.sendMessage(chat_id, "Digite o espaço de tempo entre refeições em meia horas (numero inteiro de 0 a 46, Ex: 3, que dará 1 hora e meia de intervalo)", "");
    while (intervalo == "") {
        intervalo = newResp();
    }
    bot.sendMessage(chat_id, "O intervalo horário selecionado foi " + meiaConverter(intervalo), "");
}
void TelegramBot::qtdyMessage(String chat_id) {
    bot.sendMessage(chat_id, "Digite a quantidade de refeições (numero inteiro de 0 a 24, Ex: 2)", "");
    while (quantidade == "") {
        quantidade = newResp();
    }
    bot.sendMessage(chat_id, "O quantidade selecionada foi " + quantidade + " porções diárias", "");
}
void TelegramBot::viewMessage(String chat_id) {
    String message = "";
    message += "inicio: " + ((inicio == "") ? "⭕️" : inicio) + " horas" + "\n";
    message += "intervalo: " + ((intervalo == "") ? "⭕️" : meiaConverter(intervalo)) + "\n";
    message += "quantidade: " + ((quantidade == "") ? "⭕️" : quantidade) + " porções diárias" + "\n";
    message += "horários: " + ((horarios == "") ? "⭕️" : horarios) + "\n";
    bot.sendMessage(chat_id, message, "");
}
void TelegramBot::cancelMessage(String chat_id) {
    bot.sendMessage(chat_id, "A proxima refeição será cancelada", "");
    cancelNext = true;
}
void TelegramBot::saveMessage(String chat_id) {
    int init = atoi(inicio.c_str());
    int interval = atoi(intervalo.c_str());
    int quantity = atoi(quantidade.c_str());
    horarios = "";
    for (int i = 0; i < quantity; i++) {
        String horario = String((init * 2) + (interval * i));
        horarios += meiaConverter(horario) + ((i + 1 < quantity) ? "," : "");
    }

    bot.sendMessage(chat_id, "Novos horarios: " + horarios, "");
    Serial.println(nvs.insertString(horarios) ? "Gravado" : "Erro");
}

void TelegramBot::handleNewMessages(int numNewMessages) {
    for (int i = 0; i < numNewMessages; i++) {
        // Chat id of the requester
        String chat_id = String(bot.messages[i].chat_id);
        if (chat_id != CHAT_ID) {
            bot.sendMessage(chat_id, "Unauthorized user", "");
            continue;
        }

        // Print the received message
        String text = bot.messages[i].text;
        String from_name = bot.messages[i].from_name;

        if ((text == "/start") || (text == "/help")) {
            startMessage(from_name, chat_id);
        } else if (text == "/inicio") {
            initMessage(chat_id);
        } else if (text == "/intervalo") {
            intervalMessage(chat_id);
        } else if (text == "/porcoesDiarias") {
            qtdyMessage(chat_id);
        } else if (text == "/verHorarios") {
            viewMessage(chat_id);
        } else if (text == "/cancelar") {
            cancelMessage(chat_id);
        } else if (text == "/salvar") {
            saveMessage(chat_id);
        } else if (text == "/agora"){
            fn.giraServo();
            bot.sendMessage(chat_id, "Pet alimentado!", "");
        } else {
            bot.sendMessage(chat_id, "Comando desconhecido", "");
        }
    }
}

void TelegramBot::respVerify() {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    while (numNewMessages) {
        Serial.println("got response");
        handleNewMessages(numNewMessages);
        numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
}

void TelegramBot::sendMessage(String message) {
    const String chat_id = CHAT_ID;
    bot.sendMessage(chat_id, message, "");
}