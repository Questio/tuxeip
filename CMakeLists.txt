cmake_minimum_required(VERSION 3.1)
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

set_target_properties(tuxeip PROPERTIES PUBLIC_HEADER "src/TuxDef.h;src/CM.h;src/TuxEip.h;src/ErrCodes.h;src/MR.h;src/EIP_Const.h;src/SendData.h;src/CIP_Const.h;src/CIP_IOI.h;src/AB.h;src/LGX.h;src/PLC.h;src/CIP_Types.h;src/CIP_Objects.h;src/Ethernet_IP.h")

install(TARGETS tuxeip
	LIBRARY DESTINATION lib
	PUBLIC_HEADER DESTINATION include/tuxeip)
