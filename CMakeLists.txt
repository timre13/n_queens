CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_STANDARD_REQUIRED TRUE)

SET(CMAKE_CXX_FLAGS "-pthread -Wall -Wextra -Wpedantic")

PROJECT(n_queens VERSION 1.0)

# GTK header search paths
INCLUDE_DIRECTORIES(
    /usr/include/gtkmm-3.0
    /usr/lib/x86_64-linux-gnu/gtkmm-3.0/include
    /usr/include/atkmm-1.6
    /usr/include/gtk-3.0/unix-print
    /usr/include/gdkmm-3.0
    /usr/lib/x86_64-linux-gnu/gdkmm-3.0/include
    /usr/include/giomm-2.4
    /usr/lib/x86_64-linux-gnu/giomm-2.4/include
    /usr/include/pangomm-1.4
    /usr/lib/x86_64-linux-gnu/pangomm-1.4/include
    /usr/include/glibmm-2.4
    /usr/lib/x86_64-linux-gnu/glibmm-2.4/include
    /usr/include/gtk-3.0
    /usr/include/at-spi2-atk/2.0
    /usr/include/at-spi-2.0
    /usr/include/dbus-1.0
    /usr/lib/x86_64-linux-gnu/dbus-1.0/include
    /usr/include/gtk-3.0
    /usr/include/gio-unix-2.0
    /usr/include/cairo
    /usr/include/pango-1.0
    /usr/include/fribidi
    /usr/include/harfbuzz
    /usr/include/atk-1.0
    /usr/include/cairo
    /usr/include/cairomm-1.0
    /usr/lib/x86_64-linux-gnu/cairomm-1.0/include
    /usr/include/cairo
    /usr/include/pixman-1
    /usr/include/uuid
    /usr/include/freetype2
    /usr/include/libpng16
    /usr/include/sigc++-2.0
    /usr/lib/x86_64-linux-gnu/sigc++-2.0/include
    /usr/include/gdk-pixbuf-2.0
    /usr/include/libmount
    /usr/include/blkid
    /usr/include/glib-2.0
    /usr/lib/x86_64-linux-gnu/glib-2.0/include
)

# GTK lib files
LINK_LIBRARIES(
    gtkmm-3.0
    atkmm-1.6
    gdkmm-3.0
    giomm-2.4
    pangomm-1.4
    glibmm-2.4
    gtk-3
    gdk-3
    pangocairo-1.0
    pango-1.0
    harfbuzz
    atk-1.0
    cairo-gobject
    gio-2.0
    cairomm-1.0
    cairo
    sigc-2.0
    gdk_pixbuf-2.0
    gobject-2.0
    glib-2.0
)

ADD_EXECUTABLE(n_queens
    src/main.cpp
    src/MainWindow.h
    src/MainWindow.cpp
    src/InputWindowContent.h
    src/InputWindowContent.cpp
    src/OutputWindowContent.h
    src/OutputWindowContent.cpp
    src/Board.h
    src/Board.cpp
    src/Queen.h
    src/TreeNode.h
    src/config.h
)

