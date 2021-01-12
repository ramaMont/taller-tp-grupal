#include "LoginWindow.h"
#include <QCoreApplication>
#include <QFileDialog>
#include <QScrollBar>
#include <QDialog>
#include <QMenuBar>
#include <QList>
#include <QFormLayout>
#include <QAbstractItemView>
#include <QBoxLayout>


LoginWindow::LoginWindow(ClientHolder& client_holder, QWidget *parent) : QWidget(parent), client_holder(client_holder) {

    // Tamaño y titulo de la ventana
    this->resize(900, 900);
    this->setWindowTitle(QString("Wolfenstein 3D"));

    this->setStyleSheet(
    "QWidget {background-image: url(../login_background.jpg) }"
    "QLabel { color : white; }"
    "QLineEdit { color : white; }"
    "QMenuBar {color: white;}"
    "QMenu::item {color: white;}"
    "QMessageBox QLabel {color: white;}"
    "QPushButton {color: white; background-color: brown;}"
    "QButton {color: white; background-color: brown;}"
    "QDialogButton {color: white}"
    "QDialogButtonBox {color: white;}");

    layout = new QBoxLayout(QBoxLayout::LeftToRight, this);
    layout->setContentsMargins(100, 100, 100, 100);

    crearPartidaScreen();
    partidaScreen->hide();
    crearLogInScreen();

    // Conecto eventos
    QMetaObject::connectSlotsByName(this);
    connectEvents();
    this->show();

    // Obtengo los recursos con los que se crearan los mapas
}

void LoginWindow::crearLogInScreen() {
    loginScreen = new QWidget(this);

    loginScreen->setStyleSheet(
    "background-image: url(invalid);"
    "background-color: brown");

    // Creo un dialog con un form
    QFormLayout* form = new QFormLayout(loginScreen);

    // Agrego una lista con los campos
    QList<QLineEdit *> fields;

    // Nombre del mapa
    QLineEdit* lineEditNombre = new QLineEdit(loginScreen);
    lineEditNombre->setObjectName("Nombre");
    lineEditNombre->setFixedWidth(150);
    QString labelNombre = QString("Nombre");
    form->addRow(labelNombre, lineEditNombre);
    fields << lineEditNombre;

    // Filas
    QLineEdit* lineEditServer = new QLineEdit(loginScreen);
    lineEditServer->setObjectName("Server");
    QString labelServer = QString("Server");
    form->addRow(labelServer, lineEditServer);
    fields << lineEditServer;

    // Nombre del mapa
    QLineEdit* lineEditPuerto = new QLineEdit(loginScreen);
    lineEditPuerto->setObjectName("Puerto");
    lineEditPuerto->setFixedWidth(100);
    QString labelPuerto = QString("Puerto");
    form->addRow(labelPuerto, lineEditPuerto);
    fields << lineEditPuerto;

    QPushButton* botonLogin = new QPushButton(loginScreen);
    botonLogin->setText("Log in");
    const QSize BUTTON_SIZE = QSize(50, 30);
    botonLogin->setFixedSize(BUTTON_SIZE);
    botonLogin->setObjectName(QStringLiteral("botonLogin"));

    form->addRow(botonLogin);
    form->setAlignment(botonLogin, Qt::AlignHCenter);

    layout->addWidget(loginScreen, Qt::AlignCenter);

    loginScreen->setFixedWidth(300);
    loginScreen->setFixedHeight(140);
}

void LoginWindow::login() {
    if (!validarCampos()) return;
    std::cout << "Campos correctos!" << std::endl;
    loginScreen->hide();
    partidaScreen->show();
}

void LoginWindow::crearPartidaScreen() {
    partidaScreen = new QWidget(this);

    partidaScreen->setStyleSheet(
    "background-image: url(invalid);");

    // Creo un dialog con un form
    QHBoxLayout* hlayout = new QHBoxLayout(partidaScreen);

    QPushButton* botonCrear = new QPushButton(partidaScreen);
    botonCrear->setStyleSheet("background-color: brown;");
    botonCrear->setText("Crear Partida");
    botonCrear->setObjectName(QStringLiteral("botonCrear"));

    QPushButton* botonUnirse = new QPushButton(partidaScreen);
    botonUnirse->setStyleSheet("background-color: brown;");
    botonUnirse->setText("Unirse a Partida");
    botonUnirse->setObjectName(QStringLiteral("botonUnirse"));

    hlayout->addWidget(botonCrear);
    hlayout->addWidget(botonUnirse);
    hlayout->setAlignment(botonCrear, Qt::AlignHCenter);

    layout->addWidget(partidaScreen, Qt::AlignCenter);

    partidaScreen->setFixedWidth(300);
    partidaScreen->setFixedHeight(140);
}

