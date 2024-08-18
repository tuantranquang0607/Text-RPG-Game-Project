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
	m_sText = text;
	m_sTextChunks.clear();

	std::wstring text_holder = L"";

	for (int i = 0; i < text.size(); i++)
	{
		text_holder += text[i];

		bool newLine = text[i] == '\n';

		size_t text_size = text_holder.size();

		if (text_size >= m_TextWrap || newLine)
		{
			if (!newLine)
			{
				while (text[i] != ' ' && text[i] != '.' && text[i] != '!' && text[i] != '?' && text_size > 0)
				{
					i--;
					text_holder.pop_back();
				}
			}
			else
			{
				// Get rid of the new line character
				text_holder.pop_back();
			}

			if (text_size > 0)
			{
				m_sTextChunks.push_back(text_holder);
				text_holder.clear();
			}
		}
	}

	// Push in the rest of the text
	if (!text_holder.empty())
	{
		m_sTextChunks.push_back(text_holder);
	}

	if (!SetBorderProperties())
	{
		TRPG_ERROR("Failed to set the border properties!");
		return false;
	}

	return true;
}

void Typewriter::UpdateText()
{
}

void Typewriter::Draw(bool showborder)
{
}
