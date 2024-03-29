
#include "NumberWidget.h"

CNumberWidget::CNumberWidget()	:
	m_Number(0)
{
}

CNumberWidget::CNumberWidget(const CNumberWidget& widget)	:
	CUIImage(widget)
{
	m_Number = widget.m_Number;
}

CNumberWidget::~CNumberWidget()
{
}

bool CNumberWidget::Init()
{
	return true;
}

void CNumberWidget::Update(float DeltaTime)
{
	int Number = m_Number;

	std::stack<int> NumberStack;

	while (Number > 0)
	{
		NumberStack.push(Number % 10);
		Number /= 10;
	}

	m_vecNumber.clear();

	while (!NumberStack.empty())
	{
		m_vecNumber.push_back(NumberStack.top());
		NumberStack.pop();
	}
}

void CNumberWidget::PostUpdate(float DeltaTime)
{
}

void CNumberWidget::Collision(float DeltaTime)
{
}

// 시계 숫자는 아래의 Parameter가 hDC하나만 요구하는
// Render함수 이용
void CNumberWidget::Render(HDC hDC)
{
	if (m_vecNumber.empty())
	{
		// 비어 있으면 0을 출력
		m_FrameIndex = 0;
		CUIImage::Render(hDC);
	}

	else
	{
		// 비어있지 않다면 값이 있다는 것이다.
		size_t	Size = m_vecNumber.size();

		for (size_t i = 0; i < Size; ++i)
		{
			if (m_Texture->GetTextureType() == ETexture_Type::Frame)
				m_FrameIndex = m_vecNumber[i];
			else
				m_FrameIndex = 0;

			m_Offset.x = i * m_Size.x;

			CUIImage::Render(hDC);
		}
	}
}

// 데미지 폰트는 아래 Render 이용
void CNumberWidget::Render(const Vector2& Pos, HDC hDC)
{
	if (m_vecNumber.empty())
	{
		m_FrameIndex = 0;
		CUIImage::Render(Pos, hDC);
	}

	else
	{
		size_t Size = m_vecNumber.size();

		for (size_t i = 0; i < Size; ++i)
		{
			if (m_Texture->GetTextureType() == ETexture_Type::Frame)
			{
				m_FrameIndex = m_vecNumber[i];
			}

			else
			{
				m_FrameIndex = 0;
			}

			m_Offset.x = i * m_Size.x;
			CUIImage::Render(Pos, hDC);
		}
	}
}

CNumberWidget* CNumberWidget::Clone()
{
	return new CNumberWidget(*this);
}
