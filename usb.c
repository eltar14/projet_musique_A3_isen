/**
 * @authors Antoine LE BOULCH / Julia AZEAU CIR3 Caen
 */

#include "define.h"
#include "frame.h"
#include "ftd2xx.h"
#include "usb.h"


FT_HANDLE initUSB() {
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    //LONG lComPortNumber;


    // FT_Open ============================
    ftStatus = FT_Open(0, &ftHandle);
    if (ftStatus == FT_OK) {
        printf("open USB ok\n");

        // Set read timeout of 5sec, write timeout of 1sec
        ftStatus = FT_SetTimeouts(ftHandle, 1000, 1000);
        if (ftStatus == FT_OK)
            printf("TO ok\n");

        // Set baud rate
        ftStatus = FT_SetBaudRate(ftHandle, 9600);
        if (ftStatus == FT_OK)
            printf("baud ok\n");

        ftStatus = FT_SetDataCharacteristics(ftHandle,
        FT_BITS_8,
        FT_STOP_BITS_1,
        FT_PARITY_NONE);


        if (ftStatus == FT_OK)
            printf("DC ok\n");

        ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0, 0);
        if (ftStatus == FT_OK)
            printf("flow ok\n");


    } else{
        fprintf(stderr, "open USB error\n");
    }
    return ftHandle;

}



/**
 * Permet de fermer ftHandle
 * @param ftHandle
 */
void closeUSB(FT_HANDLE ftHandle){
    FT_Close(ftHandle);
}



/**
 * Permet d'écrire dans la carte
 * @param frame
 * @param ftHandle
 */
void writeUSB(char* frame, FT_HANDLE ftHandle){
    FT_STATUS ftStatus;
    DWORD BytesWritten;

    // FTWRITE ===========================================================

    ftStatus = FT_Write(ftHandle, frame, sizeof(frame), &BytesWritten);
    if (ftStatus == FT_OK) {
        printf("Write OK \n");
    }
    else {
        printf("Write Failed \n");
    }

}