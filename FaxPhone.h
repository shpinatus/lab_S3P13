#ifndef FAXPHONE_H
#define FAXPHONE_H

#include <string>

enum class PhoneState
{
    Off,
    Ready,
    NoPaper,
    DialTone,
    Talking
};

class FaxPhone
{
public:
    static const int MAX_PAPER = 50;

    FaxPhone();
    FaxPhone(bool power, int paper);

    void change();
    bool pickUp();
    bool hangUp();
    bool dial(const std::string& number);
    bool sendFax(int pages);
    int  receiveFax(int pages);
    bool loadPaper(int sheets);

    bool isOn() const;
    bool isHandsetUp() const;
    bool isConnected() const;
    int  getPaper() const;
    PhoneState getState() const;
    std::string stateName() const;
    void show() const;

private:
    bool power;
    bool handsetUp;
    bool connected;
    int  paper;
};

#endif
