/***************************************************************************
 *   Copyright (C) 2006 by TuxPLC                                          *
 *   Author Stephane JEANNE s.jeanne@tuxplc.net                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef _ETHERNET_IP_H
#define _ETHERNET_IP_H

#include "TuxDef.h"
#include "CIP_Types.h"
#pragma pack (1)

typedef CIP_UINT Eip_Command;

/* from EtherNet/IP Adapdation of CIP Vol.2/ch.2 */

typedef struct _Encap_Header {
	CIP_UINT Command;                           /* encapsulation command */
	CIP_UINT Length;                            /* length of Data */
	CIP_UDINT Session_Handle;                   /* session identification */
	CIP_UDINT Status;                           /* Status code */
	CIP_DINT Sender_ContextL, Sender_ContextH;  /* information pertinent only to the sender of then command */
	CIP_UDINT Option;                           /* option flag */
} PACKED Encap_Header;

typedef struct _Eip_Item {
	CIP_UINT Type_Id;                           /* type of item encapsulated */
	CIP_UINT Length;                            /* length in BYTE of data to follow */
} PACKED Eip_Item;

typedef struct _Eip_Common_Packet {
	CIP_UINT Count;                             /* number of item to follow */
	Eip_Item Adress;                            /* adressing information */
	Eip_Item Data;                              /* encapsulated data packet */
} PACKED Eip_Common_Packet;

typedef struct _Eip_CPF {
	CIP_UINT Count;                             /* number of item to follow */
	Eip_Item Item;                              /* adressing information */
} PACKED Eip_CPF;

typedef struct _Interface_Information {
	CIP_UINT ItemTypeCode;
	CIP_UINT ItemLength;
} PACKED Interface_Information;

typedef struct _Service_Information {
	CIP_UINT ItemTypeCode;                      /* 0x0100 */
	CIP_UINT ItemLength;
	CIP_UINT Protocol_Version;                  /* version of encapsulated protocol shall be set to 1 */
	CIP_UINT Capability_Flags;
	char Name[16];
} PACKED Service_Information;

typedef struct _Identity_Information {
	CIP_UINT ItemTypeCode;                      /* 0x000C */
	CIP_UINT ItemLength;
	CIP_UINT Protocol_Version;                  /* version of encapsulated protocol shall be set to 1 */
	/* Socket Adress */
	CIP_INT Sin_family;                         /* shall be AF_INET=2 (big endian order) */
	CIP_UINT Sin_port;                          /* shall be set to the port number (big endian order) */
	CIP_UDINT Sin_adr;                          /* IP adress (big endian order) */
	CIP_USINT Sin_Zero[8];                      /* shall be 0 */
	CIP_UINT Vendor_ID;                         /* device manufacturers Vendor ID */
	CIP_UINT Device_Type;                       /* Device type of product */
	CIP_UINT Product_Code;                      /* Product code assigned with respect to device type */
	CIP_USINT Revision[2];                      /* Device revision */
	WORD Status;                                /* current status of device */
	CIP_UDINT Serial;                           /* Serial number of device */
	char Name[16];                              /* Human readable description of device */
	CIP_USINT State;                            /* current state of device */
} PACKED Identity_Information;

typedef Encap_Header ListInterface_Request;
typedef struct _ListInterface_Reply {
	Encap_Header Header;
	CIP_UINT Count;                             /* number of target items to follow */
} PACKED ListInterface_Reply;

typedef Encap_Header ListServices_Request;
typedef struct _ListServices_Reply {
	Encap_Header Header;
	CIP_UINT Count;                             /* number of target items to follow */
} PACKED ListServices_Reply;

typedef Encap_Header ListIdentity_Request;
typedef struct _ListIdentity_Reply {
	Encap_Header Header;
	CIP_UINT Count;                             /* number of target items to follow */
} PACKED ListIdentity_Reply;

