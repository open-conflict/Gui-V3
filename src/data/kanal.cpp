#include "kanal.h"

Kanal::Kanal() : Data(){
    int i;
    // intValue Arrays Initialisierung
    for(i = 0;i<24;i++){
        maxTemp[i].max = 255;
        maxTemp[i].min = 0;
        maxTemp[i].value = 255;
        maxTemp[i].type = TYPE_SETUP;
        maxTemp[i].car.setIndex(i+1);

        minTemp[i].max = 255;
        minTemp[i].min = 0;
        minTemp[i].value = 250;
        minTemp[i].type = TYPE_SETUP;
        minTemp[i].car.setIndex(i+1);
    }
    static int maxId = 0;
    this->setId(maxId + 1);
    maxId = this->id;
}

void Kanal::setId(int id){
    if(id >= 1 && id <= 4){
        this->id = id;
        int i;
        for(i = 0;i<24;i++){
            maxTemp[i].car.setId(20+id);
            minTemp[i].car.setId(10+id);
        }
        rpm.car.setIndex(id);
        power.car.setIndex(id);
        manualPower.car.setIndex(id);
        startupTime.car.setIndex(id);
        minPower.car.setIndex(id);
        autoMode.car.setIndex(id);
        stopEnabled.car.setIndex(id);
        threshold.car.setIndex(id);
        //qDebug() << "Kanal ID" << id;
    }else{
        qDebug() << "falsche Kanal ID" << id;
    }
}

void Kanal::ProcessData(Carriage *car){

    if(car->getId() == (10 + this->id)){        // min Temp
        this->SetValue(&minTemp[car->getIndex()],car->getData().toInt(),DATA_FROM_HW);
    }
    else if(car->getId() == (20 + this->id)){   // max Temp
        this->SetValue(&maxTemp[car->getIndex()],car->getData().toInt(),DATA_FROM_HW);
    }
    else if(car->getIndex() == this->id){
        switch(car->getId()){
            case 61:
                this->SetValue(&rpm,car->getData().toInt(),DATA_FROM_HW);
                break;
            case 62:
                this->SetValue(&power,car->getData().toInt(),DATA_FROM_HW);
                break;
            case 71:
                this->SetValue(&manualPower,car->getData().toInt(),DATA_FROM_HW);
                break;
            case 72:
                this->SetValue(&startupTime,car->getData().toInt(),DATA_FROM_HW);
                break;
            case 73:
                this->SetValue(&minPower,car->getData().toInt(),DATA_FROM_HW);
                break;
            case 74:
                this->SetValue(&autoMode,car->getData().toInt(),DATA_FROM_HW);
                break;
            case 75:
                this->SetValue(&stopEnabled,car->getData().toInt(),DATA_FROM_HW);
                break;
            case 76:
                this->SetValue(&threshold,car->getData().toInt(),DATA_FROM_HW);
                break;
        }
    }
}

void Kanal::RequestData(){
   emit PushToHw(new Carriage(1, 78, 1, 0));
}

/* ================================================================= *
 *                          SETTER / GETTER
 *
 * ================================================================= */
int Kanal::getManualPower(){
    return manualPower.value;
}

void Kanal::setManualPower(int value){
    this->SetValue(&manualPower, value);
}

int Kanal::getStartupTime(){
    return startupTime.value;
}

void Kanal::setStartupTime(int value){
    SetValue (&startupTime, value);
}

int Kanal::getMinPower(){
    return minPower.value;
}

void Kanal::setMinPower(int value){
    SetValue (&minPower, value);
}

int Kanal::getAutoMode(){
    return autoMode.value;
}

void Kanal::setAutoMode(int value){
    SetValue (&autoMode, value);
}

int Kanal::getStopEnabled(){
    return stopEnabled.value;
}

void Kanal::setStopEnabled(int value){
    SetValue (&stopEnabled, value);
}

int Kanal::getThreshold(){
    return threshold.value;
}

void Kanal::setThreshold(int value){
    SetValue (&threshold, value);
}

int Kanal::getPower(){
    return power.value;
}

void Kanal::setPower(int value){
    SetValue (&power, value);
}

int Kanal::getRpm(){
    return rpm.value;
}

void Kanal::setRpm(int value){
    SetValue (&rpm, value);
}

int Kanal::getMaxTemp(int tId){
    return maxTemp[tId].value;
}

void Kanal::setMaxTemp(int tId ,int value){
    SetValue (&maxTemp[tId], value);
}

void Kanal::setAllMaxTemp(int value){
    int i;
    for(i = 0; i<24;i++){
        SetValue (&maxTemp[i], value);
    }
}

int Kanal::getMinTemp(int tId){
    return minTemp[tId].value;
}

void Kanal::setMinTemp(int tId ,int value){
    SetValue (&minTemp[tId], value);
}

void Kanal::setAllMinTemp(int value){
    int i;
    for(i = 0; i<24;i++){
        SetValue (&minTemp[i], value);
    }
}
