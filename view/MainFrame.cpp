#include "MainFrame.h"
#include "../presenter/Presenter.h"

#include <wx/wx.h>



MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title) {
	panel = new wxPanel(this);
	panel->SetBackgroundColour(*wxLIGHT_GREY);

	//First Row (Check Find functions)
	findStatText = new wxStaticText(panel, wxID_ANY, "Check Find functions:", wxPoint(30, 20), wxDefaultSize);
	wxFont font = findStatText->GetFont();
	font.SetPointSize(12);
	font.SetWeight(wxFONTWEIGHT_BOLD);
	findStatText->SetFont(font);

	txtSlider = new wxStaticText(panel, wxID_ANY, "Number of elements: ", wxPoint(30, 45), wxDefaultSize);
	slider = new wxSlider(panel, wxID_ANY, 10, 10, 10000, wxPoint(30, 65), wxSize(200, -1), wxSL_LABELS);

	btnCreateArray = new wxButton(panel, wxID_ANY, "Create Array", wxPoint(30, 110), wxSize(120, -1));
	btnPrintArray = new wxButton(panel, wxID_ANY, "Print Array", wxPoint(30, 140), wxSize(120, -1));

	findFuns.Add("Bin Search");
	findFuns.Add("Hash Table");
	findFuns.Add("Bin Tree");
	choiceFindFun = new wxChoice(panel, wxID_ANY, wxPoint(30, 180), wxDefaultSize, findFuns);

	btnFind = new wxButton(panel, wxID_ANY, "Find", wxPoint(140, 180), wxSize(60, -1));
	btnFind->SetBackgroundColour(wxColor(70, 205, 70));

	txtValToFind = new wxStaticText(panel, wxID_ANY, "Enter Value \nto find:", wxPoint(160, 107), wxDefaultSize);
	txtCtrlValToFind = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(160, 140), wxSize(80, -1));

	staticLine1 = new wxStaticLine(panel, wxID_ANY, wxPoint(250, 10), wxSize(5, 580));
	staticLine2 = new wxStaticLine(panel, wxID_ANY, wxPoint(10, 215), wxSize(235, 5));

	//Second Row (Find Most Popular Subexpression)
	mostPopStatText = new wxStaticText(panel, wxID_ANY, "Find Most Popular \nSubexpression:", wxPoint(30, 225), wxDefaultSize);
	mostPopStatText->SetFont(font);

	txtEnterExp = new wxStaticText(panel, wxID_ANY, "Enter expression", wxPoint(30, 275), wxDefaultSize);

	txtCtrlExp = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(30, 295), wxSize(200, -1));

	btnFindExp = new wxButton(panel, wxID_ANY, "Find", wxPoint(173, 260), wxSize(60, -1));
	btnFindExp->SetBackgroundColour(wxColor(70, 205, 70));

	staticLine3 = new wxStaticLine(panel, wxID_ANY, wxPoint(10, 330), wxSize(235, 5));

	//Third Row (Matrix Processing)
	matStatText = new wxStaticText(panel, wxID_ANY, "Matrix Processing:", wxPoint(30, 340), wxDefaultSize);
	matStatText->SetFont(font);

	txtSliderMat = new wxStaticText(panel, wxID_ANY, "Number of rows and colums: ", wxPoint(30, 365), wxDefaultSize);
	sliderMat = new wxSlider(panel, wxID_ANY, 2, 1, 10, wxPoint(30, 385), wxSize(200, -1), wxSL_LABELS);

	btnCreateMatrix = new wxButton(panel, wxID_ANY, "Create Matrix", wxPoint(30, 430), wxSize(120, -1));
	btnPrintMatrix = new wxButton(panel, wxID_ANY, "Print Matrix", wxPoint(30, 460), wxSize(120, -1));

	btnProcessMat = new wxButton(panel, wxID_ANY, "Process", wxPoint(170, 440), wxSize(70, -1));
	btnProcessMat->SetBackgroundColour(wxColor(70, 205, 70));

	staticLine4 = new wxStaticLine(panel, wxID_ANY, wxPoint(10, 490), wxSize(235, 5));

	//Fourf Rov
	btnCharts = new wxButton(panel, wxID_ANY, "Generate Charts", wxPoint(30, 510), wxSize(120, -1));
	btnHideCharts = new wxButton(panel, wxID_ANY, "Hide Charts", wxPoint(30, 540), wxSize(120, -1));
	btnTests = new wxButton(panel, wxID_ANY, "Print Tests", wxPoint(30, 570), wxSize(120, -1));

	//Print Panel and Charts
	txtPrint = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(270, 20), wxSize(520, 545), wxTE_MULTILINE);

	btnClearTxtPrint = new wxButton(panel, wxID_ANY, "Clear", wxPoint(710, 570), wxSize(80, -1));

	chart1 = new ChartControl(panel, 121, wxPoint(30, 10), wxSize(290, 290));
	chart1->SetBackgroundColour(wxColor(60, 60, 60));
	chart1->values = { 0.98, 0.64, -0.17, 0.33 };
	chart1->Hide();

	chart2 = new ChartControl(panel, wxID_ANY, wxPoint(450, 10), wxSize(290, 290));
	chart2->SetBackgroundColour(wxColor(60, 60, 60));
	chart2->values = { -0.17, 0.34, 0.33, 0.98 };
	chart2->Hide();

	chart3 = new ChartControl(panel, 212, wxPoint(240, 310), wxSize(290, 290));
	chart3->SetBackgroundColour(wxColor(60, 60, 60));
	chart3->values = { 0.34, 0.33, -0.17, 0.98 };
	chart3->Hide();

	//Bindings
	btnCharts->Bind(wxEVT_BUTTON, &MainFrame::OnGraphBtnClicked, this);
	btnHideCharts->Bind(wxEVT_BUTTON, &MainFrame::OnGraphHideBtnClicked, this);
	btnClearTxtPrint->Bind(wxEVT_BUTTON, &MainFrame::OnClearTextPrintBtnClicked, this);
	btnCreateArray->Bind(wxEVT_BUTTON, &MainFrame::OnCreateArrayBtnClicked, this);
	btnPrintArray->Bind(wxEVT_BUTTON, &MainFrame::OnPrintArrayBtnClicked, this);
	btnFind->Bind(wxEVT_BUTTON, &MainFrame::OnFindBtnClicked, this);
	btnFindExp->Bind(wxEVT_BUTTON, &MainFrame::OnFindMostPopularBtnClicked, this);
	btnCreateMatrix->Bind(wxEVT_BUTTON, &MainFrame::OnCreateMatrixBtnClicked, this);
	btnPrintMatrix->Bind(wxEVT_BUTTON, &MainFrame::OnPrintMatrixBtnClicked, this);
	btnProcessMat->Bind(wxEVT_BUTTON, &MainFrame::OnProcessMatrixBtnClicked, this);
	btnTests->Bind(wxEVT_BUTTON, &MainFrame::OnTestsBtnClicked, this);
}

