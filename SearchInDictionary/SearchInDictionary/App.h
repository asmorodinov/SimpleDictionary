#pragma once

#include <wx/wx.h>

#include "Main.h"

class App : public wxApp {
 public:
    App() = default;
    ~App() = default;

    bool OnInit() override;

 private:
    Main* frame1 = nullptr;
};
