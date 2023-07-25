#include "unitconverterwindow.h"
#include <QRegExpValidator>
#include <QMap>
#include <cmath>


UnitConverterWindow::UnitConverterWindow(QWidget *parent) : QWidget(parent)
{
    // Le code pour créer l'interface utilisateur, les signaux, les slots, etc. va ici.
    // Créer les widgets
    QFormLayout *formLayout = new QFormLayout;
    inputValue = new QLineEdit;
    fromUnit = new QComboBox;
    toUnit = new QComboBox;
    resultOutput = new QTextEdit;
    resultOutput->setReadOnly(true);
    convertButton = new QPushButton("Convertir");
    saveButton = new QPushButton("Enregistrer");
    resetButton = new QPushButton("Réinitialiser");
    viewButton = new QPushButton("Consulter conversions");

    // Ajouter les options d'unités dans les combobox
    fromUnit->addItems({"Ligne", "Pouce", "Pied", "Yard", "Mile", "Millimètre", "Centimètre", "Mètre", "Kilomètre"});
    toUnit->addItems({"Ligne", "Pouce", "Pied", "Yard", "Mile", "Millimètre", "Centimètre", "Mètre", "Kilomètre"});

    // Connecter le bouton de conversion à la fonction de conversion
    connect(convertButton, &QPushButton::clicked, this, &UnitConverterWindow::convert);

    // Connecter le bouton d'enregistrement à la fonction d'enregistrement
    connect(saveButton, &QPushButton::clicked, this, &UnitConverterWindow::saveConversion);

    // Connecter le bouton de réinitialisation à la fonction de réinitialisation
    connect(resetButton, &QPushButton::clicked, this, &UnitConverterWindow::reset);

    // Connecter le bouton de consultation à la fonction de consultation des anciennes conversions
    connect(viewButton, &QPushButton::clicked, this, &UnitConverterWindow::viewConversions);

    // Ajouter les widgets au layout
    formLayout->addRow("Valeur à convertir:", inputValue);
    formLayout->addRow("De l'unité:", fromUnit);
    formLayout->addRow("Vers l'unité:", toUnit);
    formLayout->addRow("Résultat:", resultOutput);
    formLayout->addRow(convertButton, saveButton);
    formLayout->addRow(resetButton, viewButton);

    setLayout(formLayout);



    // Ouvrir la connexion à la base de données
        database = QSqlDatabase::addDatabase("QSQLITE");
        database.setDatabaseName("../Build/convertisseur.db"); //  chemin vers votre la bdd convertisseur.db

        if (!database.open())
        {
            afficherErreur("Erreur de chargement de la base données!");

        }

      // Créer un objet QRegExpValidator pour limiter l'entrée à des nombres entiers ou à virgule
           QRegExpValidator *validator = new QRegExpValidator(QRegExp("[0-9]+(\\.[0-9]*)?"), this);
           inputValue->setValidator(validator);
}

void UnitConverterWindow::afficherErreur(const QString &message)
{
    QMessageBox::critical(this, "Erreur", message);
}

void UnitConverterWindow::afficherInformation(const QString &message)
{
    QMessageBox::information(this,"Information",message);
}

