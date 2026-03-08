#pragma once

#include "UIScene.h"
#include "..\..\..\Minecraft.World\EMiniGameId.h"

class UIScene_MiniGameSelectMenu : public UIScene
{
private:
	enum EControls
	{
		eControl_Battle,
		eControl_Tumble,
		eControl_Glide,
		eControl_CreateJoinToggle,
		eControl_Count,
	};

	enum EMode
	{
		eMode_Create,
		eMode_Join,
	};

	UIControl_Button m_buttons[eControl_Count];
	UIControl_Button m_hiddenButtons[2];
	UIControl m_controlTimer;

	UI_BEGIN_MAP_ELEMENTS_AND_NAMES(UIScene)
		UI_MAP_ELEMENT(m_buttons[(int)eControl_Battle], "Button1")
		UI_MAP_ELEMENT(m_buttons[(int)eControl_Tumble], "Button2")
		UI_MAP_ELEMENT(m_buttons[(int)eControl_Glide], "Button3")
		UI_MAP_ELEMENT(m_buttons[(int)eControl_CreateJoinToggle], "Button4")
		UI_MAP_ELEMENT(m_hiddenButtons[0], "Button5")
		UI_MAP_ELEMENT(m_hiddenButtons[1], "Button6")
		UI_MAP_ELEMENT(m_controlTimer, "Timer")
	UI_END_MAP_ELEMENTS_AND_NAMES()

	EMode m_mode;
	int m_selectedMiniGame;
	bool m_bIgnorePress;

public:
	UIScene_MiniGameSelectMenu(int iPad, void *initData, UILayer *parentLayer);
	virtual ~UIScene_MiniGameSelectMenu();

	virtual EUIScene getSceneType() { return eUIScene_MiniGameSelectMenu; }
	virtual wstring getMoviePath();
	virtual void updateTooltips();
	virtual void handleReload();

	virtual void handleInput(int iPad, int key, bool repeat, bool pressed, bool released, bool &handled);

protected:
	void handlePress(F64 controlId, F64 childId);
	void handleGainFocus(bool navBack);

private:
	void UpdateModeLabel();
	void LaunchMiniGame(EMiniGameId miniGameId);
	void JoinMiniGame();
};
