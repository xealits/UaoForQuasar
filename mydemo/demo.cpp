/*
 * demo.cpp
 *
 *  Created on: 25 Oct 2017
 *      Author: pnikiel
 *
 *    This is a small demo program
 *    that illustrates how you can use your
 *    generated client.
 */

// the following defines OpcUa_StatusCode
//#include <opcua_p_types.h>
///home/itkfelixstrips/software/opcua_quasar/temp2/ua-sdk/include/uastack/opcua_p_types.h:40:2: error: #error OPCUA_P_BYTE_ORDER not defined
//   40 | #error OPCUA_P_BYTE_ORDER not defined

// instead just copy OpcUa types:
#include <cstddef>
#include <cstdint>

typedef int                 OpcUa_Int;
typedef unsigned int        OpcUa_UInt;
typedef void                OpcUa_Void;
typedef void*               OpcUa_Handle;
typedef unsigned char       OpcUa_Boolean;
typedef int8_t              OpcUa_SByte;
typedef uint8_t             OpcUa_Byte;
typedef int16_t             OpcUa_Int16;
typedef uint16_t            OpcUa_UInt16;
typedef int32_t             OpcUa_Int32;
typedef uint32_t            OpcUa_UInt32;
typedef int64_t             OpcUa_Int64;
typedef uint64_t            OpcUa_UInt64;
typedef float               OpcUa_Float;
typedef double              OpcUa_Double;
typedef char                OpcUa_CharA;
typedef unsigned char       OpcUa_UCharA;
typedef unsigned short      OpcUa_Char;
typedef intptr_t            OpcUa_IntPtr;
typedef uintptr_t           OpcUa_UIntPtr;
typedef size_t              OpcUa_Size_t;

#define OpcUa_StringA char*

//struct _OpcUa_DateTime
//{
//    OpcUa_UInt32 dwLowDateTime;
//    OpcUa_UInt32 dwHighDateTime;
//};
//typedef struct _OpcUa_DateTime OpcUa_DateTime;

/**
 * @brief The handle for the platform thread.
 */
typedef OpcUa_UInt32    OpcUa_StatusCode;


// the following file is provided with UaoForQuasar
#include <ClientSessionFactory.h>

// the following comes from generation
// you might need to use another class
//#include <HilariousClass.h>
#include <LpGBT.h>

#include <uaplatformlayer.h>
#include <iostream>


#include <map>
#include <string>
#include <functional>

//dataType="OpcUa_Boolean"
//dataType="OpcUa_Double"
//dataType="OpcUa_Int16"
//dataType="OpcUa_Int32"
//dataType="OpcUa_Int64"
//dataType="UaString"

union OpcData {
	OpcUa_Boolean b;
	OpcUa_Double d;
	OpcUa_Int16 i16;
	OpcUa_Int32 i32;
	OpcUa_Int64 i64;
	UaString s;


	OpcData() { new(&s) std::string(); }
	OpcData(const OpcData& other) { b = other.b; d = other.d; i16 = other.i16; i32 = other.i32; i64 = other.i64; new(&s) auto(other.s); }
	~OpcData() {}
};


