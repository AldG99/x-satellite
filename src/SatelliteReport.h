#ifndef SATELLITEREPORT_H
#define SATELLITEREPORT_H

#include <QString>

class SatelliteReport {
public:
    SatelliteReport();

    // Satellite data
    QString name;
    QString serial;
    QString code;
    QString status;
    bool componentsComplete;
    QString observations;
    int healthPercent;

    // Calculate satellite health percentage
    int calcularEstado();

private:
    // Helper method to check for critical observations
    bool hasCriticalObservations() const;
    int getStatusWeight() const;
};

#endif // SATELLITEREPORT_H