void UnitConverterWindow::convert() {
    // Récupérer la valeur à convertir depuis le QLineEdit
    QString inputValueText = inputValue->text();
    bool ok;
    double inputValue = inputValueText.toDouble(&ok);

    if (!ok) {
        resultOutput->setText("Valeur invalide !");
        return;
    }

    // Récupérer les unités sélectionnées dans les QComboBox
    QString fromUnitText = fromUnit->currentText();
    QString toUnitText = toUnit->currentText();

    // Définir les équivalences de conversion dans un QMap
    QMap<QString, double> conversionMap;
    conversionMap.insert("Ligne", 0.2116);
    conversionMap.insert("Pouce", 2.54);
    conversionMap.insert("Pied", 30.48);
    conversionMap.insert("Yard", 91.44);
    conversionMap.insert("Mile", 160934.4 );
    conversionMap.insert("Millimètre", 0.1);
    conversionMap.insert("Centimètre", 1);
    conversionMap.insert("Mètre", 100);
    conversionMap.insert("Kilomètre", 100000);

    // Vérifier si les unités sélectionnées sont présentes dans le QMap
    if (!conversionMap.contains(fromUnitText) || !conversionMap.contains(toUnitText)) {
        resultOutput->setText("Unités de conversion invalides !");
        return;
    }

    // Effectuer la conversion en utilisant le QMap
    double fromUnitInCm = conversionMap.value(fromUnitText);
    double toUnitInCm = conversionMap.value(toUnitText);
    double result = (inputValue * fromUnitInCm) / toUnitInCm;

        // Arrondir le résultat à 6 décimales pour réduire les marges d'erreur
        result = round(result * 100000) / 100000;

    // Afficher le résultat dans le QTextEdit
    QString resultText = QString::number(result, 'g', 15);
    resultOutput->setText(resultText);
}

void UnitConverterWindow::saveConversion()
{
    // Récupérer la valeur et les unités de conversion à partir des widgets appropriés
    QString value = inputValue->text();
    QString unitedepart = fromUnit->currentText();
    QString unitearrive = toUnit->currentText();
    QString result = resultOutput->toPlainText();

    if(value.isEmpty() || unitearrive.isEmpty() || unitedepart.isEmpty() || result.isEmpty())
    {
        afficherErreur("Assurer vous d'abord de remplir les champs de conversion et d'effectuer une conversion");
    }
    else
    {
        // Exécuter la requête SQL pour insérer les données dans la table de la base de données
        QSqlQuery query;
        query.prepare("INSERT INTO conversions (valeur, unite_depart, unite_arrive, resultat) VALUES (:value, :fromUnit, :toUnit, :result)");
        query.bindValue(":value", value);
        query.bindValue(":fromUnit", unitedepart);
        query.bindValue(":toUnit", unitearrive);
        query.bindValue(":result", result);

        if (!query.exec())
        {
            // Afficher un message d'erreur si l'insertion échoue
            afficherErreur("Erreur lors de l'enregistrement de la conversion");
        }
        else
        {
            afficherInformation("L'enregistrement a bien été effectué.");
        }
    }


}



void UnitConverterWindow::reset()
{
    // Exécuter une requête SQL pour supprimer tous les enregistrements de conversions
    QSqlQuery query("DELETE FROM conversions");

    if (!query.exec()) {
        // Afficher un message d'erreur si la réinitialisation échoue
        QMessageBox::critical(this, "Erreur de réinitialisation", "La réinitialisation a échoué.");
    } else {
        // Afficher un message de confirmation si la réinitialisation est réussie
        QMessageBox::information(this, "Réinitialisation réussie", "Toutes les conversions ont été réinitialisées.");
    }
}





void UnitConverterWindow::viewConversions()
{
    // Exécuter une requête SELECT pour récupérer les anciennes conversions
    QSqlQuery query("SELECT * FROM conversions");
    QString allConversions;
    while (query.next())
    {
        // Récupérer les données de chaque enregistrement
        QString value = query.value(1).toString();
        QString fromUnit = query.value(2).toString();
        QString toUnit = query.value(3).toString();
        QString result = query.value(4).toString();

        // Formater les données dans une chaîne pour l'affichage
             QString conversionData = QString("%1 %2 -> %3 %4\n").arg(value, fromUnit, result, toUnit);
             allConversions.append(conversionData);

    }
    // Afficher les données dans la fenêtre ou la boîte de dialogue appropriée
      if (allConversions.isEmpty())
      {
         QMessageBox::information(this, "Anciennes Conversions", "Aucune conversion enregistrée.");
      }
      else
      {
          QMessageBox::information(this, "Anciennes Conversions", allConversions);
      }
}

