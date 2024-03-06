/**
 * @authors Antoine LE BOULCH / Julia AZEAU CIR3 Caen
 */

#include <stdio.h>
#include "autotests.h"


int main(){
    printf("Demarrage du projet AUDISEN\n");

    testFrame(); // 100%
    testReadAMP(); // 100%
    testReadAMS(); // 100%
    testCreateAMS();

    return 0;
}