void MainFrame::OnCreateArrayBtnClicked(wxCommandEvent& evt) {
	presenter.createArr(slider->GetValue());

	txtPrint->WriteText("Array was created!\n\n");
}

void MainFrame::OnPrintArrayBtnClicked(wxCommandEvent& evt) {
	string arr = presenter.getArr();

	txtPrint->WriteText("Array: " + arr + "\n\n");
}

void MainFrame::OnFindBtnClicked(wxCommandEvent& evt) {
	string findType = findFuns[choiceFindFun->GetSelection()].ToStdString();
	string valueToFind = txtCtrlValToFind->GetValue().ToStdString();

	pair<string, bool> resOfFind = presenter.find(findType, valueToFind);

	bool res = resOfFind.second;

	if(res)
		txtPrint->WriteText("Value: " + valueToFind + " Exists in Array" + "\n");
	else
		txtPrint->WriteText("Value: " + valueToFind + " Doesn't exist in Array" + "\n");

	txtPrint->WriteText("Finding time: " + resOfFind.first + "\n");
}

void MainFrame::OnClearTextPrintBtnClicked(wxCommandEvent& evt) {
	txtPrint->Clear();
}

void MainFrame::OnFindMostPopularBtnClicked(wxCommandEvent& evt) {
	string res = presenter.findMostPopularExp(txtCtrlExp->GetValue().ToStdString());

	txtPrint->WriteText("Most Popular Subexpression is: " + res + "\n\n");
}

void MainFrame::OnCreateMatrixBtnClicked(wxCommandEvent& evt) {
	presenter.createMat(sliderMat->GetValue());

	txtPrint->WriteText("Matrix was created!\n\n");
}

void MainFrame::OnPrintMatrixBtnClicked(wxCommandEvent& evt) {
	string matrix = presenter.getMat();

	txtPrint->WriteText("Matrix: \n" + matrix + "\n\n");
}

void MainFrame::OnProcessMatrixBtnClicked(wxCommandEvent& evt) {
	string res = presenter.processMat();

	txtPrint->WriteText("Result: \n" + res + "\n\n");
}

void MainFrame::OnTestsBtnClicked(wxCommandEvent& evt) {
	txtPrint->WriteText(presenter.getTestRes());
}

void MainFrame::OnGraphBtnClicked(wxCommandEvent& evt) {
	//tuple<vector<double>, vector<double>, vector<double>> vecTuple = presenter.getPointsForChart();
	//
	//chart1 = new ChartControl(panel, 121, wxPoint(30, 10), wxSize(290, 290));
	//chart1->SetBackgroundColour(wxColor(60, 60, 60));
	//chart1->title = "Bin Search";
	//chart1->values = std::get<0>(vecTuple);
	//
	//chart2 = new ChartControl(panel, wxID_ANY, wxPoint(450, 10), wxSize(290, 290));
	//chart2->title = "Hash Table";
	//chart2->SetBackgroundColour(wxColor(60, 60, 60));
	//chart2->values = std::get<1>(vecTuple);
	//
	//chart3 = new ChartControl(panel, 212, wxPoint(240, 310), wxSize(290, 290));
	//chart3->title = "Bin Tree";
	//chart3->SetBackgroundColour(wxColor(60, 60, 60));
	//chart3->values = std::get<2>(vecTuple);
	
	chart1->Show();
	chart2->Show();
	chart3->Show();
}

void MainFrame::OnGraphHideBtnClicked(wxCommandEvent& evt) {
	chart1->Hide();
	chart2->Hide();
	chart3->Hide();
}

