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
#include <dirent.h>
#include "yaml-cpp/yaml.h"
#include <SocketException.hpp>


LoginWindow::LoginWindow(ClientHolder& client_holder, QWidget *parent) : 
        QWidget(parent), client_holder(client_holder), _user_id(-1) {

    // Tamaño y titulo de la ventana
    this->resize(900, 900);
    this->setWindowTitle(QString("Wolfenstein 3D"));

    this->setStyleSheet(
    "QWidget {background-image: url(../data/login_background.jpg) }"
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
                       QMessageBox::Warning, true);
        return false;
    }

    puerto_qstring.toInt(&puerto_entero);
    if (!puerto_entero) {
        mostrarWarning(QString("El puerto debe ser un numero!"),
                       QMessageBox::Warning, true);
        return false;
    }

    // TODO: Usar puerto, nombre_qstring, server_qstring para mandar al sv.
    std::string nombre = nombre_qstring.toStdString();
    std::string puerto = puerto_qstring.toStdString();
    std::string server = server_qstring.toStdString();

    try {
        client_holder.logged(puerto, server, _user_id);
    } catch (SocketException& sockt_exc) {
        mostrarWarning(QString(sockt_exc.what()),
                       QMessageBox::Warning, true);
        return false;
    } catch (...) {
        mostrarWarning(QString("El servidor no es correcto!"),
                       QMessageBox::Warning, true);
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

void LoginWindow::cargarMapasDisponibles(QComboBox& combo_mapa,
        std::map<std::string, std::string>& mapas) {
    const std::string dir_maps = "../data/maps/";
    if (auto dir = opendir(dir_maps.c_str())) {
        while (auto f = readdir(dir)) {
            if (!f->d_name || f->d_name[0] == '.')
                continue;

            std::string filename(f->d_name);
            YAML::Node map = YAML::LoadFile(dir_maps + filename);
            std::string map_name = map["nombre"].as<std::string>();
            combo_mapa.addItem(QString::fromStdString(map_name));
            mapas.insert(std::pair<std::string, std::string>(map_name,
                                                    f->d_name));
        }
        closedir(dir);
    }
}

void LoginWindow::crearPartida(){
    QDialog dialog(this);
    dialog.setWindowTitle(QString("Crear Partida"));
    dialog.setStyleSheet("background-image: url(invalid);"
    "background-color: brown;");

    // Creo un dialog con un form
    QFormLayout form(&dialog);

    // Mapas para mostrar como opciones.
    std::map<std::string, std::string> mapas;

    // Nombre del mapa
    QComboBox combo_mapa;
    QString label_mapa = QString("Mapa");
    form.addRow(label_mapa, &combo_mapa);
    cargarMapasDisponibles(combo_mapa, mapas);

    // Cantidad de bots
    QComboBox combo_bots;
    combo_bots.addItem("0");
    combo_bots.addItem("1");
    combo_bots.addItem("2");
    combo_bots.addItem("3");
    combo_bots.addItem("4");
    QString label_bots = QString("Bots");
    form.addRow(label_bots, &combo_bots);

    // Botones
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                            Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);

    // Conecto eventos
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));
    int game_id;

    if (dialog.exec() == QDialog::Accepted) {
        std::string nombre_mapa = combo_mapa.currentText().toStdString();
        std::string archivo_mapa = mapas[nombre_mapa];
        int cantidad_bots = combo_bots.currentText().toInt();

        try {
            client_holder.crearPartida(archivo_mapa, cantidad_bots, game_id);
        } catch (SocketException& sockt_exc) {
            //TODO: Mandar a la pantalla de inicio, para volver a conectarse
            mostrarWarning(QString(sockt_exc.what()),
                        QMessageBox::Warning, true);
            loginScreen->show();
            partidaScreen->hide();
            return;
        } catch (...) {
            mostrarWarning(QString("Ha ocurrido un error, intente nuevamente"),
                        QMessageBox::Warning, true);
            loginScreen->show();
            partidaScreen->hide();
            return;
        }
    } else {
        return;
    }
    waitUntilLaunch(game_id);
}

void LoginWindow::waitUntilLaunch(int& game_id) {
    std::string message = "ID de Partida: " + std::to_string(game_id)
        + "\n";
    message += "Presione OK para lanzar la partida";
    mostrarWarning(QString::fromStdString(message),
                   QMessageBox::Information, true);
    std::cout << "LANZANDO!!!";
    // TODO: Poner un try catch aca y llevar a la pantalla 
    // inicial si se corto la conexion
    try {
        client_holder.launchGame();
        QCoreApplication::quit();
    } catch (...) {
        mostrarWarning(QString("Ha ocurrido un error en la conexión, intente nuevamente"),
                        QMessageBox::Warning, true);
        loginScreen->show();
        partidaScreen->hide();
    }
}

void LoginWindow::waitUntilAnotherUserLaunch() {
    mostrarWarning(QString("Una vez que el creador lance la partida, el juego iniciará automáticamente."),
                        QMessageBox::Information, false);
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
        try {
            client_holder.unirseAPartida(id_partida);
        } catch (SocketException& e) {
            mostrarWarning(QString(e.what()),
                        QMessageBox::Warning, true);
            return;
        } catch (...) {
            mostrarWarning(QString("Ha ocurrido un error, intente nuevamente"),
                        QMessageBox::Warning, true);
            return;
        }
        waitUntilAnotherUserLaunch();
    }
}

void LoginWindow::mostrarWarning(QString message, QMessageBox::Icon icon, bool buttons) {
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
    if (!buttons) {
        messageBox.setStandardButtons(0);
    }
    messageBox.exec();
}
