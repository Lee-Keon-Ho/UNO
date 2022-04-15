#include "Room.h"
#include <memory>
CRoom::CRoom()
{

}

CRoom::~CRoom()
{
	
}

void CRoom::SetRoom(wchar_t* _name)
{
	m_room.number = 0;
	memcpy(m_room.name, _name, 64);
	m_room.playerCount = 1;
	m_room.state = true;
}