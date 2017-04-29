//
//  ofxSerialUtills.h
//
//

#ifndef ofxSerialUtills_h
#define ofxSerialUtills_h
#include "ofMain.h"

class ofxSerialUtills{
public:
    ofxSerialUtills(ofSerial& serial)
    : pSerial(&serial)
    , isSend(false)
    , selectNum(0)
    , numOfDevice(0)
    , commandConfig("select  UP/DOWN\nsetDev  RETURN\ntoggle  SPACE")
    {
    }
    
    std::string getSerialStatus(){
        std::string status;
        numOfDevice = pSerial -> getDeviceList().size();
        for(int i = 0 ; i < pSerial -> getDeviceList().size(); ++i){
            status += pSerial -> getDeviceList()[i].getDevicePath();
            if(selectNum == i){
                dev = pSerial -> getDeviceList()[i].getDevicePath();
                status += "<-";
            }
            status += "\n";
        }
        status += (isSend ? "ENABLE":"DISABLE");
        return status;
    }
    
    std::string getCommandConfig(){
        return commandConfig;
    }
    
    void keySelect(const int key){
        if(key == OF_KEY_DOWN){
            if(++selectNum > numOfDevice)
                selectNum = 0;
        }
    
        if(key == OF_KEY_UP){
            if(--selectNum < 0)
                selectNum = numOfDevice;
        }
    
        if(key == OF_KEY_RETURN){
            pSerial -> setup(dev,115200);
        }
    
        if(key == ' '){
            isSend = !isSend;
        }
    }
    
    bool isSend;
private:
    std::string commandConfig;
    ofSerial* pSerial;
    int selectNum;
    int numOfDevice;
    std::string dev;
};

#endif /* ofxSerialUtills_h */
