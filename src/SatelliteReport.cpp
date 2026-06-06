#include "SatelliteReport.h"
#include <QStringList>

SatelliteReport::SatelliteReport()
    : componentsComplete(true), healthPercent(0) {
}

int SatelliteReport::calcularEstado() {
    int baseScore = getStatusWeight();

    // Apply penalty for missing components (-15%)
    if (!componentsComplete) {
        baseScore -= 15;
    }

    // Apply penalty for critical observations (-10%)
    if (hasCriticalObservations()) {
        baseScore -= 10;
    }

    // Ensure the score is within valid range [0, 100]
    if (baseScore < 0) baseScore = 0;
    if (baseScore > 100) baseScore = 100;

    healthPercent = baseScore;
    return healthPercent;
}

int SatelliteReport::getStatusWeight() const {
    if (status == "Bueno") {
        return 100;
    } else if (status == "Regular") {
        return 70;
    } else if (status == "Malo") {
        return 40;
    } else if (status == "Fatal") {
        return 15;
    }
    return 50; // Default value if status is not recognized
}

bool SatelliteReport::hasCriticalObservations() const {
    QString obsLower = observations.toLower();

    // List of critical keywords
    QStringList criticalKeywords = {
        "falla", "critico", "crítico", "grave", "severo",
        "daño", "roto", "destruido", "perdida", "pérdida",
        "inoperante", "no funciona", "error fatal"
    };

    for (const QString& keyword : criticalKeywords) {
        if (obsLower.contains(keyword)) {
            return true;
        }
    }

    return false;
}
