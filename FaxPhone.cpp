#include "FaxPhone.h"
#include <iostream>

using namespace std;

FaxPhone::FaxPhone()
    : power(false), handsetUp(false), connected(false), paper(0)
{
}

FaxPhone::FaxPhone(bool power, int paper)
    : power(power), handsetUp(false), connected(false), paper(0)
{
    if (paper < 0)
        paper = 0;
    if (paper > MAX_PAPER)
        paper = MAX_PAPER;
    this->paper = paper;
}

void FaxPhone::change()
{
    power = !power;
    if (!power)
    {
        handsetUp = false;
        connected = false;
        cout << "Телефон-факс выключен.\n";
    }
    else
        cout << "Телефон-факс включён.\n";
}

bool FaxPhone::pickUp()
{
    if (!power)
    {
        cout << "Ошибка: устройство выключено.\n";
        return false;
    }
    if (handsetUp)
    {
        cout << "Трубка уже снята.\n";
        return false;
    }
    handsetUp = true;
    cout << "Трубка снята, слышен гудок.\n";
    return true;
}

bool FaxPhone::hangUp()
{
    if (!power || !handsetUp)
    {
        cout << "Трубка уже лежит на аппарате.\n";
        return false;
    }
    if (connected)
        cout << "Разговор завершён. ";
    handsetUp = false;
    connected = false;
    cout << "Трубка положена.\n";
    return true;
}

bool FaxPhone::dial(const string& number)
{
    if (!power || !handsetUp)
    {
        cout << "Ошибка: для набора номера снимите трубку.\n";
        return false;
    }
    if (connected)
    {
        cout << "Ошибка: уже идёт разговор.\n";
        return false;
    }
    if (number.empty() || number.find_first_not_of("0123456789+-") != string::npos)
    {
        cout << "Ошибка: неверный номер.\n";
        return false;
    }
    connected = true;
    cout << "Соединение с номером " << number << " установлено, идёт разговор.\n";
    return true;
}

bool FaxPhone::sendFax(int pages)
{
    if (!power || handsetUp)
    {
        cout << "Ошибка: факс отправляется из режима ожидания.\n";
        return false;
    }
    if (pages <= 0)
    {
        cout << "Ошибка: число страниц должно быть больше 0.\n";
        return false;
    }
    cout << "Факс отправлен, страниц: " << pages << ".\n";
    return true;
}

int FaxPhone::receiveFax(int pages)
{
    if (!power || handsetUp)
    {
        cout << "Ошибка: факс принимается только в режиме ожидания.\n";
        return 0;
    }
    if (pages <= 0)
    {
        cout << "Ошибка: число страниц должно быть больше 0.\n";
        return 0;
    }
    if (paper == 0)
    {
        cout << "Ошибка: нет бумаги, факс не принят.\n";
        return 0;
    }
    int printed = pages <= paper ? pages : paper;
    paper -= printed;
    cout << "Принят факс, напечатано страниц: " << printed << " из " << pages << ".\n";
    if (paper == 0)
        cout << "Внимание: бумага закончилась!\n";
    return printed;
}

bool FaxPhone::loadPaper(int sheets)
{
    if (sheets <= 0)
    {
        cout << "Ошибка: число листов должно быть больше 0.\n";
        return false;
    }
    if (paper + sheets > MAX_PAPER)
    {
        cout << "Ошибка: в лоток помещается ещё не более " << MAX_PAPER - paper << " листов.\n";
        return false;
    }
    paper += sheets;
    cout << "Загружено листов: " << sheets << ", в лотке: " << paper << ".\n";
    return true;
}

bool FaxPhone::isOn() const { return power; }
bool FaxPhone::isHandsetUp() const { return handsetUp; }
bool FaxPhone::isConnected() const { return connected; }
int FaxPhone::getPaper() const { return paper; }

PhoneState FaxPhone::getState() const
{
    if (!power)
        return PhoneState::Off;
    if (connected)
        return PhoneState::Talking;
    if (handsetUp)
        return PhoneState::DialTone;
    return paper > 0 ? PhoneState::Ready : PhoneState::NoPaper;
}

string FaxPhone::stateName() const
{
    switch (getState())
    {
    case PhoneState::Off:      return "Выключен";
    case PhoneState::Ready:    return "Ожидание";
    case PhoneState::NoPaper:  return "Ожидание, нет бумаги";
    case PhoneState::DialTone: return "Трубка снята (гудок)";
    case PhoneState::Talking:  return "Разговор";
    }
    return "";
}

void FaxPhone::show() const
{
    cout << "Питание: " << (power ? "вкл" : "выкл")
         << " | Трубка: " << (handsetUp ? "снята" : "положена")
         << " | Соединение: " << (connected ? "есть" : "нет")
         << " | Бумага: " << paper << "/" << MAX_PAPER
         << " | Состояние: " << stateName() << "\n";
}