typedef struct _RegisterSession_Request {
	Encap_Header Header;
	CIP_UINT Protocol_Version;                  /* requested protocol version shall be set to 1 */
	CIP_UINT Options_flags;                     /* session options shall be set to 0 */
} PACKED RegisterSession_Request;

typedef RegisterSession_Request RegisterSession_Reply;
typedef Encap_Header UnRegisterSession_Request;

typedef struct _SendData_Request {
	Encap_Header Header;
	CIP_UDINT Interface_Handle;                 /* shall be 0 for CIP */
	CIP_UINT Timeout;                           /* operation timeout */
} PACKED SendData_Request;

typedef SendData_Request SendRRData_Request;
typedef SendRRData_Request SendRRData_Reply;
typedef SendRRData_Request SendUnitData_Request;
typedef SendRRData_Reply SendUnitData_Reply;


/***************** see Vol.2/ch.2-7  ***********************/

/* --------------- Address items ------------------------- */

typedef struct _Eip_NAI {
	/* Null adress item */
	CIP_UINT Type_Id;
	CIP_UINT Length;
} PACKED Eip_NAI;
typedef Eip_NAI *PEip_NAI;

typedef struct _Eip_CAI {
	/* Connected adress item */
	CIP_UINT Type_Id;
	CIP_UINT Length;
	CIP_UDINT CID;
} PACKED Eip_CAI;
typedef Eip_CAI *PEip_CAI;

typedef struct _Eip_SAI {
	/* Sequenced adress item  -> Used for CIP transport class 0 & 1 */
	CIP_UINT Type_Id;
	CIP_UINT Length;
	CIP_UDINT CID;
	CIP_UDINT SN;
} PACKED Eip_SAI;
typedef Eip_SAI *PEip_SAI;

/* --------------- Data items ---------------------------- */

typedef struct _Eip_UDI {
	/* unconnected data item */
	CIP_UINT Type_Id; // =ItemId_UCM ($0B2)
	CIP_UINT Length;  // length in BYTE of data
} PACKED Eip_UDI;
typedef Eip_UDI *PEip_UDI;

typedef struct _Eip_CDI {
	/* connected data item */
	CIP_UINT Type_Id;
	CIP_UINT Length;
	CIP_INT Packet;
} PACKED Eip_CDI;
typedef Eip_CDI *PEip_CDI;

typedef struct _Eip_SII{
	/* socket info item */
	CIP_UINT Type_Id;
	CIP_UINT Length;
	CIP_INT Sin_family;
	CIP_UINT Sin_port;
	CIP_UDINT Sin_adr;
	CIP_UINT Sin_Zero[8];
} PACKED Eip_SII;
typedef Eip_SII *PEip_SII;

typedef struct _Eip_Session {
	int sock;
	/* Encapsulation parameters */
	CIP_UDINT Session_Handle;
	CIP_DINT Sender_ContextL,Sender_ContextH;
	/* Receive time-out */
	int timeout;
	int References;
	void *Data;
} PACKED Eip_Session;

typedef struct _Eip_Connection{
	/* Connected send parameters */
	Eip_Session *Session;
	int References;
	void *Data;
	CIP_UINT ConnectionSerialNumber;
	CIP_UINT OriginatorVendorID;
	CIP_UDINT OriginatorSerialNumber;
	CIP_UDINT OT_ConnID;
	CIP_UDINT TO_ConnID;
	CIP_INT packet;
	BYTE Path_size;
} PACKED Eip_Connection;

/****************** Declaration of global var *********************/

#define CIP_DEFAULT_TIMEOUT 1000

/*********************** Function *********************************/

int IsEIP(void *Data);

Eip_Session *_OpenSession(char *serveur,int port,int timeout);
#define OpenSession(serveur) _OpenSession(serveur,EIP_PORT,CIP_DEFAULT_TIMEOUT);

void CloseSession(Eip_Session *session);

#define CipOpenSock(serveur) _CipOpenSock(serveur,EIP_PORT)

int _RegisterSession(Eip_Session *session);
#define RegisterSession _RegisterSession

