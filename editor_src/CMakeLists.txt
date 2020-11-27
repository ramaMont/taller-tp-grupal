project(qt5-demo)

# Find the QtWidgets library
find_package(Qt5Widgets)

add_executable(editor
  Editor.cpp
  dragwidget.cpp
  MapaEditable.cpp
  main.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(editor Qt5::Widgets)
