#include <gtkmm/application.h>
#include <gtkmm/applicationwindow.h>
#include <memory>
#include "MainWindow.h"

int main(int argc, char** argv)
{
    auto app = Gtk::Application::create(argc, argv, "org.timre13.nqueen");
    auto window = std::make_unique<MainWindow>();

    return app->run(*window);
}
