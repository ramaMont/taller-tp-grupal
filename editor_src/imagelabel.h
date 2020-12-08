#include <QObject>
#include <QLabel>
#include <string>
#include <iostream>

class ImageLabel : public QLabel {
    Q_OBJECT

 public:
    std::string element_name;
    void setElementName(const std::string& element_name) {
        this->element_name = element_name;
    }

 protected slots:
}
