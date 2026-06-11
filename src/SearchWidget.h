#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QStringList>

class SearchWidget : public QWidget {
    Q_OBJECT

public:
    explicit SearchWidget(QWidget *parent = nullptr);

signals:
    void observationSelected(const QString &observation);

private slots:
    void onSearchTextChanged(const QString &text);
    void onItemClicked(QListWidgetItem *item);
    void onAddButtonClicked();

private:
    void setupUI();
    void loadCommonObservations();
    void filterObservations(const QString &filter);

    QLineEdit *searchEdit;
    QListWidget *observationsList;
    QPushButton *addButton;

    QStringList allObservations;
};

#endif // SEARCHWIDGET_H
