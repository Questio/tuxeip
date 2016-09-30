cmake_minimum_required(VERSION 2.6)
project(tuxeip)
set(tuxeip_VERSION_MAJOR 1)
set(tuxeip_VERSION_MINOR 0)

add_library(tuxeip SHARED src/AB.cpp
			  src/CIP_IOI.cpp
			  src/CM.cpp
			  src/ErrCodes.cpp
			  src/Ethernet_IP.cpp
			  src/LGX.cpp
			  src/MR.cpp
			  src/PLC.cpp
			  src/SendData.cpp)

install(TARGETS tuxeip DESTINATION lib)