bool LoginWindow::validarCampos() {
    bool puerto_entero = false;
    // int puerto;
    QLineEdit* nombreEdit = findChild<QLineEdit*>("Nombre");
    QLineEdit* serverEdit = findChild<QLineEdit*>("Server");
    QLineEdit* puertoEdit = findChild<QLineEdit*>("Puerto");
    QString puerto_qstring = puertoEdit->text();
    QString nombre_qstring = nombreEdit->text();
    QString server_qstring = serverEdit->text();

    if ((puerto_qstring.length() == 0) || (nombre_qstring.length() == 0)
        || (server_qstring.length() == 0)) {
        mostrarWarning(QString("Todos los campos deben completarse!"),
                       QMessageBox::Warning);
        return false;
    }

    puerto_qstring.toInt(&puerto_entero);
    if (!puerto_entero) {
        mostrarWarning(QString("El puerto debe ser un numero!"),
                       QMessageBox::Warning);
        return false;
    }

    // TODO: Usar puerto, nombre_qstring, server_qstring para mandar al sv.
    std::string nombre = nombre_qstring.toStdString();
    std::string puerto = puerto_qstring.toStdString();
    std::string server = server_qstring.toStdString();

    try {
        client_holder.logged(nombre, puerto, server);
    } catch (...) {
        mostrarWarning(QString("El servidor no es correcto!"),
                       QMessageBox::Warning);
        return false;
    }

    return true;
}

void LoginWindow::connectEvents() {
    // Conecto el evento del boton
    QPushButton* botonLogin = findChild<QPushButton*>("botonLogin");
    QPushButton* botonCrear = findChild<QPushButton*>("botonCrear");
    QPushButton* botonUnirse = findChild<QPushButton*>("botonUnirse");
    QObject::connect(botonLogin, &QPushButton::clicked,
                     this, &LoginWindow::login);
    QObject::connect(botonCrear, &QPushButton::clicked,
                     this, &LoginWindow::crearPartida);
    QObject::connect(botonUnirse, &QPushButton::clicked,
                     this, &LoginWindow::unirseAPartida);
}

void LoginWindow::crearPartida(){
    QDialog dialog(this);
    dialog.setWindowTitle(QString("Crear Partida"));
    dialog.setStyleSheet("background-image: url(invalid);"
    "background-color: brown;");

    // Creo un dialog con un form
    QFormLayout form(&dialog);

    // Agrego una lista con los campos
    QList<QLineEdit *> fields;

    // Nombre del mapa
    QLineEdit lineEditIDMapa(&dialog);
    QString labelIDMapa = QString("ID Mapa");
    form.addRow(labelIDMapa, &lineEditIDMapa);
    fields << &lineEditIDMapa;

    // Botones
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                            Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    // Conecto eventos
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted){
        int game_id;
        // If the user didn't dismiss the dialog, do something with the fields
        std::string id_mapa = lineEditIDMapa.text().toStdString();

        // TODO: usar el id_mapa
        //QCoreApplication::quit();
        try {
            client_holder.crearPartida(id_mapa, game_id);
        } catch (...) {
            mostrarWarning(QString("Ha ocurrido un error, intente nuevamente"),
                        QMessageBox::Warning);
        }
    }
}

void LoginWindow::unirseAPartida() {
    QDialog dialog(this);
    dialog.setWindowTitle(QString("Unirse a Partida"));
    dialog.setStyleSheet("background-image: url(invalid);"
    "background-color: brown;");

    // Creo un dialog con un form
    QFormLayout form(&dialog);

    // Agrego una lista con los campos
    QList<QLineEdit *> fields;

    // Nombre del mapa
    QLineEdit lineEditIdPartida(&dialog);
    QString labelIdPartida = QString("ID Partida");
    form.addRow(labelIdPartida, &lineEditIdPartida);
    fields << &lineEditIdPartida;

    // Botones
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                            Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    // Conecto eventos
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    // Show the dialog as modal
    if (dialog.exec() == QDialog::Accepted) {
        // TODO: usar el id partida
        std::string id_partida = lineEditIdPartida.text().toStdString();
        //QCoreApplication::exit();
        client_holder.unirseAPartida(id_partida);
    }
}

void LoginWindow::mostrarWarning(QString message, QMessageBox::Icon icon) {
    QMessageBox messageBox(this);
    messageBox.setStyleSheet(
    "QWidget {background-image: url(../imgs/fondo3.png); background-color: brown; }"
    "QLabel { color : white; }"
    "QMenuBar {color: white;}"
    "QMenu::item {color: white;}"
    "QMessageBox QLabel {color: white;}"
    "QPushButton {color: white;}"
    "QButton {color: white;}"
    "QDialogButton {color: white}"
    "QDialogButtonBox {color: white;}");
    messageBox.setText(message);
    messageBox.setWindowTitle("Aviso");
    messageBox.setIcon(icon);
    messageBox.exec();
}