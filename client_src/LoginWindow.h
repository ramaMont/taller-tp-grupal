#ifndef GREETER_H
#define GREETER_H

#include "ClientHolder.h"

#include <string>
#include <iostream>
#include <map>

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
#include <QGridLayout>
#include <QStandardItemModel>
#include <QVariant>
#include <QScrollArea>
#include <QMessageBox>
#include <QBoxLayout>


class LoginWindow : public QWidget {
public:
    explicit LoginWindow(ClientHolder& client_holder, QWidget *parent = 0);

private:
    // Creo los widgets asignandole un padre
    void crearLogInScreen();
    void crearPartidaScreen();
    void connectEvents();
    void login();
    void mostrarWarning(QString message, QMessageBox::Icon icon, bool buttons);
    void waitUntilLaunch(int& game_id);
    void waitUntilAnotherUserLaunch();
    bool validarCampos();
    void crearPartida();
    void unirseAPartida();
    void cargarMapasDisponibles(QComboBox& combo_mapa,
                                std::map<std::string, std::string>& mapas);
    QBoxLayout* layout;
    QWidget* loginScreen;
    QWidget* partidaScreen;
    QLabel* labelId;
    ClientHolder& client_holder;
    int _user_id;
};

#endif // GREETER_H
