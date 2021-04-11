#include "Main.h"

#include <fstream>
#include <cstring>

constexpr static int id1 = 1234;
constexpr static int id2 = 1235;
constexpr static int id3 = 1236;

wxBEGIN_EVENT_TABLE(Main, wxFrame) EVT_TEXT(id1, Main::OnTextTyped) EVT_BUTTON(id2, Main::OnPrevButtonPressed)
    EVT_BUTTON(id3, Main::OnNextButtonPressed) wxEND_EVENT_TABLE();

Main::Main() : wxFrame(nullptr, wxID_ANY, "Search in dictionary", wxPoint(30, 30), wxSize(540, 635)) {
    inputField = new wxTextCtrl(this, id1, input, wxPoint(10, 10), wxSize(500, 25));
    prevButton = new wxButton(this, id2, "<", wxPoint(10, 45), wxSize(25, 25));
    nextButton = new wxButton(this, id3, ">", wxPoint(45, 45), wxSize(25, 25));
    resultsList = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 80), wxSize(500, 500), wxTE_MULTILINE | wxTE_RICH | wxTE_READONLY);

    std::ifstream fin = std::ifstream("data/words.txt");
    std::string s;
    while ((fin >> s)) {
        s.push_back('\n');
        dict.push_back(std::move(s));
    }
    fin.close();

    updateList();
}

void Main::OnTextTyped(wxCommandEvent& evt) {
    input = inputField->GetValue().ToStdString();
    updateList();

    evt.Skip();
}

void Main::OnPrevButtonPressed(wxCommandEvent& evt) {
    previousPage();
    evt.Skip();
}
void Main::OnNextButtonPressed(wxCommandEvent& evt) {
    nextPage();
    evt.Skip();
}

void Main::updateList() {
    lastIndex = 0;

    prevButtonEnabled = false;
    prevButton->Disable();

    nextPage();
}

void Main::nextPage() {
    resultsList->Clear();
    nextButtonEnabled = false;

    size_t wordsFound = 0;

    if (lastIndex != 0) {
        prevButtonEnabled = true;
        prevButton->Enable();
    }

    for (size_t i = lastIndex; i < dict.size(); ++i) {
        const char* str = dict[i].c_str();

        if (input.empty() || std::strstr(str, input.c_str()) != 0) {
            if (wordsFound < wordsPerPage) resultsList->AppendText(wxString(str));

            if (wordsFound == wordsPerPage) {
                nextButtonEnabled = true;
                break;
            }

            if (wordsFound == 0) firstIndex = i - 1;
            lastIndex = i + 1;

            ++wordsFound;
        }
    }

    nextButton->Enable();
    if (!nextButtonEnabled) nextButton->Disable();
}

void Main::previousPage() {
    nextButtonEnabled = true;
    nextButton->Enable();

    resultsList->Clear();
    prevButtonEnabled = false;

    size_t wordsFound = 0;

    std::vector<size_t> vec;

    for (size_t i = firstIndex; i != -1; --i) {
        const char* str = dict[i].c_str();

        if (input.empty() || std::strstr(str, input.c_str()) != 0) {
            if (wordsFound < wordsPerPage) vec.push_back(i);

            if (wordsFound == wordsPerPage) {
                prevButtonEnabled = true;
                break;
            }

            if (wordsFound == 0) lastIndex = i + 1;
            firstIndex = i - 1;

            ++wordsFound;
        }
    }

    for (size_t i = vec.size(); i-- > 0;) resultsList->AppendText(wxString(dict[vec[i]]));

    prevButton->Enable();
    if (!prevButtonEnabled) prevButton->Disable();
}
