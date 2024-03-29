#pragma once
#include <wx/wx.h>
#include <wx/statline.h>
#include <iostream>
#include "chart/Chartcontrol.h"
#include "../presenter/Presenter.h"


class MainFrame : public wxFrame {
public:
	MainFrame(const wxString& title);
private:
	wxArrayString findFuns;
    wxArrayString types;
	wxPanel* panel;
	wxStaticText* findStatText, * matStatText, * mostPopStatText, *txtSlider, *txtEnterExp, *txtSliderMat, *txtValToFind;
	wxSlider* slider, *sliderMat;
	wxButton* btnCreateArray, *btnPrintArray, *btnFind, *btnFindExp, *btnCreateMatrix, *btnPrintMatrix, *btnProcessMat, *btnCharts, *btnTests, *btnHideCharts, *btnClearTxtPrint;
	wxChoice* choiceFindFun, *valueTypeChoice;
	wxStaticLine* staticLine1, * staticLine2, * staticLine3, *staticLine4;
	wxTextCtrl* txtCtrlExp, * txtPrint, *txtCtrlValToFind;
	ChartControl* chart1, * chart2, * chart3;

	Presenter presenter;

	void OnCreateArrayBtnClicked(wxCommandEvent& evt);
	void OnPrintArrayBtnClicked(wxCommandEvent& evt);
	void OnFindBtnClicked(wxCommandEvent& evt);
	void OnGraphBtnClicked(wxCommandEvent& evt);
	void OnGraphHideBtnClicked(wxCommandEvent& evt);
	void OnClearTextPrintBtnClicked(wxCommandEvent& evt);
	void OnFindMostPopularBtnClicked(wxCommandEvent& evt);
	void OnCreateMatrixBtnClicked(wxCommandEvent& evt);
	void OnPrintMatrixBtnClicked(wxCommandEvent& evt);
	void OnProcessMatrixBtnClicked(wxCommandEvent& evt);
	void OnTestsBtnClicked(wxCommandEvent& evt);
};
