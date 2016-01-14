//
// Created by robin on 1/8/16.
//

UsbKeyboardDevice UsbKeyboard = UsbKeyboardDevice("us");


/* We use a simplifed keyboard report descriptor which does not support the
 * boot protocol. We don't allow setting status LEDs and but we do allow
 * simultaneous key presses.
 * The report descriptor has been created with usb.org's "HID Descriptor Tool"
 * which can be downloaded from http://www.usb.org/developers/hidpage/.
 * Redundant entries (such as LOGICAL_MINIMUM and USAGE_PAGE) have been omitted
 * for the second INPUT item.
 */
PROGMEM const char usbHidReportDescriptor[35] = { /* USB report descriptor */
        0x05, 0x01,                    // USAGE_PAGE (Generic Desktop)
        0x09, 0x06,                    // USAGE (Keyboard)
        0xa1, 0x01,                    // COLLECTION (Application)
        0x05, 0x07,                    //   USAGE_PAGE (Keyboard)
        0x19, 0xe0,                    //   USAGE_MINIMUM (Keyboard LeftControl)
        0x29, 0xe7,                    //   USAGE_MAXIMUM (Keyboard Right GUI)
        0x15, 0x00,                    //   LOGICAL_MINIMUM (0)
        0x25, 0x01,                    //   LOGICAL_MAXIMUM (1)
        0x75, 0x01,                    //   REPORT_SIZE (1)
        0x95, 0x08,                    //   REPORT_COUNT (8)
        0x81, 0x02,                    //   INPUT (Data,Var,Abs)
        0x95, BUFFER_SIZE-1,           //   REPORT_COUNT (simultaneous keystrokes)
        0x75, 0x08,                    //   REPORT_SIZE (8)
        0x25, 0x65,                    //   LOGICAL_MAXIMUM (101)
        0x19, 0x00,                    //   USAGE_MINIMUM (Reserved (no event indicated))
        0x29, 0x65,                    //   USAGE_MAXIMUM (Keyboard Application)
        0x81, 0x00,                    //   INPUT (Data,Ary,Abs)
        0xc0                           // END_COLLECTION
};

UsbKeyboardDevice::UsbKeyboardDevice(const char* layout)
    : _layout(0)
{
    PORTD = 0; // TODO: Only for USB pins?
    DDRD |= ~USBMASK;

    cli();
    usbDeviceDisconnect();
    usbDeviceConnect();


    usbInit();

    sei();

    // TODO: Remove the next two lines once we fix
    //       missing first keystroke bug properly.
    memset(reportBuffer, 0, sizeof(reportBuffer));
    usbSetInterrupt(reportBuffer, sizeof(reportBuffer));
    setLayout(layout);
}

bool UsbKeyboardDevice::isUsbReady()
{
    UsbKeyboard.update();
    return usbInterruptIsReady();
}

void UsbKeyboardDevice::setLayout(const char* layout)
{
    delete _layout;
    _layout = new char[strlen(layout)];
    strcpy(_layout, layout);
}

int UsbKeyboardDevice::charModAltGr(char c, int* modifier)
{
    *modifier = MOD_ALT_RIGHT;
    return c;
}

int UsbKeyboardDevice::charModShift(char c, int* modifier)
{
    *modifier = MOD_SHIFT_LEFT;
    return c;
}

