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

#include "EnvVariablesGetter.h"

LoginWindow::LoginWindow(ClientHolder& client_holder, QWidget *parent) : 
        QWidget(parent), client_holder(client_holder), _user_id(-1) {

    // Tamaño y titulo de la ventana
    this->resize(770, 900);
    this->setWindowTitle(QString("Wolfenstein 3D"));

    EnvVariablesGetter envVariablesGetter;
    QString data_path = QString::fromUtf8(envVariablesGetter.getDataPath().c_str());

    this->setStyleSheet(
    "QWidget {background-image: url("+data_path+"/login_background.jpg) }"
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

    QLineEdit* lineEditServer = new QLineEdit(loginScreen);
    lineEditServer->setObjectName("Server");
    QString labelServer = QString("Server");
    form->addRow(labelServer, lineEditServer);
    fields << lineEditServer;

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
    loginScreen->setFixedHeight(110);
}

void LoginWindow::login() {
    if (!validarCampos()) return;
    std::string msg = "Tu Nº de jugador: " + std::to_string(_user_id);
    labelId->setText(QString::fromStdString(msg));
    loginScreen->hide();
    partidaScreen->show();
}

void LoginWindow::crearPartidaScreen() {
    partidaScreen = new QWidget(this);

    partidaScreen->setStyleSheet(
    "background-image: url(invalid);");

    QFormLayout* form = new QFormLayout(partidaScreen);

    // Resolucion
    combo_resolution = new QComboBox();
    combo_resolution->addItem("320:200");
    combo_resolution->addItem("640:400");
    label_resolution = new QLabel(partidaScreen);
    label_resolution->setStyleSheet("background-color: brown;");
    label_resolution->setText("Resolución");
    label_resolution->setFixedWidth(100);
    label_resolution->setAlignment(Qt::AlignCenter);
    combo_resolution->setMaximumWidth(200);

    // Fullscreen
    combo_fullscreen = new QComboBox();
    combo_fullscreen->addItem("Si");
    combo_fullscreen->addItem("No");
    label_fullscreen = new QLabel(partidaScreen);
    label_fullscreen->setStyleSheet("background-color: brown;");
    label_fullscreen->setText("Fullscreen");
    label_fullscreen->setFixedWidth(100);
    label_fullscreen->setAlignment(Qt::AlignCenter);
    combo_fullscreen->setMaximumWidth(50);

    // Botones
    QPushButton* botonCrear = new QPushButton(partidaScreen);
    botonCrear->setStyleSheet("background-color: brown;");
    botonCrear->setText("Crear Partida");
    botonCrear->setObjectName(QStringLiteral("botonCrear"));

    QPushButton* botonUnirse = new QPushButton(partidaScreen);
    botonUnirse->setStyleSheet("background-color: brown;");
    botonUnirse->setText("Unirse a Partida");
    botonUnirse->setObjectName(QStringLiteral("botonUnirse"));

    labelId = new QLabel(partidaScreen);
    labelId->setStyleSheet("background-color: brown;");
    labelId->setFixedHeight(25);
    labelId->setAlignment(Qt::AlignCenter);

    form->addRow(labelId);
    form->addRow(label_resolution, combo_resolution);
    form->addRow(label_fullscreen, combo_fullscreen);
    form->addRow(botonCrear, botonUnirse);

    layout->addWidget(partidaScreen, Qt::AlignCenter);

    partidaScreen->setFixedWidth(300);
    partidaScreen->setFixedHeight(140);
}

bool LoginWindow::validarCampos() {
    bool puerto_entero = false;
    QLineEdit* serverEdit = findChild<QLineEdit*>("Server");
    QLineEdit* puertoEdit = findChild<QLineEdit*>("Puerto");
    QString puerto_qstring = puertoEdit->text();
    QString server_qstring = serverEdit->text();

    if ((puerto_qstring.length() == 0) || (server_qstring.length() == 0)) {
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

    EnvVariablesGetter envVariablesGetter;
    const std::string dir_maps = envVariablesGetter.getMapsPath();
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
    combo_bots.setMaximumWidth(50);
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
        std::string resolution = combo_resolution->currentText().toStdString();
        std::string fullscreen_str = combo_fullscreen->currentText().toStdString();
        bool fullscreen = (fullscreen_str == "Si") ? true : false;

        try {
            client_holder.crearPartida(archivo_mapa, cantidad_bots, game_id,
                                       resolution, fullscreen);
        } catch (SocketException& sockt_exc) {
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

void LoginWindow::waitUntilLaunch(int game_id) {
    std::string message = "Clave Secreta: " + std::to_string(game_id);
    message += "     Tu Nº de Jugador: " + std::to_string(_user_id) + "\n";
    message += "Presione OK para lanzar la partida";
    mostrarWarning(QString::fromStdString(message),
                   QMessageBox::Information, true);
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
    QString labelIdPartida = QString("Clave Secreta");
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
        std::string resolution = combo_resolution->currentText().toStdString();
        std::string fullscreen_str = combo_fullscreen->currentText().toStdString();
        bool fullscreen = (fullscreen_str == "Si") ? true : false;
        try {
            client_holder.unirseAPartida(id_partida, resolution, fullscreen);
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
