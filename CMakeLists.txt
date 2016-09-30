cmake_minimum_required(VERSION 2.6)
project(tuxeip)

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
