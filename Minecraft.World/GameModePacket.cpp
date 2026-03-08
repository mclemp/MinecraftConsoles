#include "stdafx.h"
#include "GameModePacket.h"
#include "DataInputStream.h"
#include "DataOutputStream.h"

GameModePacket::GameModePacket()
{
	m_message = (EMessage)0;
}

shared_ptr<Packet> GameModePacket::create()
{
	return shared_ptr<Packet>(new GameModePacket());
}

shared_ptr<GameModePacket> GameModePacket::Create(EMessage msg, const Data &data)
{
	shared_ptr<GameModePacket> packet(new GameModePacket());
	packet->m_message = msg;
	return packet;
}

void GameModePacket::read(DataInputStream *dis)
{
	m_message = (EMessage)dis->readInt();
}

void GameModePacket::write(DataOutputStream *dos)
{
	dos->writeInt((int)m_message);
}

void GameModePacket::handle(PacketListener *listener)
{
}

void GameModePacket::AddAreaBoundsData::ReadPacket(shared_ptr<GameModePacket> packet)
{
}

void GameModePacket::AddAreaBoundsData::WritePacket(shared_ptr<GameModePacket> packet) const
{
}

void GameModePacket::LockPlayerLocation::ReadPacket(shared_ptr<GameModePacket> packet)
{
}

void GameModePacket::LockPlayerLocation::WritePacket(shared_ptr<GameModePacket> packet) const
{
}
