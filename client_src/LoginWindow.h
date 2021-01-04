#ifndef GREETER_H
#define GREETER_H

#include <string>
#include <iostream>
#include <QApplication>
#include <QMouseEvent>
#include <QtWidgets>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QMimeData>
#include <QPainter>
#include <QDrag>
#include <map>
#include <QGridLayout>
#include <QStandardItemModel>
#include <QVariant>
#include <QScrollArea>
#include <QMessageBox>
#include <QBoxLayout>

class LoginWindow : public QWidget {
public:
    explicit LoginWindow(QWidget *parent = 0);

private:
    // Creo los widgets asignandole un padre
    void crearLogInScreen();
    void crearPartidaScreen();
    void connectEvents();
    void login();
    void mostrarWarning(QString message, QMessageBox::Icon icon);
    bool validarCampos();
    void crearPartida();
    void unirseAPartida();
    QBoxLayout* layout;
    QWidget* loginScreen;
    QWidget* partidaScreen;
};

#endif // GREETER_H