#ifdef ARD_USBKBD_AZERTY
int UsbKeyboardDevice::charToKeyAzerty(int c, int* modifier)
{
    *modifier = 0;

    if (c == '0')
        return charModShift(KEY_0, modifier);
    if (c >= '1' && c <= '9')
        return charModShift(KEY_1 + c - '1', modifier);

    if (c == '\n')
        return KEY_ENTER;
    if (c == ' ')
        return KEY_SPACE;


    if (c >= 'a' && c <= 'z')
    {
        if (c == 'a')
            c = 'q';
        else if (c == 'm')
            return KEY_SEMICOLON;
        else if (c == 'q')
            c = 'a';
        else if (c == 'w')
            c = 'z';
        else if (c == 'z')
            c = 'w';
        return KEY_A + c - 'a';
    }
    if (c >= 'A' && c <= 'Z')
    {
        if (c == 'A')
            c = 'Q';
        else if (c == 'M')
            return charModShift(KEY_SEMICOLON, modifier);
        else if (c == 'Q')
            c = 'A';
        else if (c == 'W')
            c = 'Z';
        else if (c == 'Z')
            c = 'W';
        return charModShift(KEY_A + c - 'A', modifier);
    }

    if (c == '~')
        return charModAltGr(KEY_2, modifier);
    if (c == '#')
        return charModAltGr(KEY_3, modifier);
    if (c == '{')
        return charModAltGr(KEY_4, modifier);
    if (c == '[')
        return charModAltGr(KEY_5, modifier);
    if (c == '|')
        return charModAltGr(KEY_6, modifier);
    if (c == '`')
        return charModAltGr(KEY_7, modifier);
    if (c == '\\')
        return charModAltGr(KEY_8, modifier);
    if (c == '^')
        return charModAltGr(KEY_9, modifier);
    if (c == '@')
        return charModAltGr(KEY_0, modifier);
    if (c == ']')
        return charModAltGr(KEY_HYPHEN, modifier);
    if (c == '}')
        return charModAltGr(KEY_EQUAL, modifier);
    if (c == -75)//µ
        return charModShift(KEY_BSLASH, modifier);
    if (c == '*')
        return KEY_BSLASH;

    if (c == '&')
        return KEY_1;
    if (c == -23)//é
        return KEY_2;
    if (c == '\"')
        return KEY_3;
    if (c == '\'')
        return KEY_4;
    if (c == '(')
        return KEY_5;
    if (c == '-')
        return KEY_6;
    if (c == -24)//è
        return KEY_7;
    if (c == '_')
        return KEY_8;
    if (c == -25)//ç
        return KEY_9;
    if (c == -32)//à
        return KEY_0;
    if (c == ')')
        return KEY_HYPHEN;
    if (c == '=')
        return KEY_EQUAL;
    if (c == '+')
        return charModShift(KEY_EQUAL, modifier);

    if (c == ',')
        return KEY_M;
    if (c == ';')
        return KEY_COMMA;
    if (c == ':')
        return KEY_DOT;
    if (c == '!')
        return KEY_SLASH;
    if (c == -7)//ù
        return KEY_QUOTE;
    if (c == '<')
        return KEYP_NUS_BSLASH;

    if (c == '?')
        return charModShift(KEY_M, modifier);
    if (c == '.')
        return charModShift(KEY_COMMA, modifier);
    if (c == '/')
        return charModShift(KEY_DOT, modifier);
    if (c == -89)//§
        return charModShift(KEY_SLASH, modifier);
    if (c == '%')
        return charModShift(KEY_QUOTE, modifier);
    if (c == '>')
        return charModShift(KEYP_NUS_BSLASH, modifier);

    return 0;
}
#endif

