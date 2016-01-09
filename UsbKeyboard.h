/*
 * Based on Obdev's AVRUSB code and under the same license.
 *
 * TODO: Make a proper file header. :-)
 */
#ifndef __UsbKeyboard_h__
#define __UsbKeyboard_h__

#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <string.h>

#include "usbdrv.h"

// TODO: Work around Arduino 12 issues better.
//#include <WConstants.h>
//#undef int()

typedef uint8_t byte;

#define WAIT_USB do {           \
  UsbKeyboard.update();         \
  if (!usbInterruptIsReady())   \
  {                             \
    return;                     \
  }                             \
} while(0)

#define BUFFER_SIZE 4 // Minimum of 2: 1 for modifiers + 1 for keystroke 


static uchar    idleRate;           // in 4 ms units 


#include "keycodes.h"

class UsbKeyboardDevice {
 public:
  UsbKeyboardDevice (const char* layout);

  void setLayout(const char* layout);

  bool isUsbReady();
    
  void update() {
    usbPoll();
  }

  void sendKeyStrokes(const char* str);

  void sendKeyStroke(byte keyStroke) {
    sendKeyStroke(keyStroke, 0);
  }

  void sendKeyStroke(byte keyStroke, byte modifiers);

#ifdef ARD_USBKBD_AZERTY
  static int charToKeyAzerty(int, int*);
#endif

#ifdef ARD_USBKBD_QWERTY
  static int charToKeyQwerty(int, int*);
#endif
    
  //private: TODO: Make friend?
  uchar    reportBuffer[4];    // buffer for HID reports [ 1 modifier byte + (len-1) key strokes]

private:
  char* _layout;
  static int charModAltGr(char, int*);
  static int charModShift(char, int*);

};

#include "UsbKeyboard.hxx"

#endif // __UsbKeyboard_h__
