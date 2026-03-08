#include "stdafx.h"
#include "UI.h"
#include "UIScene_MiniGameSelectMenu.h"
#include "..\..\Minecraft.h"
#include "..\..\..\Minecraft.World\MiniGameDef.h"
#include "..\..\..\Minecraft.World\EMiniGameId.h"

UIScene_MiniGameSelectMenu::UIScene_MiniGameSelectMenu(int iPad, void *initData, UILayer *parentLayer) : UIScene(iPad, parentLayer)
{
	initialiseMovie();

	m_mode = eMode_Create;
	m_selectedMiniGame = -1;
	m_bIgnorePress = false;

	m_buttons[(int)eControl_Battle].init(L"Battle", eControl_Battle);
	m_buttons[(int)eControl_Tumble].init(L"Tumble", eControl_Tumble);
	m_buttons[(int)eControl_Glide].init(L"Glide", eControl_Glide);
	m_buttons[(int)eControl_CreateJoinToggle].init(L"Mode: Create", eControl_CreateJoinToggle);

	handleReload();
	doHorizontalResizeCheck();
}

UIScene_MiniGameSelectMenu::~UIScene_MiniGameSelectMenu()
{
}

wstring UIScene_MiniGameSelectMenu::getMoviePath()
{
	return L"MainMenu";
}

void UIScene_MiniGameSelectMenu::updateTooltips()
{
}

void UIScene_MiniGameSelectMenu::handleReload()
{
	removeControl(&m_hiddenButtons[0], false);
	removeControl(&m_hiddenButtons[1], false);
	m_controlTimer.setVisible(false);
}

void UIScene_MiniGameSelectMenu::handleInput(int iPad, int key, bool repeat, bool pressed, bool released, bool &handled)
{
	if(m_bIgnorePress) return;

	ui.AnimateKeyPress(m_iPad, key, repeat, pressed, released);

	switch(key)
	{
	case ACTION_MENU_CANCEL:
		if(pressed)
		{
			navigateBack();
			handled = true;
		}
		break;
	case ACTION_MENU_OK:
	case ACTION_MENU_UP:
	case ACTION_MENU_DOWN:
	case ACTION_MENU_LEFT:
	case ACTION_MENU_RIGHT:
		sendInputToMovie(key, repeat, pressed, released);
		handled = true;
		break;
	}
}

void UIScene_MiniGameSelectMenu::handlePress(F64 controlId, F64 childId)
{
	if(m_bIgnorePress) return;

	ui.PlayUISFX(eSFX_Press);

	switch((int)controlId)
	{
	case eControl_Battle:
		if(m_mode == eMode_Create)
			LaunchMiniGame(MINIGAME_BATTLE);
		else
			JoinMiniGame();
		break;
	case eControl_Tumble:
		if(m_mode == eMode_Create)
			LaunchMiniGame(MINIGAME_TUMBLE);
		else
			JoinMiniGame();
		break;
	case eControl_Glide:
		if(m_mode == eMode_Create)
			LaunchMiniGame(MINIGAME_GLIDE);
		else
			JoinMiniGame();
		break;
	case eControl_CreateJoinToggle:
		if(m_mode == eMode_Create)
			m_mode = eMode_Join;
		else
			m_mode = eMode_Create;
		UpdateModeLabel();
		break;
	}
}

void UIScene_MiniGameSelectMenu::handleGainFocus(bool navBack)
{
	UIScene::handleGainFocus(navBack);
	m_bIgnorePress = false;
}

void UIScene_MiniGameSelectMenu::UpdateModeLabel()
{
	if(m_mode == eMode_Create)
		m_buttons[(int)eControl_CreateJoinToggle].setLabel(L"Mode: Create");
	else
		m_buttons[(int)eControl_CreateJoinToggle].setLabel(L"Mode: Join");
}

void UIScene_MiniGameSelectMenu::LaunchMiniGame(EMiniGameId miniGameId)
{
	Minecraft *pMinecraft = Minecraft::GetInstance();
	if(!pMinecraft)
		return;

	m_bIgnorePress = true;

	pMinecraft->SetupMiniGameInstance(MiniGameDef::GetCustomGameModeById(miniGameId, true), 0);

	// navigate to load menu to configure options before starting the game
	ui.NavigateToScene(m_iPad, eUIScene_LoadMenu, NULL);
}

void UIScene_MiniGameSelectMenu::JoinMiniGame()
{
	m_bIgnorePress = true;

	// navigate to the join menu to find/join existing games
	ui.NavigateToScene(m_iPad, eUIScene_JoinMenu, NULL);
}
