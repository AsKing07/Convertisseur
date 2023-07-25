#ifndef UNITCONVERTERWINDOW_H
#define UNITCONVERTERWINDOW_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QMessageBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QTextEdit>


class UnitConverterWindow : public QWidget {
    Q_OBJECT

public:
    explicit UnitConverterWindow(QWidget *parent = nullptr);

private slots:
    void convert();
    void saveConversion();
    void reset();
    void viewConversions();

private:
    // Ajoutez ici les membres nécessaires pour gérer les enregistrements de conversions si vous utilisez une base de données locale.
     QSqlDatabase database;
     void afficherErreur(const QString &message);
     void afficherInformation(const QString &message);

     QLineEdit *inputValue;
     QTextEdit *resultOutput;
     QComboBox *toUnit;
     QComboBox *fromUnit;
     QPushButton *convertButton;
     QPushButton *saveButton;
     QPushButton *resetButton;
     QPushButton *viewButton;




};

#endif // UNITCONVERTERWINDOW_H
