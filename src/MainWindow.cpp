#include "MainWindow.h"
#include "ReportGenerator.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setupUI();
    applyStyles();
    setWindowTitle("Sistema de Mantenimiento de Satélites");
    resize(900, 700);
}

MainWindow::~MainWindow() {
}

void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Tab widget
    tabWidget = new QTabWidget();

    // Satellite form tab
    satelliteForm = new SatelliteForm();
    tabWidget->addTab(satelliteForm, "📑 Formulario");

    // Search widget tab
    searchWidget = new SearchWidget();
    tabWidget->addTab(searchWidget, "🔎 Búsqueda de Observaciones");

    mainLayout->addWidget(tabWidget);

    // Status panel
    statusPanel = new QWidget();
    QVBoxLayout *statusLayout = new QVBoxLayout(statusPanel);

    QGroupBox *healthGroup = new QGroupBox("📊 Estado General del Satélite");
    QVBoxLayout *healthLayout = new QVBoxLayout();

    healthLabel = new QLabel("Condición: -- %");
    healthLabel->setAlignment(Qt::AlignCenter);
    QFont labelFont = healthLabel->font();
    labelFont.setPointSize(14);
    labelFont.setBold(true);
    healthLabel->setFont(labelFont);

    healthBar = new QProgressBar();
    healthBar->setRange(0, 100);
    healthBar->setValue(0);
    healthBar->setTextVisible(true);
    healthBar->setFormat("%p%");
    healthBar->setMinimumHeight(30);

    healthLayout->addWidget(healthLabel);
    healthLayout->addWidget(healthBar);
    healthGroup->setLayout(healthLayout);

    // Generate report button
    generateReportBtn = new QPushButton("🖨️ Generar Reporte PDF");
    generateReportBtn->setMinimumHeight(40);
    QFont btnFont = generateReportBtn->font();
    btnFont.setPointSize(12);
    btnFont.setBold(true);
    generateReportBtn->setFont(btnFont);

    statusLayout->addWidget(healthGroup);
    statusLayout->addWidget(generateReportBtn);

    mainLayout->addWidget(statusPanel);

    setCentralWidget(centralWidget);

    // Connections
    connect(satelliteForm, &SatelliteForm::dataChanged, this, &MainWindow::onFormDataChanged);
    connect(searchWidget, &SearchWidget::observationSelected, satelliteForm, &SatelliteForm::setObservations);
    connect(generateReportBtn, &QPushButton::clicked, this, &MainWindow::onGenerateReport);
}

void MainWindow::applyStyles() {
    QString style = R"(
        QMainWindow {
            background-color: #f5f5f5;
        }
        QTabWidget::pane {
            border: 2px solid #3498db;
            background-color: white;
            border-radius: 5px;
        }
        QTabBar::tab {
            background-color: #ecf0f1;
            color: #2c3e50;
            padding: 10px 20px;
            margin: 2px;
            border-top-left-radius: 5px;
            border-top-right-radius: 5px;
        }
        QTabBar::tab:selected {
            background-color: #3498db;
            color: white;
            font-weight: bold;
        }
        QGroupBox {
            font-weight: bold;
            border: 2px solid #3498db;
            border-radius: 5px;
            margin-top: 10px;
            padding: 15px;
            background-color: white;
        }
        QGroupBox::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 5px;
            color: #3498db;
        }
        QPushButton {
            background-color: #27ae60;
            color: white;
            border: none;
            border-radius: 5px;
            padding: 10px;
        }
        QPushButton:hover {
            background-color: #2ecc71;
        }
        QPushButton:pressed {
            background-color: #229954;
        }
        QProgressBar {
            border: 2px solid #3498db;
            border-radius: 5px;
            text-align: center;
            background-color: #ecf0f1;
        }
        QProgressBar::chunk {
            background-color: #3498db;
            border-radius: 3px;
        }
    )";
    setStyleSheet(style);
}

void MainWindow::onFormDataChanged() {
    // Get data from form
    currentReport = satelliteForm->getReport();

    // Calculate health
    currentReport.calcularEstado();

    // Update display
    updateHealthDisplay();
}

void MainWindow::updateHealthDisplay() {
    int health = currentReport.healthPercent;
    healthBar->setValue(health);
    healthLabel->setText(QString("Condición: %1%").arg(health));

    // Change color based on health level
    QString barColor;
    if (health >= 80) {
        barColor = "#27ae60"; // Green
    } else if (health >= 60) {
        barColor = "#f39c12"; // Orange
    } else if (health >= 40) {
        barColor = "#e67e22"; // Dark orange
    } else {
        barColor = "#e74c3c"; // Red
    }

    QString barStyle = QString(R"(
        QProgressBar {
            border: 2px solid %1;
            border-radius: 5px;
            text-align: center;
            background-color: #ecf0f1;
        }
        QProgressBar::chunk {
            background-color: %1;
            border-radius: 3px;
        }
    )").arg(barColor);

    healthBar->setStyleSheet(barStyle);
}

void MainWindow::onGenerateReport() {
    if (currentReport.name.isEmpty() || currentReport.serial.isEmpty()) {
        QMessageBox::warning(this, "Error",
            "Por favor complete al menos el nombre y número de serie del satélite.");
        return;
    }

    // Recalculate to ensure up-to-date values
    currentReport.calcularEstado();

    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Guardar Reporte PDF",
        QString("Reporte_%1.pdf").arg(currentReport.name),
        "PDF Files (*.pdf)"
    );

    if (!fileName.isEmpty()) {
        ReportGenerator::exportToPDF(currentReport, fileName);
        QMessageBox::information(this, "Éxito",
            "El reporte PDF ha sido generado correctamente.");
    }
}
