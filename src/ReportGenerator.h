#ifndef REPORTGENERATOR_H
#define REPORTGENERATOR_H

#include <QString>
#include "SatelliteReport.h"

class ReportGenerator {
public:
    static void exportToPDF(const SatelliteReport &report, const QString &fileName);

private:
    ReportGenerator() = delete; // Static class, no instances
};

#endif // REPORTGENERATOR_H
