﻿/***********************************************************************************
**
** PacketManager.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef PACKETMANAGER_H
#define PACKETMANAGER_H
//----------------------------------------------------------------------------------
#include "../Globals.h"
#include "../Wisp/WispPacketReader.h"
//----------------------------------------------------------------------------------
class CPacketManager;
typedef void (CPacketManager::*PACKET_FUNCTION)();
//----------------------------------------------------------------------------------
#define ORION_SAVE_ALL_PACKETS 1

#define ORION_SAVE_PACKET 1

#if ORION_SAVE_ALL_PACKETS == 1
#define ORION_IGNORE_PACKET 1
#else
#define ORION_IGNORE_PACKET 0
#endif
//----------------------------------------------------------------------------------
//!Направление пакета
enum PACKET_DIRECTION
{
	DIR_SEND = 0,	//!От клиента серверу
	DIR_RECV,		//!От сервера клиенту
	DIR_BOTH		//!В обе стороны
};
//----------------------------------------------------------------------------------
//!Класс для хранения информации о пакетах
class CPacketInfo
{
public:
	//!Записывать ли пакет в лог
	bool save;

	//!Название пакета
	const char *Name;

	//!Размер пакета
	int Size;

	//!Направление пакета
	PACKET_DIRECTION Direction;

	//!Обработчик пакета
	PACKET_FUNCTION Handler;
};
//----------------------------------------------------------------------------------
struct HTMLGumpDataInfo
{
	int X;
	int Y;
	int Width;
	int Height;
	int TextID;
	int HaveBackground;
	int HaveScrollbar;
	int Color;
	bool IsXMF;
};
//----------------------------------------------------------------------------------
#define HANDLER_PACKET(name)void Handle ##name ()
//----------------------------------------------------------------------------------
class CPacketManager : public WISP_NETWORK::CPacketReader
{
	SETGETE(CLIENT_VERSION, ClientVersion, OnClientVersionChange);
	SETGET(string, AutoLoginNames);
	SETGET(uint, LastGumpID);
	SETGET(uint, LastGumpX);
	SETGET(uint, LastGumpY);

private:
	static CPacketInfo m_Packets[0x100];

	bool AutoLoginNameExists(const string &name);

	void AddHTMLGumps(class CGump *gump, vector<HTMLGumpDataInfo> &list);

	UINT_LIST m_MegaClilocRequests;

	deque<UCHAR_LIST> m_PluginData;

protected:
	virtual void OnPacket();

	virtual void OnReadFailed();

	//!Обработчики пакетов
	HANDLER_PACKET(LoginError);
	HANDLER_PACKET(ServerList);
	HANDLER_PACKET(RelayServer);
	HANDLER_PACKET(CharacterList);
	HANDLER_PACKET(ResendCharacterList);
	HANDLER_PACKET(LoginComplete);
	HANDLER_PACKET(SetTime);
	HANDLER_PACKET(EnterWorld);
	HANDLER_PACKET(UpdateHitpoints);
	HANDLER_PACKET(UpdateMana);
	HANDLER_PACKET(UpdateStamina);
	HANDLER_PACKET(MobileAttributes);
	HANDLER_PACKET(NewHealthbarUpdate);
	HANDLER_PACKET(UpdatePlayer);
	HANDLER_PACKET(CharacterStatus);
	HANDLER_PACKET(UpdateItem);
	HANDLER_PACKET(UpdateItemSA);
	HANDLER_PACKET(UpdateObject);
	HANDLER_PACKET(EquipItem);
	HANDLER_PACKET(UpdateContainedItem);
	HANDLER_PACKET(UpdateContainedItems);
	HANDLER_PACKET(DenyMoveItem);
	HANDLER_PACKET(DeleteObject);
	HANDLER_PACKET(UpdateCharacter);
	HANDLER_PACKET(Warmode);
	HANDLER_PACKET(PauseControl);
	HANDLER_PACKET(OpenPaperdoll);
	HANDLER_PACKET(ClientVersion);
	HANDLER_PACKET(Ping);
	HANDLER_PACKET(SetWeather);
	HANDLER_PACKET(PersonalLightLevel);
	HANDLER_PACKET(LightLevel);
	HANDLER_PACKET(EnableLockedFeatures);
	HANDLER_PACKET(OpenContainer);
	HANDLER_PACKET(UpdateSkills);
	HANDLER_PACKET(ExtendedCommand);
	HANDLER_PACKET(DenyWalk);
	HANDLER_PACKET(ConfirmWalk);
	HANDLER_PACKET(OpenUrl);
	HANDLER_PACKET(Target);
	HANDLER_PACKET(Talk);
	HANDLER_PACKET(UnicodeTalk);
	HANDLER_PACKET(ClientTalk);
	HANDLER_PACKET(MultiPlacement);
	HANDLER_PACKET(GraphicEffect);
	HANDLER_PACKET(DeathScreen);
	HANDLER_PACKET(PlaySoundEffect);
	HANDLER_PACKET(PlayMusic);
	HANDLER_PACKET(DragAnimation);
	HANDLER_PACKET(CorpseEquipment);
	HANDLER_PACKET(ASCIIPrompt);
	HANDLER_PACKET(UnicodePrompt);
	HANDLER_PACKET(CharacterAnimation);
	HANDLER_PACKET(NewCharacterAnimation);
	HANDLER_PACKET(DisplayQuestArrow);
	HANDLER_PACKET(ClientViewRange);
	HANDLER_PACKET(KrriosClientSpecial);
	HANDLER_PACKET(AssistVersion);
	HANDLER_PACKET(CharacterListNotification);
	HANDLER_PACKET(ErrorCode);
	HANDLER_PACKET(AttackCharacter);
	HANDLER_PACKET(Season);
	HANDLER_PACKET(DisplayDeath);
	HANDLER_PACKET(OpenChat);
	HANDLER_PACKET(DisplayClilocString);
	HANDLER_PACKET(MegaCliloc);
	HANDLER_PACKET(Damage);
	HANDLER_PACKET(BuffDebuff);
	HANDLER_PACKET(SecureTrading);
	HANDLER_PACKET(TextEntryDialog);
	HANDLER_PACKET(OpenMenuGump);
	HANDLER_PACKET(OpenGump);
	HANDLER_PACKET(OpenCompressedGump);
	HANDLER_PACKET(DyeData);
	HANDLER_PACKET(DisplayMap);
	HANDLER_PACKET(MapData);
	HANDLER_PACKET(TipWindow);
	HANDLER_PACKET(CharacterProfile);
	HANDLER_PACKET(BulletinBoardData);
	HANDLER_PACKET(OpenBook);
	HANDLER_PACKET(OpenBookNew);
	HANDLER_PACKET(BookData);
	HANDLER_PACKET(BuyList);
	HANDLER_PACKET(SellList);
	HANDLER_PACKET(BuyReply);
	HANDLER_PACKET(Logout);

	//Не обработаны
	/*
	0x15 BMSG("Follow", 0x09),
	0x2F RMSG("Combat Notification", 0x0a),
	0x97 RMSG("Move Player", 0x02),
	0xB2 BMSG("Chat Data", SIZE_VARIABLE),
	0xB3 RMSG("Chat Text ?", SIZE_VARIABLE),
	0xB5 BMSG("Open Chat Window", 0x40),
	0xB7 RMSG("Popup Help Data", SIZE_VARIABLE),
	0xD7 BMSG("+AoS command",SIZE_VARIABLE),
	0xD8 RMSG("+Custom house",SIZE_VARIABLE),
	0xDC RMSG("OPL Info Packet", 9),

0xC4, 0x81, 0x76, 0x28, 0x29, 0x2F, 0x30, 0x31, 0x7B, 0x8B,
0x98, 0x15, 0x38, 0x97, 0xC3, 0xCB, 0xB2, 0xB3, 0xB7, 0xBB,
0xC6, 0xC9, 0xCA, 0xD0, 0xCE, 0xCD, 0xD8, 0xDA, 0xDB, 0xDC,
0x16, 0xDE, 0xE5, 0xE6, 0xE7, 0xE9, 0xEA, 0xF2, 0xF6, 0xF7
	*/

public:
	CPacketManager();
	virtual ~CPacketManager();

	virtual int GetPacketSize(const UCHAR_LIST &packet, int &offsetToSize);

	CPacketInfo GetInfo(const uchar &buf) const { return m_Packets[buf]; }

	void SendMegaClilocRequests(UINT_LIST &list);

	void SendMegaClilocRequests();

	void AddMegaClilocRequest(const uint &serial, const bool &existsTest);

	void SavePluginReceivePacket(puchar buf, const int &size);

	void ProcessPluginPackets();

	void PluginReceiveHandler(puchar buf, const int &size);
};
//---------------------------------------------------------------------------
extern CPacketManager g_PacketManager;
//---------------------------------------------------------------------------
#endif