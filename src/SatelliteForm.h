#ifndef SATELLITEFORM_H
#define SATELLITEFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QTextEdit>
#include <QLabel>
#include "SatelliteReport.h"

class SatelliteForm : public QWidget {
    Q_OBJECT

public:
    explicit SatelliteForm(QWidget *parent = nullptr);

    // Get current form data as a report
    SatelliteReport getReport() const;

public slots:
    void setObservations(const QString &text);

signals:
    void dataChanged();

private slots:
    void onFieldChanged();

private:
    void setupUI();

    // Form fields
    QLineEdit *nameEdit;
    QLineEdit *serialEdit;
    QLineEdit *codeEdit;
    QComboBox *statusCombo;
    QCheckBox *componentsCheck;
    QTextEdit *observationsEdit;
};

#endif // SATELLITEFORM_H
