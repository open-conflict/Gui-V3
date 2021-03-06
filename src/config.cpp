#include "config.h"

DashBoard dashDummy;

Config::Config(){
    int size;
    settings = new QSettings("config.ini", QSettings::IniFormat);
    qDebug() << "lade ini";

    /* ======= COM PORT ========= */

    settings->beginGroup("com");
    com_port = readQString("com1",settings->value("port").toString());
    com_baud = readInt(57600,settings->value("baud").toString());
    settings->endGroup();
    qDebug() << com_baud;
    qDebug() << com_port;

    /* ======= DASH ========= */

    settings->beginGroup("dash");

    defaultDash.type =          readQString("lcd",      settings->value("type").toString());
    defaultDash.name =          readQString("default",      settings->value("name").toString());
    defaultDash.colorOk =       readSplitQString("green",    settings->value("color").toString(),",",0);
    defaultDash.colorWarn =     readSplitQString("orange",   settings->value("color").toString(),",",1);
    defaultDash.colorError =    readSplitQString("red",      settings->value("color").toString(),",",2);
    defaultDash.rangeStart =    readSplitQString("0",        settings->value("range").toString(),",",0);
    defaultDash.rangeEnd =      readSplitQString("0",        settings->value("range").toString(),",",1);
    defaultDash.limitOk =       readSplitQString("40",       settings->value("limit").toString(),",",0);
    defaultDash.limitWarn =     readSplitQString("50",       settings->value("limit").toString(),",",1);
    defaultDash.limitAlarm =    readSplitQString("65",       settings->value("limit").toString(),",",2);

    size = settings->beginReadArray("widget");
    for (int i = 0; i < size; ++i) {
        settings->setArrayIndex(i);
        if(settings->value("value").toString() != ""){
            dashDummy.type =           readQString(defaultDash.type,      settings->value("type").toString());
            dashDummy.value =          settings->value("value").toString();
            dashDummy.name =           readQString(defaultDash.name,      settings->value("name").toString());
            dashDummy.colorOk =        readSplitQString(defaultDash.colorOk,         settings->value("color").toString(),",",0);
            dashDummy.colorWarn =      readSplitQString(defaultDash.colorWarn,       settings->value("color").toString(),",",1);
            dashDummy.colorError =     readSplitQString(defaultDash.colorError,      settings->value("color").toString(),",",2);
            dashDummy.rangeStart =     readSplitQString(defaultDash.rangeStart,      settings->value("range").toString(),",",0);
            dashDummy.rangeEnd =       readSplitQString(defaultDash.rangeEnd,        settings->value("range").toString(),",",1);
            dashDummy.limitOk =        readSplitQString(defaultDash.limitOk,         settings->value("limit").toString(),",",0);
            dashDummy.limitWarn =      readSplitQString(defaultDash.limitWarn,       settings->value("limit").toString(),",",1);
            dashDummy.limitAlarm =     readSplitQString(defaultDash.limitAlarm,      settings->value("limit").toString(),",",2);
            dash.append(dashDummy);
        }
    }
    settings->endArray();
    settings->endGroup();

    /* ======= DISPLAY ========= */

    // %m		  : Minute 2 Char
    // %h		  : Hour 2 Char
    // %s		  : Seconds 2 Char
    displayReplace.append({"%h","\xc1\x01",2});
    displayReplace.append({"%m","\xc1\x02",2});
    displayReplace.append({"%s","\xc1\x03",2});

    // %t01 - %t24 : Teperatur 4 Char
    displayReplace.append({"%t01","\xc0\x01\x00\x00",4});
    displayReplace.append({"%t02","\xc0\x02\x00\x00",4});
    displayReplace.append({"%t03","\xc0\x03\x00\x00",4});
    displayReplace.append({"%t04","\xc0\x04\x00\x00",4});
    displayReplace.append({"%t05","\xc0\x05\x00\x00",4});
    displayReplace.append({"%t06","\xc0\x06\x00\x00",4});
    displayReplace.append({"%t07","\xc0\x07\x00\x00",4});
    displayReplace.append({"%t08","\xc0\x08\x00\x00",4});
    displayReplace.append({"%t09","\xc0\x09\x00\x00",4});
    displayReplace.append({"%t10","\xc0\x10\x00\x00",4});
    displayReplace.append({"%t11","\xc0\x11\x00\x00",4});
    displayReplace.append({"%t12","\xc0\x12\x00\x00",4});
    displayReplace.append({"%t13","\xc0\x13\x00\x00",4});
    displayReplace.append({"%t14","\xc0\x14\x00\x00",4});
    displayReplace.append({"%t15","\xc0\x15\x00\x00",4});
    displayReplace.append({"%t16","\xc0\x16\x00\x00",4});
    displayReplace.append({"%t17","\xc0\x17\x00\x00",4});
    displayReplace.append({"%t18","\xc0\x18\x00\x00",4});
    displayReplace.append({"%t19","\xc0\x19\x00\x00",4});
    displayReplace.append({"%t20","\xc0\x20\x00\x00",4});
    displayReplace.append({"%t21","\xc0\x21\x00\x00",4});
    displayReplace.append({"%t22","\xc0\x22\x00\x00",4});
    displayReplace.append({"%t23","\xc0\x23\x00\x00",4});
    displayReplace.append({"%t24","\xc0\x24\x00\x00",4});

    // %cpu       : CPU Clock 4 char
    displayReplace.append({"%cpu","\xc2\x01\x00\x00",4});

    // %cp        : CPU usage 3 char
    // %gp        : GPU usage 3 char
    // %ra        : RAM usage 3 char
    displayReplace.append({"%cp","\xc3\x01\x00",3});
    displayReplace.append({"%gp","\xc3\x02\x00",3});
    displayReplace.append({"%ra","\xc3\x03\x00",3});

    // %wf        : water flow 3 char
    displayReplace.append({"%wf","\xc4\1\0\0",4});

    // %rp1 - %rp4 : FAN RPM 4 char
    displayReplace.append({"%rp1","\xc5\x01\x00\x00",4});
    displayReplace.append({"%rp2","\xc5\x02\x00\x00",4});
    displayReplace.append({"%rp3","\xc5\x03\x00\x00",4});
    displayReplace.append({"%rp4","\xc5\x04\x00\x00",4});

    // %p1  - %p4  : FAN Power 3 char
    displayReplace.append({"%p1","\xc6\x01\x00",3});
    displayReplace.append({"%p2","\xc6\x02\x00",3});
    displayReplace.append({"%p3","\xc6\x03\x00",3});

    settings->beginGroup("display");
    size = settings->beginReadArray("lcd");
    qDebug() << size;
    for (int i = 0; i < size; ++i) {
        settings->setArrayIndex(i);
        display.append(displayString(settings->value("row1").toString()));
        display.append(displayString(settings->value("row2").toString()));
        display.append(displayString(settings->value("row3").toString()));
    }
    settings->endArray();
    settings->endGroup();

    displayArray = display.toLatin1();

    foreach( DisplayReplace rep, displayReplace ){
        int index = 0;
        int rounds = 0;
        while(display.indexOf(rep.before,index) != -1 && rounds < 5){
            index = display.indexOf(rep.before,index);
            displayArray.replace(index,rep.lenght, rep.after.data(),rep.lenght);
            rounds++;
        }
    }

    qDebug() << displayArray.toHex();


}

QString Config::displayString(QString str){
    QString s;
    int i;
    if(str.count() == 16){
        qDebug() << "16 zeichen";
        return str;
    }else{
        qDebug() << str.count() << " zeichen";
        return QString("                ");
    }
}

QString Config::readQString(QString def, QString str){
    if(str == "")
        return def;
    else
        return str;
}

QString Config::readSplitQString(QString def, QString str, QString splitChar,int index){
    QStringList sl;
    if(str == "")
        return def;
    else
        sl = str.split(",");
        qDebug() << "size: " << sl.size() << " index: " << index;
        if(sl.size() <= index){
            return def;
        }else{
            return sl[index];
        }
}

int Config::readInt(int def, QString str){
    if(str == "")
        return def;
    else
        return str.toInt();
}
