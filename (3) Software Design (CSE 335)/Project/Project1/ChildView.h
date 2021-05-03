// ChildView.h : interface of the CChildView class
//


#pragma once
#include "Game.h"
#include "PanelScore.h"
#include "DoubleBufferDC.h"
#include "Tower.h"
#include "TowerRing.h"
#include "TowerEight.h"
#include <string>
#include <winnt.h>

// CChildView window

/**
 * The child window our program draws in.
 */
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:
	/// true until the first time we draw
	bool mFirstDraw = true;
	/// Last time we read the timer
	long long mLastTime = 0; 
	/// Rate the timer updates
	double mTimeFreq = 0; 
// Operations
public:

// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
	/// Game class
	CGame mGame;
	/// score class
	CPanelScore mScore;
	/// helps regulate psuh backs into mTowerVector
	bool mInitialzed = false;
	/// image for tower ring
	std::unique_ptr<Gdiplus::Bitmap> mTowerRings;
	/// image for tower bomb
	std::unique_ptr<Gdiplus::Bitmap> mTowerBomb;
	/// tower bomb image
	std::unique_ptr<Gdiplus::Bitmap> mTowerEight;
	/// Item the mouse is currently holding
	std::shared_ptr<CItem> mGrabbedItem;

	/// denies the various items from updating
	bool GoActivated = true;

public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLevelLevel1();
	afx_msg void OnLevelLevel2();
	afx_msg void OnLevelLevel3();
	afx_msg void OnLevelLevel0();
};

