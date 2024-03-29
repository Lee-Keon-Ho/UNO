#pragma once

enum ePacketType
{
	CS_PT_LOGIN = 1,
	CS_PT_CREATEROOM,
	CS_PT_USERLIST,
	CS_PT_ROOMLIST,
	CS_PT_INROOM,
	CS_PT_OUTROOM,
	CS_PT_ROOMSTATE,
	CS_PT_CHATTING,
	CS_PT_READY,
	CS_PT_START,
	CS_PT_DRAWCARD,
	CS_PT_TAKECARD,
	CS_PT_CHOISECOLOR,
	CS_PT_RESET,
	CS_PT_LOGOUT,
	CS_PT_QUICKROOM,
	CS_PT_MAX
};