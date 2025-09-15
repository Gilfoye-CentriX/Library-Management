#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QListWidget>
#include <QComboBox>
#include <QLabel>
#include <QSharedPointer>
#include "librarystorage.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleAddBook();
    void handleAddMagazine();
    void handleSearch();
    void handleBorrow();
    void handleReturn();
    void handleItemDoubleClicked(QListWidgetItem *item);
    void handleFilterChanged(int index);
    void handleSortChanged(int index);
    void handleExport();
    void handleImport();
    void handleManualSave();

private:
    // GUI widgets
    QWidget *centralWidget;
    QLineEdit *titleLineEdit;
    QLineEdit *authorLineEdit;
    QSpinBox *idSpinBox;
    QLineEdit *genreLineEdit;
    QLineEdit *yearLineEdit;
    QLineEdit *publisherLineEdit;
    QPushButton *addBookButton;
    QPushButton *addMagazineButton;
    QPushButton *searchButton;
    QPushButton *borrowButton;
    QPushButton *returnButton;
    QPushButton *importButton;
    QPushButton *exportButton;
    QPushButton *saveButton;
    QLineEdit *searchLineEdit;
    QComboBox *filterComboBox;
    QComboBox *sortComboBox;
    QListWidget *listWidget;
    QLabel *statusLabel;

    LibraryStorage storage;
    QString dataFile = "library_data.txt";

    void loadData();
    void saveData();
    void updateItemList();
    void clearInputFields();
    void showItemDetails(QSharedPointer<LibraryItem> item);
    void createDefaultDataset();
};

#endif // MAINWINDOW_H
