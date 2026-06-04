#include "ReportGenerator.h"
#include <QPrinter>
#include <QPainter>
#include <QTextDocument>
#include <QDateTime>

void ReportGenerator::exportToPDF(const SatelliteReport &report, const QString &fileName) {
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(fileName);
    printer.setPageSize(QPageSize::A4);
    printer.setPageMargins(QMarginsF(20, 20, 20, 20), QPageLayout::Millimeter);

    QPainter painter(&printer);

    int pageWidth = printer.pageRect(QPrinter::DevicePixel).width();
    int yPos = 0;
    int lineHeight = 60;
    int sectionSpacing = 80;

    // Helper lambda for drawing text
    auto drawText = [&](const QString &text, const QFont &font, const QColor &color = Qt::black) {
        painter.setFont(font);
        painter.setPen(color);
        QRect rect(0, yPos, pageWidth, lineHeight * 2);
        painter.drawText(rect, Qt::AlignLeft | Qt::TextWordWrap, text);
        yPos += lineHeight;
    };

    auto drawSeparator = [&]() {
        painter.setPen(QPen(QColor(52, 152, 219), 3));
        painter.drawLine(0, yPos + 20, pageWidth, yPos + 20);
        yPos += 50;
    };

    // Title
    QFont titleFont("Arial", 24, QFont::Bold);
    drawText("REPORTE DE MANTENIMIENTO DE SATÉLITE", titleFont, QColor(41, 128, 185));
    yPos += 20;

    // Date and time
    QFont dateFont("Arial", 10);
    QString dateStr = QString("Fecha de generación: %1")
        .arg(QDateTime::currentDateTime().toString("dd/MM/yyyy hh:mm:ss"));
    drawText(dateStr, dateFont, QColor(127, 140, 141));
    yPos += sectionSpacing;

    drawSeparator();

    // Basic Information Section
    QFont sectionFont("Arial", 16, QFont::Bold);
    QFont labelFont("Arial", 11, QFont::Bold);
    QFont valueFont("Arial", 11);

    drawText("INFORMACIÓN BÁSICA", sectionFont, QColor(52, 152, 219));
    yPos += 30;

    // Name
    painter.setFont(labelFont);
    painter.setPen(Qt::black);
    painter.drawText(0, yPos, "Nombre del Satélite:");
    painter.setFont(valueFont);
    painter.drawText(250, yPos, report.name);
    yPos += lineHeight;

    // Serial
    painter.setFont(labelFont);
    painter.drawText(0, yPos, "Número de Serie:");
    painter.setFont(valueFont);
    painter.drawText(250, yPos, report.serial);
    yPos += lineHeight;

    // Code
    painter.setFont(labelFont);
    painter.drawText(0, yPos, "Código de Identificación:");
    painter.setFont(valueFont);
    painter.drawText(250, yPos, report.code);
    yPos += lineHeight + sectionSpacing;

    drawSeparator();

    // Status Section
    drawText("ESTADO Y COMPONENTES", sectionFont, QColor(52, 152, 219));
    yPos += 30;

    // Status
    painter.setFont(labelFont);
    painter.drawText(0, yPos, "Estado del Satélite:");
    painter.setFont(valueFont);

    QColor statusColor;
    if (report.status == "Bueno") statusColor = QColor(39, 174, 96);
    else if (report.status == "Regular") statusColor = QColor(243, 156, 18);
    else if (report.status == "Malo") statusColor = QColor(230, 126, 34);
    else statusColor = QColor(231, 76, 60);

    painter.setPen(statusColor);
    QFont statusFont("Arial", 11, QFont::Bold);
    painter.setFont(statusFont);
    painter.drawText(250, yPos, report.status);
    yPos += lineHeight;

    // Components
    painter.setPen(Qt::black);
    painter.setFont(labelFont);
    painter.drawText(0, yPos, "Componentes:");
    painter.setFont(valueFont);
    QString componentsText = report.componentsComplete ? "Completos" : "Faltantes";
    QColor compColor = report.componentsComplete ? QColor(39, 174, 96) : QColor(231, 76, 60);
    painter.setPen(compColor);
    painter.setFont(statusFont);
    painter.drawText(250, yPos, componentsText);
    yPos += lineHeight + sectionSpacing;

    drawSeparator();

    // Health Percentage Section
    QFont healthTitleFont("Arial", 18, QFont::Bold);
    drawText("CONDICIÓN GENERAL", healthTitleFont, QColor(52, 152, 219));
    yPos += 30;

    // Draw health bar
    int barWidth = pageWidth - 200;
    int barHeight = 50;
    int barX = 100;

    // Background
    painter.setPen(QPen(Qt::gray, 2));
    painter.setBrush(QColor(236, 240, 241));
    painter.drawRect(barX, yPos, barWidth, barHeight);

    // Health bar fill
    QColor healthColor;
    if (report.healthPercent >= 80) healthColor = QColor(39, 174, 96);
    else if (report.healthPercent >= 60) healthColor = QColor(243, 156, 18);
    else if (report.healthPercent >= 40) healthColor = QColor(230, 126, 34);
    else healthColor = QColor(231, 76, 60);

    painter.setPen(Qt::NoPen);
    painter.setBrush(healthColor);
    int fillWidth = (barWidth * report.healthPercent) / 100;
    painter.drawRect(barX, yPos, fillWidth, barHeight);

    // Percentage text
    QFont percentFont("Arial", 20, QFont::Bold);
    painter.setPen(Qt::white);
    painter.setFont(percentFont);
    QString percentText = QString("%1%").arg(report.healthPercent);
    painter.drawText(QRect(barX, yPos, barWidth, barHeight), Qt::AlignCenter, percentText);

    yPos += barHeight + sectionSpacing;

    drawSeparator();

    // Observations Section
    drawText("OBSERVACIONES TÉCNICAS", sectionFont, QColor(52, 152, 219));
    yPos += 30;

    // Draw observations in a box
    QRect obsRect(0, yPos, pageWidth, 0);
    painter.setPen(QPen(QColor(189, 195, 199), 2));
    painter.setBrush(QColor(250, 250, 250));

    // Calculate observations height
    QFont obsFont("Arial", 10);
    painter.setFont(obsFont);
    QRect textBoundingRect = painter.boundingRect(
        QRect(10, yPos + 10, pageWidth - 20, 2000),
        Qt::AlignLeft | Qt::TextWordWrap,
        report.observations.isEmpty() ? "Sin observaciones registradas." : report.observations
    );

    int obsBoxHeight = textBoundingRect.height() + 40;
    painter.drawRect(0, yPos, pageWidth, obsBoxHeight);

    // Draw observations text
    painter.setPen(Qt::black);
    painter.drawText(
        QRect(20, yPos + 20, pageWidth - 40, obsBoxHeight - 40),
        Qt::AlignLeft | Qt::TextWordWrap,
        report.observations.isEmpty() ? "Sin observaciones registradas." : report.observations
    );

    yPos += obsBoxHeight + sectionSpacing;

    // Footer
    yPos = printer.pageRect(QPrinter::DevicePixel).height() - 100;
    painter.setPen(QPen(QColor(189, 195, 199), 2));
    painter.drawLine(0, yPos, pageWidth, yPos);

    yPos += 30;
    QFont footerFont("Arial", 9);
    footerFont.setItalic(true);
    painter.setFont(footerFont);
    painter.setPen(QColor(127, 140, 141));
    painter.drawText(0, yPos, "Sistema de Mantenimiento de Satélites v1.0");
    painter.drawText(pageWidth - 400, yPos, "Documento generado automáticamente");

    painter.end();
}
