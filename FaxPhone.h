// S3P13 Моделирование устройств с помощью класса
// Вариант 14 «Телефон-факс»
#ifndef FAXPHONE_H
#define FAXPHONE_H

#include <string>

// Состояния устройства
enum class PhoneState
{
    Off,        // выключен
    Ready,      // ожидание, бумага есть
    NoPaper,    // ожидание, нет бумаги (приём факса невозможен)
    DialTone,   // трубка снята, гудок
    Talking     // разговор
};

class FaxPhone
{
public:
    static const int MAX_PAPER = 50;   // ёмкость лотка, листов

    FaxPhone();                          // конструктор по умолчанию
    FaxPhone(bool power, int paper);     // конструктор с параметрами

    // Методы, моделирующие поведение
    void change();                       // включить / выключить питание
    bool pickUp();                       // снять трубку
    bool hangUp();                       // положить трубку
    bool dial(const std::string& number);// набрать номер
    bool sendFax(int pages);             // отправить факс
    int  receiveFax(int pages);          // принять факс, возвращает число напечатанных листов
    bool loadPaper(int sheets);          // загрузить бумагу

    // Просмотр свойств
    bool isOn() const;
    bool isHandsetUp() const;
    bool isConnected() const;
    int  getPaper() const;
    PhoneState getState() const;
    std::string stateName() const;
    void show() const;

private:
    bool power;        // питание: вкл / выкл
    bool handsetUp;    // трубка: снята / положена
    bool connected;    // соединение с абонентом
    int  paper;        // бумага в лотке: 0..MAX_PAPER
};

#endif // FAXPHONE_H
