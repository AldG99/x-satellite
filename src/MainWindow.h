#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include <QProgressBar>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "SatelliteForm.h"
#include "SearchWidget.h"
#include "SatelliteReport.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onFormDataChanged();
    void onGenerateReport();

private:
    void setupUI();
    void applyStyles();
    void updateHealthDisplay();

    // Widgets
    QTabWidget *tabWidget;
    SatelliteForm *satelliteForm;
    SearchWidget *searchWidget;

    // Status panel
    QWidget *statusPanel;
    QProgressBar *healthBar;
    QLabel *healthLabel;
    QPushButton *generateReportBtn;

    // Data
    SatelliteReport currentReport;
};

#endif // MAINWINDOW_H
