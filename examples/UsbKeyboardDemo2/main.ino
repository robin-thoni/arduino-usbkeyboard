#define ARD_UTILS_DELAYMS
#define ARD_UTILS_UTF8
#include "ArdUtils/ArdUtils.h"

#define ARD_USBKBD_AZERTY
#define ARD_USBKBD_QWERTY
#include "UsbKeyboard.h"

#define ledPin 13

void setup()
{
    pinMode (ledPin, OUTPUT);
    digitalWrite (ledPin, HIGH);
}

void loop()
{
    WAIT_USB;
    ArdUtils::delayMs(42);

    char* str = "abcdefghijklmnopqrstuvwxyz\nABCDEFGHIJKLMNOPQRSTUVWXYZ\n0123456789\n&\"\'(-_)=\n~#{[|`\\^@]}\n,;:!$\n?.<>/\n+-*/%\nµù§\néèçà\n";

    ArdUtils::utf8ToAscii(str);

    UsbKeyboard.setLayout("fr");
    UsbKeyboard.sendKeyStrokes(str);

    ArdUtils::delayMs(4000);

    UsbKeyboard.setLayout("us");
    UsbKeyboard.sendKeyStrokes(str);


    digitalWrite(ledPin, !digitalRead(ledPin));
}
