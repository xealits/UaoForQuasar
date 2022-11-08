project(uaoclient_demo)

cmake_minimum_required(VERSION 2.8)

include_directories(../supplementary_include)
include_directories(../generated)

#set( OPCUA_TOOLKIT_PATH /opt/OpcUaToolkit-eval-1.5.5)
set( OPCUA_TOOLKIT_PATH /home/itkfelixstrips/software/opcua_quasar/temp2/ua-sdk)

include_directories( ${OPCUA_TOOLKIT_PATH}/include/uastack )
#include_directories( ${OPCUA_TOOLKIT_PATH}/include/uabase )
include_directories( ${OPCUA_TOOLKIT_PATH}/include/uabasecpp ) # statuscode.h with UaStatus
include_directories( ${OPCUA_TOOLKIT_PATH}/include/uapkicpp )
include_directories( ${OPCUA_TOOLKIT_PATH}/include )
include_directories( ${OPCUA_TOOLKIT_PATH}/include/platform/linux )

#link_directories( ${OPCUA_TOOLKIT_PATH}/lib/ )
#link_directories( /opt/atlas/openssl-1.1.0/lib/ ) # openssl 1.1.0
#link_directories( /opt/atlas/openssl-1.1.0/lib/ ${OPCUA_TOOLKIT_PATH}/lib/ )

file(GLOB GENERATED_SRCS ../generated/*.cpp)

add_executable(demo 
        demo.cpp 
        ../supplementary_src/ClientSessionFactory.cpp 
        ../supplementary_src/UaoExceptions.cpp  # patch
        ${GENERATED_SRCS}
        )

target_link_libraries(demo 
        #${OPCUA_TOOLKIT_PATH}/lib/libuaclient.a
        ${OPCUA_TOOLKIT_PATH}/lib/libuaclientcpp.a
        #${OPCUA_TOOLKIT_PATH}/lib/libuabase.a
        ${OPCUA_TOOLKIT_PATH}/lib/libuabasecpp.a
        #${OPCUA_TOOLKIT_PATH}/lib/libuapki.a
        ${OPCUA_TOOLKIT_PATH}/lib/libuapkicpp.a
        ${OPCUA_TOOLKIT_PATH}/lib/libuastack.so
	#${OPCUA_TOOLKIT_PATH}/lib/libxmlparser.a
	${OPCUA_TOOLKIT_PATH}/lib/libxmlparsercpp.a

        -lxml2	
        -lpthread

	-ldl
	#/opt/atlas/openssl-1.1.0/lib/libcrypto.a
	/opt/atlas/openssl-1.1.0/lib/libssl.so
	/opt/atlas/openssl-1.1.0/lib/libcrypto.so
	#-L/opt/atlas/openssl-1.1.0/lib/
        #-lcrypto
        )

#target_link_libraries(demo 
#        #${OPCUA_TOOLKIT_PATH}/lib/libuaclient.a
#        #${OPCUA_TOOLKIT_PATH}/lib/libuabase.a
#        #${OPCUA_TOOLKIT_PATH}/lib/libuapki.a
#        #${OPCUA_TOOLKIT_PATH}/lib/libuastack.so
#	#${OPCUA_TOOLKIT_PATH}/lib/libxmlparser.a
#
#        #uaclient
#        #uabase
#        #uapki
#        #uastack
#	#xmlparser
#
#        #uabase
#        #uastack
#
#        coremodule
#        uabasecpp
#        uastack
#        uaclientcpp
#        uapkicpp
#	xmlparsercpp
#
##coremodule
##coremoduled
##memory
##memoryd
##network
##networkd
##platform
##platformd
##pubsubbasecpp
##pubsubbasecppd
##pubsubmodule
##pubsubmoduled
##trace
##traced
##uabase
##uabasecpp
##uabasecppd
##uabased
##uaclientcpp
##uaclientcppd
##uaencoder
##uaencoderd
##uamodels
##uamodelsd
##uamodule
##uamoduled
##uapkicpp
##uapkicppd
##uapubsub
##uapubsubd
##uastackd
##uastack
##util
##utild
##xmlparsercpp
##xmlparsercppd
#
#
#        -lxml2	
#        -lpthread
#        -lcrypto
#        )
