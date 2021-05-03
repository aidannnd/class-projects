
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "Project1.h"
#include "ChildView.h"
#include "Game.h"
#include "DoubleBufferDC.h"
#include "Level.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "TowerBomb.h"
#include "TowerCustom.h"
#include "GoButton.h"
#include "TowerBombCounter.h"

using namespace Gdiplus;
using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

/// Maximum amount of time to allow for elapsed
const double MaxElapsed = 0.050;

/// Margin of towers from side and bottom in pixels
const int Margin = 5;

// CChildView

CChildView::CChildView()
{
	// Load the tower-rings  image
	mTowerRings = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/tower-rings.png"));
	if (mTowerRings->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/tower-rings.png");
	}

	// Load the tower-bomb  image
	mTowerBomb = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/tower-bomb.png"));
	if (mTowerBomb->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/tower-bomb.png");
	}

	// Load the tower8  image
	mTowerEight = unique_ptr<Bitmap>(Bitmap::FromFile(L"images/tower8.png"));
	if (mTowerEight->GetLastStatus() != Ok)
	{
		AfxMessageBox(L"Failed to open images/tower8.png");
	}
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_LEVEL_LEVEL1, &CChildView::OnLevelLevel1)
	ON_COMMAND(ID_LEVEL_LEVEL2, &CChildView::OnLevelLevel2)
	ON_COMMAND(ID_LEVEL_LEVEL3, &CChildView::OnLevelLevel3)
	ON_COMMAND(ID_LEVEL_LEVEL0, &CChildView::OnLevelLevel0)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	
	CPaintDC paintDC(this); // device context for painting
	CDoubleBufferDC dc(&paintDC);
	Graphics graphics(dc.m_hDC);

	// TODO: Add your message handler code here
	CRect rect;
	GetClientRect(&rect);

	mGame.OnDraw(&graphics, rect.Width(), rect.Height());


	// Do not call CWnd::OnPaint() for painting messages

	if (mFirstDraw)
	{
		mFirstDraw = false;
		SetTimer(1, FrameDuration, nullptr);

		/*
		* Initialize the elapsed time system
		*/
		LARGE_INTEGER time, freq;
		QueryPerformanceCounter(&time);
		QueryPerformanceFrequency(&freq);

		mLastTime = time.QuadPart;
		mTimeFreq = double(freq.QuadPart);
	}

	/**
	* Compute the elapsed time since the last draw
	*/
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	long long diff = time.QuadPart - mLastTime;
	double elapsed = double(diff) / mTimeFreq;
	mGame.SetTimer(elapsed);
	mLastTime = time.QuadPart;
	if (mGame.GetTimer() <= 2)
	{
		FontFamily fontFamily(L"Arial");
		Gdiplus::Font font(&fontFamily, 80, FontStyleBold);
		PointF origin(150, 400);
		SolidBrush red(Color(255, 0, 0));

		auto LevelString = L"Level " + to_wstring(mGame.GetLevel()->GetCurLevel()) + L" Begin";
		graphics.DrawString(LevelString.c_str(),  // String to draw
			-1,         // String length, -1 so it figures it out on its own
			&font,      // The font to use
			origin,		// Where to draw (top left corner)
			&red);    // The brush to draw the text with

	}
	if (!mGame.GetButtonStatus())
	{
		//
		// Prevent tunnelling
		//
		while (elapsed > MaxElapsed)
		{
			mGame.Update(MaxElapsed);

			elapsed -= MaxElapsed;
		}

		// Consume any remaining time
		if (elapsed > 0)
		{
			mGame.Update(elapsed);
		}
	}
}

/**
* Erase the background
*
* This is disabled to eliminate flicker
* \param pDC Device context
* \return FALSE
*/
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return false;
}


/**
 * Handle 
 events
 * \param nIDEvent The timer event ID
 */
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	Invalidate();

	CWnd::OnTimer(nIDEvent);
}



