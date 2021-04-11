#pragma once

#include <string>
#include <vector>

#include <wx/wx.h>

class Main : public wxFrame {
 public:
    Main();

 private:
    void OnTextTyped(wxCommandEvent& evt);
    void OnPrevButtonPressed(wxCommandEvent& evt);
    void OnNextButtonPressed(wxCommandEvent& evt);

    void updateList();
    void nextPage();
    void previousPage();

 private:
    wxTextCtrl* inputField = nullptr;
    wxTextCtrl* resultsList = nullptr;
    wxButton* prevButton = nullptr;
    wxButton* nextButton = nullptr;

    std::vector<std::string> dict;
    std::string input = "";

    static constexpr int wordsPerPage = 32;
    size_t firstIndex = 0;
    size_t lastIndex = 0;
    bool nextButtonEnabled = false;
    bool prevButtonEnabled = false;

    wxDECLARE_EVENT_TABLE();
};
