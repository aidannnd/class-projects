/**
 * \file ChildView.cpp
 *
 * \author Aidan Delfuoco
 */

#include "pch.h"
#include "framework.h"
#include "AquaLand.h"
#include "ChildView.h"
#include "FishBeta.h"
#include "FishMagikarp.h"
#include "FishGoldeen.h"
#include "FishAngler.h"
#include "DoubleBufferDC.h"
#include "Aquarium.h"

using namespace Gdiplus;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/// Initial fish X location
const int InitialX = 200;

/// Initial fish Y location
const int InitialY = 200;

 /**
  * Constructor
  */
CChildView::CChildView()
{
}

/**
 * Destructor
 */
CChildView::~CChildView()
{
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_ADDFISH_BETAFISH, &CChildView::OnAddfishBetafish)
//	ON_MESSAGE(OnLButtonDown, &CChildView::OnOnlbuttondown)
//ON_MESSAGE(OnLButtonDown, &CChildView::WM_LBUTTONDOWN)
//ON_MESSAGE(WM_LBUTTONDOWN, &CChildView::OnLButtonDown)
ON_WM_LBUTTONUP()
ON_WM_MOUSEMOVE()
ON_WM_LBUTTONDOWN()
ON_WM_ERASEBKGND()
ON_COMMAND(ID_ADDFISH_MAGIKARPFISH, &CChildView::OnAddfishMagikarpfish)
ON_COMMAND(ID_ADDFISH_GOLDEENFISH, &CChildView::OnAddfishGoldeenfish)
ON_COMMAND(ID_ADDFISH_ANGLERFISH, &CChildView::OnAddfishAnglerfish)
END_MESSAGE_MAP()

/**
 * This function is called before the window is created.
 * \param cs A structure with the window creation parameters
 * \returns TRUE
 */
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

/**
 * This function is called to draw in the window.
 *
 * This function is called in response to a drawing message
 * whenever we need to redraw the window on the screen.
 * It is responsible for painting the window.
 */
void CChildView::OnPaint()
{
	CPaintDC paintDC(this);     // device context for painting
	CDoubleBufferDC dc(&paintDC); // device context for painting
	Graphics graphics(dc.m_hDC);

	mAquarium.OnDraw(&graphics);
}

/**
 * Add Fish/Beta menu option handler
 */
void CChildView::OnAddfishBetafish()
{
	auto fish = make_shared<CFishBeta>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	Invalidate();
}

/**
 * Add Fish/Magikarp menu option handler
 */
void CChildView::OnAddfishMagikarpfish()
{
	auto fish = make_shared<CFishMagikarp>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	Invalidate();
}

/**
 * Add Fish/Goldeen menu option handler
 */
void CChildView::OnAddfishGoldeenfish()
{
	auto fish = make_shared<CFishGoldeen>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	Invalidate();
}

/**
 * Add Fish/Angler menu option handler
 */
void CChildView::OnAddfishAnglerfish()
{
	auto fish = make_shared<CFishAngler>(&mAquarium);
	fish->SetLocation(InitialX, InitialY);
	mAquarium.Add(fish);
	Invalidate();
}

/** 
 * Called when there is a left mouse button press
 * \param nFlags Flags associated with the mouse button press
 * \param point Where the button was pressed
*/
void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	mGrabbedItem = mAquarium.HitTest(point.x, point.y);
	if (mGrabbedItem != nullptr)
	{
		// We have selected an item
		// Move it to the end of the list of items
		// you'll need code here to do that...
		mAquarium.MoveToEnd(mGrabbedItem);
	}
}

/**
 * Called when the left mouse button is released
 * \param nFlags Flags associated with the mouse button release
 * \param point Where the button was pressed
 */
void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	OnMouseMove(nFlags, point);
}

/**
 * Called when the mouse is moved
 * \param nFlags Flags associated with the mouse movement
 * \param point Where the button was pressed
 */
void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	// See if an item is currently being moved by the mouse
	if (mGrabbedItem != nullptr)
	{
		// If an item is being moved, we only continue to 
		// move it while the left button is down.
		if (nFlags & MK_LBUTTON)
		{
			mGrabbedItem->SetLocation(point.x, point.y);
		}
		else
		{
			// When the left button is released, we release the
			// item.
			mGrabbedItem = nullptr;
		}

		// Force the screen to redraw
		Invalidate();
	}
}

/**
 * Erase the background
 *
 * This is disabled to eliminate flicker
 * \param pDC Device context
 * \returns FALSE
 */
BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
    return FALSE;
}