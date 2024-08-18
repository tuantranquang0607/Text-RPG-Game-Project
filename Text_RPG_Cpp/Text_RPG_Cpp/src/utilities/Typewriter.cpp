#include "Typewriter.h"
#include "../Logger.h"
#include "../Console.h"

#include <algorithm>

bool Typewriter::SetBorderProperties()
{
    return false;
}

void Typewriter::DrawBorder()
{
}

void Typewriter::ClearArea()
{
}

Typewriter::Typewriter(Console& console) : Typewriter(console, 1, 1, L"TODO: Set type writer text!", 50, 250)
{

}

Typewriter::Typewriter(Console& console, int start_x, int start_y, const std::wstring& text, int text_wrap, int speed, WORD textColor, WORD borderColor) :
    m_Console( console ),
    m_sText{ text },
    m_sCurrentText{ L"" },
    m_X{ start_x },
    m_Y{ start_y },
    m_BorderX{ 0 },
    m_BorderY{ 0 },
    m_BorderWidth{ 0 },
    m_BorderHeight{ 0 },
    m_TextSpeed{ speed },
    m_TextWrap{ text_wrap },
    m_Index{ 0 },
    m_CharIndex{ 0 },
    m_TextIndex{ 0 },
    m_TextColor{ textColor },
    m_BorderColor{ borderColor },
    m_Timer{},
    m_bFinished{ false }
{
    if (!SetText( text ))
	{
        TRPG_ERROR("Failed to initialize text for the typewriter!");
        return;
	}

    ClearArea();

    m_Timer.Start();
}

Typewriter::~Typewriter()
{
}

bool Typewriter::SetText(const std::wstring& text)
{
    return false;
}

void Typewriter::UpdateText()
{
}

void Typewriter::Draw(bool showborder)
{
}
