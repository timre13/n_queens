#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>
#include <memory>
#include "InputWindow.h"

int main(int argc, char** argv)
{
    auto app = Gtk::Application::create(argc, argv, "org.timre13.nqueen");

    auto inputWindow = new InputWindow;

    return app->run(*inputWindow);
}
