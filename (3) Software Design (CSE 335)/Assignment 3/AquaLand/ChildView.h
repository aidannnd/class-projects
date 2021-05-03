/**
 * \file ChildView.h
 *
 * \author Aidan Delfuoco
 *
 * Class that implements the child window our program draws in.
 *
 * The window is a child of the main frame, which holds this
 * window, the menu bar, and the status bar.
 */

#pragma once

#include "Aquarium.h"

 /**
  * The child window our program draws in.
  */
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

private:
	CAquarium mAquarium; ///< An object that describes our aquarium

	/// Any item we are currently dragging
	std::shared_ptr<CItem> mGrabbedItem;

	// Attributes
public:
	/// True until the first time we draw
	bool mFirstDraw = true;

	// Operations
public:

// Overrides
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	long long mLastTime = 0;    ///< Last time we read the timer
	double mTimeFreq = 0;       ///< Rate the timer updates

// Implementation
public:
	virtual ~CChildView();

// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAddfishBetafish();
	afx_msg void OnAddfishMagikarpfish();
	afx_msg void OnAddfishGoldeenfish();
protected:
//	afx_msg LRESULT OnOnlbuttondown(WPARAM wParam, LPARAM lParam);
//	afx_msg LRESULT WM_LBUTTONDOWN(WPARAM wParam, LPARAM lParam);
//	afx_msg LRESULT OnLButtonDown(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnAdddecorCastledecor();
	afx_msg void OnFileSaveas();
	afx_msg void OnFileOpen32777();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

