#pragma once
#include "xrUICore/Windows/UIFrameWindow.h"
#include "xrCore/Containers/AssociativeVector.hpp"

class CUIStatic;
class CUIXml;
class CGameTask;
class CMapSpot;

class CUIMapLocationHint final : public CUIFrameWindow
{
    typedef CUIFrameWindow inherited;

    CUIWindow* m_owner{};
    CUIFrameWindow* m_border{};
    AssociativeVector<shared_str, CUIStatic*> m_info;
    void SetInfoMode(u8 mode);

public:
    CUIMapLocationHint() : CUIFrameWindow(CUIMapLocationHint::GetDebugType()) {}

    void Init(CUIXml& uiXml, LPCSTR path);

    void SetInfoStr(LPCSTR text);
    void SetInfoMSpot(CMapSpot* spot);
    void SetInfoTask(CGameTask* task);

    void SetOwner(CUIWindow* w) { m_owner = w; }
    CUIWindow* GetOwner() const { return m_owner; }

    pcstr GetDebugType() override { return "CUIMapLocationHint"; }

private:
    float m_posx_icon{};
    float m_posx_caption{};
};
