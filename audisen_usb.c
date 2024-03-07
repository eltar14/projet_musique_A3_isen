/**
 * @authors Antoine LE BOULCH / Julia AZEAU CIR3 Caen
 */
#define _WIN32
#include <stdio.h>
#include "amp.h"
#include "ams.h"
#include "frame.h"
#include "usb.h"
#include "ftd2xx.h"

int main(){
    printf("Demarrage du projet AUDISEN USB\n");
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    //ftHandle = initUSB();
    ftStatus = FT_Open(0, &ftHandle);
    if (ftStatus == FT_OK) {
        fprintf(stderr, "open USB ok\n");
    }else{
        fprintf(stderr, "open USB error\n");
    }
    return 0;
}