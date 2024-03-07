/**
 * @authors Antoine LE BOULCH / Julia AZEAU CIR3 Caen
 */

#include "define.h"
#include "frame.h"
#include "ftd2xx.h"
#include "usb.h"


FT_HANDLE initUSB(){
    FT_HANDLE ftHandle;
    FT_STATUS ftStatus;
    //LONG lComPortNumber;


    // FT_Open ============================
    ftStatus = FT_Open(0, &ftHandle);
    if (ftStatus == FT_OK) {
        fprintf(stderr, "open USB ok\n");

        // Set read timeout of 5sec, write timeout of 1sec
        ftStatus = FT_SetTimeouts(ftHandle, 5000, 1000);
        // Set baud rate
        ftStatus = FT_SetBaudRate(ftHandle, 9600);

        ftStatus = FT_SetDataCharacteristics(ftHandle,
        FT_BITS_8,
        FT_STOP_BITS_1,
        FT_PARITY_NONE);

        ftStatus = FT_SetFlowControl(ftHandle, FT_FLOW_NONE, 0x0, 0x0);


    }else{
        fprintf(stderr, "open USB error\n");
    }



/*
// FT_GetComPortNumber ================
        ftStatus = FT_GetComPortNumber(ftHandle,&lComPortNumber);
        if (ftStatus == FT_OK) {
            if (lComPortNumber == -1) {
                // No COM port assigned
                printf("No COM port assigned\n");
            }
            else {
                // COM port assigned with number held in lComPortNumber
                printf("COM port is %d\n", lComPortNumber);
            }
        }
        else {
            // FT_GetComPortNumber FAILED!
            printf("FT_GetComPortNumber FAILED\n");
        }
 */


    // FT_GetDeviceInfo ===================
    /*
    ftStatus = FT_GetDeviceInfo(
            ftHandle,
            &ftDevice,
            &deviceID,
            SerialNumber,
            Description,
            NULL
    );
    if (ftStatus == FT_OK) {
        // FT_GetDeviceInfo OK, use ftHandle to access device
        printf("FT_GetDeviceInfo OK.\n");
    }
    else {
        // FT_GetDeviceInfo failed
    }
 */


    return ftHandle;

}
void closeUSB(FT_HANDLE ftHandle){
    FT_Close(ftHandle);
}


void writeUSB(char* frame, FT_HANDLE ftHandle){
    FT_STATUS ftStatus;
    DWORD BytesWritten;
    //LONG lComPortNumber;

    // GETCOMPORTNULBER =================================================

    //ftStatus = FT_GetComPortNumber(ftHandle,&lComPortNumber);



    // FTWRITE ===========================================================

    ftStatus = FT_Write(ftHandle, frame, sizeof(frame), &BytesWritten, NULL);
    if (ftStatus == FT_OK) {
        // FT_Write OK
        printf("Write OK \n");
    }
    else {
        // FT_Write Failed
        printf("Write Failed \n");
    }

}