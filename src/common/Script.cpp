///* 
// * File:   Script.cpp
// * Author: acailly
// * 
// * Created on 12 février 2014, 18:25
// */
//
//#include "Script.h"
//
//Script::Script()
//{
//}
//
//Script::~Script()
//{
//}
//
//void Script::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
//{
//    //------------------------------------------------------------------
//    // READ SCRIPT FILE 
//    //------------------------------------------------------------------
//    QString inScriptFileName;
//    if (inputs.GetValue("SCRIPT", inScriptFileName))
//    {
//        QFile scriptFile(inScriptFileName);
//        if (scriptFile.open(QIODevice::ReadOnly)) {
//            QTextStream in(&scriptFile);
//            script = in.readAll();
//            scriptFile.close();
//        }
//    }
//        
//    //------------------------------------------------------------------
//    // EXECUTE THE SCRIPT 
//    //------------------------------------------------------------------
//    //Read the input
//    //TODO ACY 
//    
//    //Reset the output
////    scriptEngine.globalObject().setProperty("_out", "");
//    //TODO ACY Trouver un moyen de passer un QVariant qui puisse être modifié dans le script
//    
//    //Execute
//    scriptEngine.evaluate(script);
//    
//    //Get the output
////    QScriptValue output = scriptEngine.globalObject().property("_out");
////    output.toVariant();
//    //TODO ACY
//}
