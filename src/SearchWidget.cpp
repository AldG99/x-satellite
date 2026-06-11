#include "SearchWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>

SearchWidget::SearchWidget(QWidget *parent)
    : QWidget(parent) {
    loadCommonObservations();
    setupUI();
}

void SearchWidget::setupUI() {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Search group
    QGroupBox *searchGroup = new QGroupBox("Buscar Observaciones Comunes");
    QVBoxLayout *searchLayout = new QVBoxLayout();

    QLabel *searchLabel = new QLabel("Ingrese palabras clave para buscar:");
    searchEdit = new QLineEdit();
    searchEdit->setPlaceholderText("Ej: panel solar, batería, falla...");

    searchLayout->addWidget(searchLabel);
    searchLayout->addWidget(searchEdit);
    searchGroup->setLayout(searchLayout);

    // Results group
    QGroupBox *resultsGroup = new QGroupBox("Observaciones Disponibles");
    QVBoxLayout *resultsLayout = new QVBoxLayout();

    observationsList = new QListWidget();
    observationsList->setAlternatingRowColors(true);

    QLabel *instructionLabel = new QLabel(
        "Haga clic en una observación para seleccionarla, "
        "luego presione 'Agregar' para incluirla en el formulario."
    );
    instructionLabel->setWordWrap(true);
    instructionLabel->setStyleSheet("color: #7f8c8d; font-style: italic;");

    addButton = new QPushButton("➕ Agregar Observación Seleccionada");
    addButton->setMinimumHeight(35);

    resultsLayout->addWidget(observationsList);
    resultsLayout->addWidget(instructionLabel);
    resultsLayout->addWidget(addButton);
    resultsGroup->setLayout(resultsLayout);

    // Add groups to main layout
    mainLayout->addWidget(searchGroup);
    mainLayout->addWidget(resultsGroup);

    // Apply styles
    QString style = R"(
        QLineEdit {
            padding: 8px;
            border: 2px solid #bdc3c7;
            border-radius: 5px;
            background-color: white;
        }
        QLineEdit:focus {
            border: 2px solid #3498db;
        }
        QListWidget {
            border: 2px solid #bdc3c7;
            border-radius: 5px;
            background-color: white;
            padding: 5px;
        }
        QListWidget::item {
            padding: 8px;
            border-radius: 3px;
        }
        QListWidget::item:selected {
            background-color: #3498db;
            color: white;
        }
        QListWidget::item:hover {
            background-color: #ecf0f1;
        }
        QPushButton {
            background-color: #3498db;
            color: white;
            border: none;
            border-radius: 5px;
            padding: 10px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #5dade2;
        }
        QPushButton:pressed {
            background-color: #2980b9;
        }
    )";
    setStyleSheet(style);

    // Initialize list with all observations
    filterObservations("");

    // Connect signals
    connect(searchEdit, &QLineEdit::textChanged, this, &SearchWidget::onSearchTextChanged);
    connect(observationsList, &QListWidget::itemClicked, this, &SearchWidget::onItemClicked);
    connect(observationsList, &QListWidget::itemDoubleClicked, this, &SearchWidget::onItemClicked);
    connect(addButton, &QPushButton::clicked, this, &SearchWidget::onAddButtonClicked);
}

void SearchWidget::loadCommonObservations() {
    allObservations << "Falla en panel solar - reducción de generación de energía"
                    << "Batería degradada - capacidad reducida al 80%"
                    << "Sistema de control térmico operando normalmente"
                    << "Degradación de células solares por radiación"
                    << "Antena de comunicaciones con pérdida de ganancia"
                    << "Giroscopio presentando drift aumentado"
                    << "Propulsor con consumo irregular de combustible"
                    << "Computadora de a bordo con reinicio esporádico"
                    << "Sensor de orientación descalibrado"
                    << "Sistema de refrigeración con baja eficiencia"
                    << "Transpondedor operando fuera de especificación"
                    << "Tanque de combustible con fugas menores detectadas"
                    << "Panel solar desplegado parcialmente"
                    << "Comunicación intermitente con estación terrestre"
                    << "Cámara de observación con pixeles muertos"
                    << "Batería con temperatura elevada"
                    << "Velocidad de rotación fuera de rango nominal"
                    << "Memoria de almacenamiento con sectores dañados"
                    << "Magnetómetro con lecturas inconsistentes"
                    << "Sistema de posicionamiento GPS con error aumentado"
                    << "Circuito de distribución de potencia con anomalías"
                    << "Instrumento científico inoperante"
                    << "Recubrimiento térmico deteriorado por micrometeoritos"
                    << "Oscilador de frecuencia con deriva térmica"
                    << "Válvula de propulsión atascada en posición abierta";
}

void SearchWidget::filterObservations(const QString &filter) {
    observationsList->clear();

    if (filter.isEmpty()) {
        observationsList->addItems(allObservations);
    } else {
        QString lowerFilter = filter.toLower();
        for (const QString &obs : allObservations) {
            if (obs.toLower().contains(lowerFilter)) {
                observationsList->addItem(obs);
            }
        }
    }

    // Show message if no results
    if (observationsList->count() == 0) {
        QListWidgetItem *noResultItem = new QListWidgetItem("No se encontraron observaciones");
        noResultItem->setFlags(Qt::NoItemFlags);
        noResultItem->setForeground(Qt::gray);
        observationsList->addItem(noResultItem);
    }
}

void SearchWidget::onSearchTextChanged(const QString &text) {
    filterObservations(text);
}

void SearchWidget::onItemClicked(QListWidgetItem *item) {
    if (item && item->flags() & Qt::ItemIsEnabled) {
        emit observationSelected(item->text());
    }
}

void SearchWidget::onAddButtonClicked() {
    QListWidgetItem *currentItem = observationsList->currentItem();
    if (currentItem && currentItem->flags() & Qt::ItemIsEnabled) {
        emit observationSelected(currentItem->text());
    }
}