#ifdef ARD_USBKBD_QWERTY
int UsbKeyboardDevice::charToKeyQwerty(int c, int* modifier)
{
    *modifier = 0;
    if (c == '0')
        return KEY_0;
    if (c >= '1' && c <= '9')
        return KEY_1 + c - '1';
    if (c >= 'a' && c <= 'z')
        return KEY_A + c - 'a';
    if (c >= 'A' && c <= 'Z')
        return charModShift(KEY_A + c - 'A', modifier);

    if (c == '\n')
        return KEY_ENTER;
    if (c == ' ')
        return KEY_SPACE;


    if (c == '.')
        return KEY_DOT;
    if (c == ',')
        return KEY_COMMA;
    if (c == '/')
        return KEY_SLASH;
    if (c == ';')
        return KEY_SEMICOLON;
    if (c == '`')
        return KEY_TILDE;
    if (c == '-')
        return KEY_HYPHEN;
    if (c == '=')
        return KEY_EQUAL;
    if (c == '\'')
        return KEY_QUOTE;
    if (c == '~')
        return charModShift(KEY_TILDE, modifier);
    if (c == '<')
        return charModShift(KEY_COMMA, modifier);
    if (c == '>')
        return charModShift(KEY_DOT, modifier);
    if (c == '?')
        return charModShift(KEY_SLASH, modifier);
    if (c == ':')
        return charModShift(KEY_SEMICOLON, modifier);

    if (c == '!')
        return charModShift(KEY_1, modifier);
    if (c == '@')
        return charModShift(KEY_2, modifier);
    if (c == '#')
        return charModShift(KEY_3, modifier);
    if (c == '$')
        return charModShift(KEY_4, modifier);
    if (c == '%')
        return charModShift(KEY_5, modifier);
    if (c == '^')
        return charModShift(KEY_6, modifier);
    if (c == '&')
        return charModShift(KEY_7, modifier);
    if (c == '*')
        return charModShift(KEY_8, modifier);
    if (c == '(')
        return charModShift(KEY_9, modifier);
    if (c == ')')
        return charModShift(KEY_0, modifier);
    if (c == '_')
        return charModShift(KEY_HYPHEN, modifier);
    if (c == '+')
        return charModShift(KEY_EQUAL, modifier);
    if (c == '"')
        return charModShift(KEY_QUOTE, modifier);

    if (c == '{')
        return charModShift(KEY_LBRACKET, modifier);
    if (c == '}')
        return charModShift(KEY_RBRACKET, modifier);
    if (c == '|')
        return charModShift(KEY_BSLASH, modifier);

    if (c == '[')
        return KEY_LBRACKET;
    if (c == ']')
        return KEY_RBRACKET;
    if (c == '\\')
        return KEY_BSLASH;
    return 0;
}
#endif

void UsbKeyboardDevice::sendKeyStrokes(const char* str)
{
    int (*charToKey)(int,int*) = 0;
#ifdef ARD_USBKBD_AZERTY
    if (!strcmp(_layout, "fr"))
    {
        charToKey = charToKeyAzerty;
    }
#endif
#ifdef ARD_USBKBD_QWERTY
    if (!strcmp(_layout, "us"))
    {
        charToKey = charToKeyQwerty;
    }
#endif
    if (!charToKey)
    {
        return;
    }

    while (*str)
    {
        int modifier = 0;
        int k = charToKey(*str, &modifier);
        /*if (!k)
        {
          k = KEY_SPACE;
          char buf[12];
          itoa((unsigned)*str, buf, 10);
          sendKeyStrokes(buf);
        }*/
        if (k)
        {
            UsbKeyboard.sendKeyStroke(k, modifier);
        }
        ++str;
    }
}

void UsbKeyboardDevice::sendKeyStroke(byte keyStroke, byte modifiers)
{

    while (!usbInterruptIsReady()) {
        // Note: We wait until we can send keystroke
        //       so we know the previous keystroke was
        //       sent.
    }

    memset(reportBuffer, 0, sizeof(reportBuffer));

    reportBuffer[0] = modifiers;
    reportBuffer[1] = keyStroke;

    usbSetInterrupt(reportBuffer, sizeof(reportBuffer));

    while (!usbInterruptIsReady()) {
        // Note: We wait until we can send keystroke
        //       so we know the previous keystroke was
        //       sent.
    }

    // This stops endlessly repeating keystrokes:
    memset(reportBuffer, 0, sizeof(reportBuffer));
    usbSetInterrupt(reportBuffer, sizeof(reportBuffer));

}


uchar usbFunctionSetup(uchar data[8])
{
    usbRequest_t    *rq = (usbRequest_t *)((void *)data);

    usbMsgPtr = UsbKeyboard.reportBuffer; //
    if((rq->bmRequestType & USBRQ_TYPE_MASK) == USBRQ_TYPE_CLASS){
        /* class request type */

        if(rq->bRequest == USBRQ_HID_GET_REPORT){
            /* wValue: ReportType (highbyte), ReportID (lowbyte) */

            /* we only have one report type, so don't look at wValue */
            // TODO: Ensure it's okay not to return anything here?
            return 0;

        }else if(rq->bRequest == USBRQ_HID_GET_IDLE){
            //            usbMsgPtr = &idleRate;
            //            return 1;
            return 0;
        }else if(rq->bRequest == USBRQ_HID_SET_IDLE){
            idleRate = rq->wValue.bytes[1];
        }
    }else{
        /* no vendor specific requests implemented */
    }
    return 0;
}