int _UnRegisterSession(Eip_Session *session);
#define UnRegisterSession _UnRegisterSession

ListServices_Reply *_ListServices(Eip_Session *session);
#define ListServices _ListServices

ListIdentity_Reply *_ListIdentity(Eip_Session *session);
#define ListIdentity _ListIdentity

ListInterface_Reply *_ListInterfaces(Eip_Session *session);
#define ListInterfaces _ListInterfaces

int _GetItemSize(Eip_Item *item);

Encap_Header *_BuildRequest(Eip_Session *session,
	Eip_Item *adressitem,
	void *adress,
	Eip_Item *dataitem,
	void *data,
	int timeout);

int _SendData(Eip_Session *session,CIP_UINT command,
	Eip_Item *adressitem,void *adress,
	Eip_Item *dataitem,void *data);

Encap_Header *_SendData_WaitReply(Eip_Session *session,
	CIP_UINT command,
	Eip_Item *adressitem,void *adress,
	Eip_Item *dataitem,void *data);

Encap_Header *_SendRRData(Eip_Session *session,
	Eip_Item *adressitem,void *adress,
	Eip_Item *dataitem,void *data);
#define SendRRData(session,adressitem,dataitem) _SendRRData(session,adressitem,NULL,dataitem,NULL)

Encap_Header *_SendUnitData(Eip_Session *session,
	Eip_Item *adressitem,void *adress,
	Eip_Item *dataitem,void *data);
#define SendUnitData(session,adressitem,dataitem) _SendRRData(session,adressitem,NULL,dataitem,NULL)

Eip_CDI *_ConnectedSend( Eip_Session *session,
	Eip_Connection *connection,
	void *request,
	int size);
#define ConnectedSend(Connection,request,size) _ConnectedSend(Connection->Session,Connection,request,size)


CIP_UDINT _GetEipStatus(Encap_Header *header);
#define GetEipStatus(header) _GetEipStatus((Encap_Header *)header)

Eip_Common_Packet *_GetEipCommonPacket(Encap_Header *header);
#define GetEipCommonPacket(header) _GetEipCommonPacket((Encap_Header *)header)

Eip_CPF *_GetEipCPF(Encap_Header *header);
#define GetEipCPF(header) _GetEipCPF((Encap_Header *)header)

Eip_Item *_GetItem(Eip_Common_Packet *CP,int id);
#define GetItem(header,id) _GetItem(_GetEipCommonPacket((Encap_Header *)header),id)

Eip_Item *_GetAdressItem(Encap_Header *header);
#define GetAdressItem(header) _GetAdressItem((Encap_Header *)header)

Eip_Item *_GetDataItem(Encap_Header *header);
#define GetDataItem(header) _GetDataItem((Encap_Header *)header);

ListInterface_Reply *_GetInterfaces(Encap_Header *header);
#define GetInterfaces(header) _GetInterfaces((Encap_Header *)header);

ListServices_Reply *_GetServices(Encap_Header *header);
#define GetServices(header) _GetServices((Encap_Header *)header);

ListIdentity_Reply *_GetIdentity(Encap_Header *header);
#define GetIdentity(header) _GetIdentity((Encap_Header *)header);


void _InitHeader(Encap_Header *header,
	CIP_UDINT session_handle,
	CIP_DINT Sender_ContextL,
	CIP_DINT Sender_ContextH);

void _FillHeader(Encap_Header *header,CIP_UDINT session_handle,
								CIP_DINT Sender_ContextL,CIP_DINT Sender_ContextH);

int _AddHeader(Encap_Header *header,void *buffer,int size);
int _AddBYTE2Header(Encap_Header *header,BYTE value);
int _AddINT2Header(Encap_Header *header,CIP_INT value);
int _AddDINT2Header(Encap_Header *header,CIP_DINT value);
int _Addtab2Header(Encap_Header *header,BYTE *buff[],int size);

#endif /* _ETHERNET_IP_H */
