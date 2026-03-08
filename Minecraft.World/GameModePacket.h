#pragma once

#include "Packet.h"

class GameModePacket : public Packet, public enable_shared_from_this<GameModePacket>
{
public:
	enum EMessage
	{
		MSG_CLEAR_AREA_BOUNDS = 0x0C,
		MSG_ADD_AREA_BOUNDS = 0x0D,
		MSG_RESET_AREA_BOUNDS = 0x0F,
		MSG_LOCK_PLAYER_LOCATION = 0x13
	};

	class Data
	{
	public:
		virtual ~Data() {}
		virtual void ReadPacket(shared_ptr<GameModePacket> packet) = 0;
		virtual void WritePacket(shared_ptr<GameModePacket> packet) const = 0;
	};

	class EmptyData : public Data
	{
	public:
		EmptyData() {}
		void ReadPacket(shared_ptr<GameModePacket> packet) {}
		void WritePacket(shared_ptr<GameModePacket> packet) const {}
	};

	class AddAreaBoundsData : public Data
	{
	public:
		AddAreaBoundsData(int minX, int minY, int minZ, int maxX, int maxY, int maxZ)
			: m_minX(minX), m_minY(minY), m_minZ(minZ)
			, m_maxX(maxX), m_maxY(maxY), m_maxZ(maxZ) {}

		void ReadPacket(shared_ptr<GameModePacket> packet);
		void WritePacket(shared_ptr<GameModePacket> packet) const;

		int m_minX, m_minY, m_minZ;
		int m_maxX, m_maxY, m_maxZ;
	};

	class LockPlayerLocation : public Data
	{
	public:
		LockPlayerLocation(bool lock) : m_lock(lock) {}

		void ReadPacket(shared_ptr<GameModePacket> packet);
		void WritePacket(shared_ptr<GameModePacket> packet) const;

		bool m_lock;
	};

	GameModePacket();

	static shared_ptr<Packet> create();
	static shared_ptr<GameModePacket> Create(EMessage msg, const Data &data);

	virtual int getId() { return 159; }
	virtual int getEstimatedSize() { return 4; }
	virtual void read(DataInputStream *dis);
	virtual void write(DataOutputStream *dos);
	virtual void handle(PacketListener *listener);

	EMessage m_message;
};