/**
 * Handle left button down events
 * \param nFlags Flag
 * \param point Point of occurence
 * Directs to Game class
 */
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (mGame.GetButtonStatus())
	{
		if (mGame.HitTestForButton(point.x, point.y))
		{
			mGame.RemoveButton();
		}
		mGrabbedItem = mGame.OnLButtonDown(point.x, point.y);
		if (mGrabbedItem != nullptr)
		{
			mGame.MoveToFront(mGrabbedItem);
			bool checkRing = mGrabbedItem->HitTest(1125, 100);
			bool checkEight = mGrabbedItem->HitTest(1125, 200);
			bool checkBomb = mGrabbedItem->HitTest(1125, 300);
			bool checkCustom = mGrabbedItem->HitTest(1125, 400);
			// checking if one of the towers is selected or not
			if (!checkRing && !checkEight && !checkBomb && !checkCustom)
			{
			}
			else if (mGrabbedItem->GetType() == "Ring")
			{
				auto TowerRing = std::make_shared<CTowerRing>(&mGame);
				TowerRing->SetLocation(1125, 100);
				mGame.Add(TowerRing);
				mGrabbedItem = TowerRing;
			}
			else if (mGrabbedItem->GetType() == "Eight")
			{
				auto TowerEight = std::make_shared<CTowerEight>(&mGame);
				TowerEight->SetLocation(1125, 200);
				mGame.Add(TowerEight);
				mGrabbedItem = TowerEight;
			}
			else if (mGrabbedItem->GetType() == "Bomb")
			{
				CTowerBombCounter visitor;
				mGame.Accept(&visitor);
				auto TowerBomb = std::make_shared<CTowerBomb>(&mGame, visitor.GetTowerBombCount());
				TowerBomb->SetLocation(1125, 300);
				mGame.Add(TowerBomb);
				mGrabbedItem = TowerBomb;
			}
			else if (mGrabbedItem->GetType() == "Custom")
			{
				auto TowerCustom = std::make_shared<CTowerCustom>(&mGame);
				TowerCustom->SetLocation(1125, 400);
				mGame.Add(TowerCustom);
				mGrabbedItem = TowerCustom;
			}
		}
		CWnd::OnLButtonDown(nFlags, point);
	}
	
}

/**
 * Handle left button up events
 * \param nFlags Flag
 * \param point Point of occurence
 * Directs to Game class
 */
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonUp(nFlags, point);

	OnMouseMove(nFlags, point);

	std::shared_ptr<CItem> item = mGame.HitTestForOpenTile(point.x, point.y);
	if (item != nullptr && mGrabbedItem != nullptr)
	{
		bool result = item->MoveTower(mGrabbedItem);
		if (result == true)
		{
			mGame.DeleteItem(mGrabbedItem);
		}
	}
	else if (mGrabbedItem != nullptr)
	{
		mGame.DeleteItem(mGrabbedItem);
	}
	this->OnPaint();
	Invalidate();
}

/** Called when the mouse is moved
* \param nFlags Flags associated with the mouse movement
* \param point Where the button was pressed
*/
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	auto tup = mGame.OnLButtonUp(point.x, point.y);

	// See if an item is currently being moved by the mouse
	if (mGrabbedItem != nullptr)
	{
		// If an item is being moved, we only continue to 
		// move it while the left button is down.
		if (nFlags & MK_LBUTTON)
		{
			mGrabbedItem->SetLocation(get<0>(tup), get<1>(tup));
		}

		// Force the screen to redraw
		Invalidate();
	}
}

/**
 * Handle level 0 selection event
 */
void CChildView::OnLevelLevel0()
{
	std::shared_ptr<CLevel> curLevel = mGame.GetLevel();
	curLevel->Load(&mGame, 0);
	mGame.ShowButton();
	mGame.ResetBalloons();
	mGame.ResetScore();
}

/**
 * Handle level 1 selection event
 */
void CChildView::OnLevelLevel1()
{
	std::shared_ptr<CLevel> curLevel = mGame.GetLevel();
	curLevel->Load(&mGame, 1);
	mGame.ShowButton();
	mGame.ResetBalloons();
	mGame.ResetScore();
	mGame.SetTimerToZero();
}

/**
 * Handle level 2 selection event
 */
void CChildView::OnLevelLevel2()
{
	std::shared_ptr<CLevel> curLevel = mGame.GetLevel();
	curLevel->Load(&mGame, 2);
	mGame.ShowButton();
	mGame.ResetBalloons();
	mGame.ResetScore();
	mGame.SetTimerToZero();
}

/**
 * Handle level 3 selection event
 */
void CChildView::OnLevelLevel3()
{
	std::shared_ptr<CLevel> curLevel = mGame.GetLevel();
	curLevel->Load(&mGame, 3);
	mGame.ShowButton();
	mGame.ResetBalloons();
	mGame.ResetScore();
	mGame.SetTimerToZero();
}