std::map<std::string, std::function<OpcData(UaoClient::LpGBT&)>> _comline_lambdas_LpGBT = {
  //{"hostname", [](UaoClient::LpGBT& dev) -> union OpcData {union OpcData res; res.s = dev.readhostname(); return res;}},
  //{"portRX", [](UaoClient::LpGBT& dev) -> union OpcData {union OpcData res; res.i16 = dev.readportRX(); return res;}},
  //{"portTX", [](UaoClient::LpGBT& dev) -> union OpcData {union OpcData res; res.i16 = dev.readportTX(); return res;}},
  //{"elinkRX", [](UaoClient::LpGBT& dev) -> union OpcData {union OpcData res; res.i16 = dev.readelinkRX(); return res;}},
  //{"elinkTX", [](UaoClient::LpGBT& dev) -> union OpcData {union OpcData res; res.i16 = dev.readelinkTX(); return res;}},
  {"Path", [](UaoClient::LpGBT& dev) -> union OpcData {union OpcData res; res.s = dev.readPath(); return res;}},
  {"State", [](UaoClient::LpGBT& dev) -> union OpcData {union OpcData res; res.s = dev.readState(); return res;}},
  {"Status", [](UaoClient::LpGBT& dev) -> union OpcData {union OpcData res; res.s = dev.readStatus(); return res;}},
  {"VDAC", [](UaoClient::LpGBT& dev) -> union OpcData {union OpcData res; res.i32 = dev.readVDAC(); return res;}},
  {"Temp", [](UaoClient::LpGBT& dev) -> union OpcData {union OpcData res; res.i16 = dev.readTemp(); return res;}},
  {"Reconfigure", [](UaoClient::LpGBT& dev) -> union OpcData {union OpcData res; res.b = dev.readReconfigure(); return res;}},
  {"ConfigFile", [](UaoClient::LpGBT& dev) -> union OpcData {union OpcData res; res.s = dev.readConfigFile(); return res;}},
  //{"SecLpGBTPort", [](UaoClient::LpGBT& dev) -> union OpcData {union OpcData res; res.i16 = dev.readSecLpGBTPort(); return res;}},
  //{"SecLpGBTConfigFile", [](UaoClient::LpGBT& dev) -> union OpcData {union OpcData res; res.s = dev.readSecLpGBTConfigFile(); return res;}},
  //{"SecLpGBTI2C", [](UaoClient::LpGBT& dev) -> union OpcData {union OpcData res; res.i16 = dev.readSecLpGBTI2C(); return res;}}
};

std::map<std::string, std::string> _comline_types_LpGBT = {
  {"hostname", "UaString"},
  {"portRX", "OpcUa_Int16"},
  {"portTX", "OpcUa_Int16"},
  {"elinkRX", "OpcUa_Int16"},
  {"elinkTX", "OpcUa_Int16"},
  {"Path", "UaString"},
  {"State", "UaString"},
  {"Status", "UaString"},
  {"VDAC", "OpcUa_Int32"},
  {"Temp", "OpcUa_Int16"},
  {"Reconfigure", "OpcUa_Boolean"},
  {"ConfigFile", "UaString"},
  {"SecLpGBTPort", "OpcUa_Int16"},
  {"SecLpGBTConfigFile", "UaString"},
  {"SecLpGBTI2C", "OpcUa_Int16"}
};



int main()
{
    UaPlatformLayer::init();

    UaClientSdk::UaSession* session = ClientSessionFactory::connect("opc.tcp://127.0.0.1:4841");
    if (!session)
        return -1;

    //HilariousClass hc (session, UaNodeId("hc1",2));
    UaoClient::LpGBT lpgbt (session, UaNodeId("fibreB.lpGBT", 2)); // what is "2"? should it be fibreA/lpGBT ?
    while(1)
    {
        //std::cout << "value=" << hc.readHilariousVariable() << std::endl;
        //std::cout << "value readStatus =" << lpgbt.readStatus().toUtf8() << std::endl;
        std::string variable_name = "Status";
        auto res = _comline_lambdas_LpGBT[variable_name](lpgbt);

        const std::string& variable_type = _comline_types_LpGBT[variable_name];
        // TODO: make a proper variant-like class out of it?
        if      (variable_type == "UaString")
            std::cout << "value read" << variable_name << " =" << res.s.toUtf8() << std::endl;
        else if (variable_type == "OpcUa_Int16")
            std::cout << "value read" << variable_name << " =" << std::to_string(res.i16) << std::endl;
        else if (variable_type == "OpcUa_Int32")
            std::cout << "value read" << variable_name << " =" << std::to_string(res.i32) << std::endl;
        else if (variable_type == "OpcUa_Int64")
            std::cout << "value read" << variable_name << " =" << std::to_string(res.i64) << std::endl;
        else if (variable_type == "OpcUa_Double")
            std::cout << "value read" << variable_name << " =" << std::to_string(res.d) << std::endl;
        else if (variable_type == "OpcUa_Boolean")
            std::cout << "value read" << variable_name << " =" << std::to_string(res.b) << std::endl;

        usleep(1000000);
    }
}




