#include <QApplication>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Set application metadata
    app.setApplicationName("Sistema de Mantenimiento de Satélites");
    app.setApplicationVersion("1.0.0");
    app.setOrganizationName("Aerospace Engineering");

    // Create and show main window
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
