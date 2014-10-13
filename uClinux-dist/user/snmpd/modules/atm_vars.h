#ifndef		_ATMVARS_H_
#define		_ATMVARS_H_

CVoidType	admInit (void);


/*
 * MIB entry declarations 
 */

// atmMIB.1
#define ATMINTERFACECONFTABLE					2
#define ATMTRAFFICDESCRPARAMTABLE			5
#define ATMVCLTABLE								7
#define AAL5VCCTABLE							12
#define ATMTRAFFICDESCRPARAMINDEXNEXT		13

// atmMIB.1.2.1
#define ATMINTERFACECONFTABLENUM				15

#define ATMINTERFACEMAXVPCS					1
#define ATMINTERFACEMAXVCCS					2
#define ATMINTERFACECONFVPCS					3
#define ATMINTERFACECONFVCCS					4
#define ATMINTERFACEMAXACTIVEVPIBITS			5
#define ATMINTERFACEMAXACTIVEVCIBITS			6
#define ATMINTERFACEILMIVPI					7
#define ATMINTERFACEILMIVCI					8
#define ATMINTERFACEADDRESSTYPE				9
#define ATMINTERFACEADMINADDRESS				10
#define ATMINTERFACEMYNEIGHBORIPADDRESS		11
#define ATMINTERFACEMYNEIGHBORIFNAME		12
#define ATMINTERFACECURRENTMAXVPIBITS		13
#define ATMINTERFACECURRENTMAXVCIBITS		14
#define ATMINTERFACESUBSCRADDRESS			15

// atmMIB.1.5.1
#define ATMTRAFFICDESCRPARAMTABLENUM		10

#define ATMTRAFFICDESCRTYPE					2
#define ATMTRAFFICDESCRPARAM1					3
#define ATMTRAFFICDESCRPARAM2					4
#define ATMTRAFFICDESCRPARAM3					5
#define ATMTRAFFICDESCRPARAM4					6
#define ATMTRAFFICDESCRPARAM5					7
#define ATMTRAFFICQOSCLASS					8
#define ATMTRAFFICDESCRROWSTATUS				9
#define ATMSERVICECATEGORY					10
#define ATMTRAFFICFRAMEDISCARD				11

// atmMIB.1.7.1
#define ATMVCLTABLENUM							13

#define ATMVCLADMINSTATUS						3
#define ATMVCLOPERSTATUS						4
#define ATMVCLLASTCHANGE						5
#define ATMVCLRECEIVETRAFFICDESCRINDEX		6
#define ATMVCLTRANSMITTRAFFICDESCRINDEX		7
#define ATMVCCAALTYPE							8
#define ATMVCCAAL5CPCSTRANSMITSDUSIZE		9
#define ATMVCCAAL5CPCSRECEIVESDUSIZE			10
#define ATMVCCAAL5ENCAPSTYPE					11
#define ATMVCLCROSSCONNECTIDENTIFIER			12
#define ATMVCLROWSTATUS						13
#define ATMVCLCASTTYPE							14
#define ATMVCLCONNKIND 						15

// atmMIB.1.12.1
#define AAL5VCCTABLENUM						3

#define AAL5VCCCRCERRORS						3
#define AAL5VCCSARTIMEOUTS					4
#define AAL5VCCOVERSIZEDSDUS					5

// atmMIB.1.13.0
#define ATMTRAFFICDESCRPARAMINDEXNEXTNUM	1

#endif
