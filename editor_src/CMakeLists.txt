project(qt5-demo)

# Find the QtWidgets library
find_package(Qt5Widgets)

add_executable(editor
  ResourcesWidget.cpp
  Editor.cpp
  MapaEditable.cpp
  MapWidget.cpp
  main.cpp)

# Use the Widgets module from Qt 5.
target_link_libraries(editor Qt5::Widgets)
