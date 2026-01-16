#include "SatelliteForm.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QGroupBox>

SatelliteForm::SatelliteForm(QWidget *parent)
    : QWidget(parent) {
    setupUI();
}

void SatelliteForm::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Basic information group
    QGroupBox *basicGroup = new QGroupBox("Información Básica");
    QFormLayout *basicLayout = new QFormLayout();

    nameEdit = new QLineEdit();
    nameEdit->setPlaceholderText("Ej: Satélite Geoestacionario-1");
    serialEdit = new QLineEdit();
    serialEdit->setPlaceholderText("Ej: SN-2024-001");
    codeEdit = new QLineEdit();
    codeEdit->setPlaceholderText("Ej: SAT-GEO-01");

    basicLayout->addRow("Nombre del Satélite:", nameEdit);
    basicLayout->addRow("Número de Serie:", serialEdit);
    basicLayout->addRow("Código de Identificación:", codeEdit);
    basicGroup->setLayout(basicLayout);

    // Status and components group
    QGroupBox *statusGroup = new QGroupBox("Estado y Componentes");
    QFormLayout *statusLayout = new QFormLayout();

    statusCombo = new QComboBox();
    statusCombo->addItems({"Bueno", "Regular", "Malo", "Fatal"});
    statusCombo->setCurrentIndex(0);

    componentsCheck = new QCheckBox("Componentes completos");
    componentsCheck->setChecked(true);

    statusLayout->addRow("Estado del Satélite:", statusCombo);
    statusLayout->addRow("Componentes:", componentsCheck);
    statusGroup->setLayout(statusLayout);

    // Observations group
    QGroupBox *obsGroup = new QGroupBox("Observaciones");
    QVBoxLayout *obsLayout = new QVBoxLayout();

    QLabel *obsLabel = new QLabel("Ingrese observaciones sobre el estado del satélite:");
    observationsEdit = new QTextEdit();
    observationsEdit->setPlaceholderText(
        "Ej: Panel solar B presenta degradación del 15%.\n"
        "Sistema de control térmico operando normalmente.\n"
        "Batería con capacidad reducida al 80%."
    );
    observationsEdit->setMinimumHeight(150);

    obsLayout->addWidget(obsLabel);
    obsLayout->addWidget(observationsEdit);
    obsGroup->setLayout(obsLayout);

    // Add all groups to main layout
    mainLayout->addWidget(basicGroup);
    mainLayout->addWidget(statusGroup);
    mainLayout->addWidget(obsGroup);
    mainLayout->addStretch();

    // Apply styles
    QString style = R"(
        QLineEdit, QComboBox, QTextEdit {
            padding: 8px;
            border: 2px solid #bdc3c7;
            border-radius: 5px;
            background-color: white;
        }
        QLineEdit:focus, QComboBox:focus, QTextEdit:focus {
            border: 2px solid #3498db;
        }
        QCheckBox {
            spacing: 8px;
        }
        QCheckBox::indicator {
            width: 20px;
            height: 20px;
        }
        QCheckBox::indicator:unchecked {
            border: 2px solid #bdc3c7;
            background-color: white;
            border-radius: 3px;
        }
        QCheckBox::indicator:checked {
            border: 2px solid #3498db;
            background-color: #3498db;
            border-radius: 3px;
            image: url(data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHdpZHRoPSIxNiIgaGVpZ2h0PSIxNiIgdmlld0JveD0iMCAwIDI0IDI0IiBmaWxsPSJub25lIiBzdHJva2U9IndoaXRlIiBzdHJva2Utd2lkdGg9IjMiIHN0cm9rZS1saW5lY2FwPSJyb3VuZCIgc3Ryb2tlLWxpbmVqb2luPSJyb3VuZCI+PHBvbHlsaW5lIHBvaW50cz0iMjAgNiA5IDE3IDQgMTIiPjwvcG9seWxpbmU+PC9zdmc+);
        }
    )";
    setStyleSheet(style);

    // Connect signals
    connect(nameEdit, &QLineEdit::textChanged, this, &SatelliteForm::onFieldChanged);
    connect(serialEdit, &QLineEdit::textChanged, this, &SatelliteForm::onFieldChanged);
    connect(codeEdit, &QLineEdit::textChanged, this, &SatelliteForm::onFieldChanged);
    connect(statusCombo, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &SatelliteForm::onFieldChanged);
    connect(componentsCheck, &QCheckBox::stateChanged, this, &SatelliteForm::onFieldChanged);
    connect(observationsEdit, &QTextEdit::textChanged, this, &SatelliteForm::onFieldChanged);
}

SatelliteReport SatelliteForm::getReport() const {
    SatelliteReport report;
    report.name = nameEdit->text();
    report.serial = serialEdit->text();
    report.code = codeEdit->text();
    report.status = statusCombo->currentText();
    report.componentsComplete = componentsCheck->isChecked();
    report.observations = observationsEdit->toPlainText();
    return report;
}

void SatelliteForm::setObservations(const QString &text) {
    QString currentText = observationsEdit->toPlainText();
    if (!currentText.isEmpty() && !currentText.endsWith("\n")) {
        currentText += "\n";
    }
    observationsEdit->setPlainText(currentText + text);
}

void SatelliteForm::onFieldChanged() {
    emit dataChanged();
}
