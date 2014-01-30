PROJECT(tuxeip)

ADD_LIBRARY(tuxeip STATIC src/AB.cpp
			  src/CIP_IOI.cpp
			  src/CM.cpp
			  src/ErrCodes.cpp
			  src/Ethernet_IP.cpp
			  src/LGX.cpp
			  src/MR.cpp
			  src/PLC.cpp
			  src/SendData.cpp)

