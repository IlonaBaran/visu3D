#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "openglwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton *button = findChild<QPushButton*>("pushButton");
    QObject::connect(button, &QPushButton::clicked, this, &MainWindow::comboBoxValue);

    QPushButton *button_2 = findChild<QPushButton*>("pushButton_2");
    QObject::connect(button_2, &QPushButton::clicked, this, &MainWindow::backGroundValue);

    // couche cachée ou non
    //connect(checkBoxObjet, SIGNAL(stateChanged(int)), this, SLOT(onCheckBoxStateChanged(int)));

    // Rendre l'option désactivée
    QComboBox* comboBox = findChild<QComboBox*>("comboBox");
    ui->comboBox->setItemData(4, 0, Qt::UserRole - 1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::comboBoxValue() {
    QString selectedValue;

    // Récupérer la valeur sélectionnée dans la QComboBox
    QComboBox* comboBox = findChild<QComboBox*>("comboBox");
    if (comboBox) {
        selectedValue = comboBox->currentText();
    }

    QString file ;

    // Choisir le fichier à visualiser en fonction du choix de la combobox
    if (selectedValue == "cityjson"){
        file = openFile("Fichiers (*.cityjson)");
    } else if (selectedValue == "nuage"){
        file = openFile("Fichiers (*.ply)");
    } else if (selectedValue == "objet"){
        file = openFile("Fichiers (*.obj)");
    } else if (selectedValue == "points"){
        file = "points";
    } else if (selectedValue == "cube"){
        file = "cube";
    }

    // Création QCheckBox et activé car visible par défaut
    QCheckBox *checkBox = new QCheckBox(file, this);
    checkBox->setChecked(true);

    // Ajout dans le layout crée
    QVBoxLayout *layout = findChild<QVBoxLayout*>("verticalLayout");

    // Ajoute du QCheckBox au layout
    layout->addWidget(checkBox);

    ui->openGLWidget->setSelectedValue(selectedValue, file);
    ui->openGLWidget->update();
}


QString MainWindow::openFile(QString type)
{
    QFileDialog dialog(this, tr("Sélectionner un fichier"));
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(type);

    if (dialog.exec()) {
        QStringList fileNames = dialog.selectedFiles();

        if (!fileNames.isEmpty()) {
            QString filePath = fileNames.first();
            return filePath;
        }
    } else {
        return NULL;
    }
}


void MainWindow::backGroundValue() {
    // Récupérez le texte des QDoubleSpinBox
    float number1 = findChild<QDoubleSpinBox*>("number1")->value();
    float number2 = findChild<QDoubleSpinBox*>("number2")->value();
    float number3 = findChild<QDoubleSpinBox*>("number3")->value();

    ui->openGLWidget->setSelectedValueBis(number1, number2, number3);
    ui->openGLWidget->update();
}
