#include <iostream>
#include <string>
#include "FaxPhone.h"

using namespace std;

const int COUNT = 3;

int readInt(const string& prompt)
{
    int value;
    while (true)
    {
        cout << prompt;
        if (cin >> value)
            return value;
        if (cin.eof())
            exit(0);
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Ошибка: введите целое число.\n";
    }
}

void demoDefaultConstructor()
{
    cout << "\n--- Объект, созданный конструктором по умолчанию ---\n";
    FaxPhone phone;
    phone.show();
}

void demoParamConstructor()
{
    cout << "\n--- Объект, созданный конструктором с параметрами ---\n";
    FaxPhone phone(true, 20);
    phone.show();
}

void editAndShow(FaxPhone office[], int n)
{
    cout << "\n--- Редактирование и просмотр свойств каждого объекта ---\n";
    office[0].change();
    office[0].loadPaper(10);
    office[1].pickUp();
    office[1].dial("+7-812-305-12-00");
    office[2].change();
    office[2].receiveFax(7);
    for (int i = 0; i < n; i++)
    {
        cout << "Аппарат " << i + 1 << ": ";
        office[i].show();
    }
}

void processArray(FaxPhone office[], int n)
{
    cout << "\n--- Обработка массива объектов ---\n";
    int onCount = 0, talking = 0, totalPaper = 0, minIndex = 0;
    for (int i = 0; i < n; i++)
    {
        if (office[i].isOn())
            onCount++;
        if (office[i].getState() == PhoneState::Talking)
            talking++;
        totalPaper += office[i].getPaper();
        if (office[i].getPaper() < office[minIndex].getPaper())
            minIndex = i;
    }
    cout << "Включено аппаратов: " << onCount << " из " << n << "\n";
    cout << "Идёт разговор: " << talking << "\n";
    cout << "Всего бумаги в лотках: " << totalPaper << " листов\n";
    cout << "Меньше всего бумаги у аппарата " << minIndex + 1
         << " (" << office[minIndex].getPaper() << " л.)\n";
    cout << "Дозаправка бумагой аппаратов, где меньше 10 листов:\n";
    for (int i = 0; i < n; i++)
        if (office[i].getPaper() < 10)
        {
            cout << "Аппарат " << i + 1 << ": ";
            office[i].loadPaper(FaxPhone::MAX_PAPER - office[i].getPaper());
        }
}

void controlMenu(FaxPhone& phone)
{
    int work = 1;
    while (work)
    {
        cout << "\n===== Телефон-факс =====\n";
        phone.show();
        cout << "1. Вкл/выкл питание\n"
             << "2. Снять трубку\n"
             << "3. Набрать номер\n"
             << "4. Положить трубку\n"
             << "5. Отправить факс\n"
             << "6. Принять факс\n"
             << "7. Загрузить бумагу\n"
             << "0. Выход\n";
        int command = readInt("Введите номер команды -> ");
        switch (command)
        {
        case 1: phone.change(); break;
        case 2: phone.pickUp(); break;
        case 3:
        {
            string number;
            cout << "Номер: ";
            cin >> number;
            phone.dial(number);
            break;
        }
        case 4: phone.hangUp(); break;
        case 5: phone.sendFax(readInt("Страниц: ")); break;
        case 6: phone.receiveFax(readInt("Страниц: ")); break;
        case 7: phone.loadPaper(readInt("Листов: ")); break;
        case 0: work = 0; break;
        default: cout << "Нет такой команды.\n";
        }
    }
}

int main()
{
    demoDefaultConstructor();
    demoParamConstructor();

    FaxPhone office[COUNT] = { FaxPhone(), FaxPhone(true, 30), FaxPhone(false, 5) };
    cout << "\n--- Массив объектов ---\n";
    for (int i = 0; i < COUNT; i++)
    {
        cout << "Аппарат " << i + 1 << ": ";
        office[i].show();
    }

    editAndShow(office, COUNT);
    processArray(office, COUNT);

    cout << "\nУправление аппаратом (создан конструктором по умолчанию):";
    FaxPhone phone;
    controlMenu(phone);
    cout << "Работа завершена.\n";
    return 0;
}
