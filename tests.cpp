// Тесты модели «Телефон-факс»: проверка переходов по диаграмме состояний
// Сборка: g++ tests.cpp FaxPhone.cpp -o tests
#include <iostream>
#include <sstream>
#include <string>
#include "FaxPhone.h"

using namespace std;

int passed = 0, failed = 0;

void check(bool condition, const string& name)
{
    if (condition)
        passed++;
    else
        failed++;
    cerr << (condition ? "[OK]   " : "[FAIL] ") << name << "\n";
}

int main()
{
    // Сообщения устройства во время тестов не выводим
    stringstream sink;
    streambuf* old = cout.rdbuf(sink.rdbuf());

    FaxPhone a;
    check(a.getState() == PhoneState::Off && a.getPaper() == 0, "Конструктор по умолчанию: Выключен, 0 листов");

    FaxPhone b(true, 70);
    check(b.getState() == PhoneState::Ready && b.getPaper() == FaxPhone::MAX_PAPER,
          "Конструктор с параметрами: Ожидание, бумага ограничена 50");

    check(!a.pickUp() && a.getState() == PhoneState::Off, "Выключен: снять трубку нельзя");
    a.change();
    check(a.getState() == PhoneState::NoPaper, "Выключен -> change() -> Ожидание, нет бумаги");
    check(a.receiveFax(3) == 0, "Нет бумаги: факс не принимается");
    check(a.loadPaper(5) && a.getState() == PhoneState::Ready, "Нет бумаги -> loadPaper() -> Ожидание");
    check(!a.loadPaper(100) && a.getPaper() == 5, "Переполнение лотка не допускается");

    check(a.sendFax(2) && a.getState() == PhoneState::Ready, "Ожидание -> sendFax() -> Ожидание");
    check(a.receiveFax(2) == 2 && a.getPaper() == 3, "Ожидание -> receiveFax(2): расход бумаги");
    check(a.receiveFax(10) == 3 && a.getState() == PhoneState::NoPaper,
          "Ожидание -> receiveFax(): бумага закончилась -> Нет бумаги");
    a.loadPaper(10);

    check(a.pickUp() && a.getState() == PhoneState::DialTone, "Ожидание -> pickUp() -> Трубка снята");
    check(!a.sendFax(1), "Трубка снята: отправка факса невозможна");
    check(!a.dial("12ab") && a.getState() == PhoneState::DialTone, "Неверный номер: разговор не начат");
    check(a.dial("88123051200") && a.getState() == PhoneState::Talking, "Трубка снята -> dial() -> Разговор");
    check(!a.dial("123"), "Разговор: повторный набор невозможен");
    check(a.hangUp() && a.getState() == PhoneState::Ready, "Разговор -> hangUp() -> Ожидание");

    a.pickUp();
    check(a.hangUp() && a.getState() == PhoneState::Ready, "Трубка снята -> hangUp() -> Ожидание");

    a.pickUp();
    a.dial("100");
    a.change();
    check(a.getState() == PhoneState::Off && !a.isHandsetUp() && !a.isConnected(),
          "Разговор -> change() -> Выключен (соединение разорвано)");
    check(a.getPaper() == 10, "Бумага сохраняется после выключения");

    cout.rdbuf(old);
    cout << "Пройдено: " << passed << ", ошибок: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}
