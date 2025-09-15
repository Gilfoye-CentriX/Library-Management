#include "mainwindow.h"
#include "book.h"
#include "magazine.h"
#include "LibraryUtils/libraryutils.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QIntValidator>
#include <QFile>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Central widget
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Layouts
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    QHBoxLayout *topLayout = new QHBoxLayout();
    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    QHBoxLayout *filterSortLayout = new QHBoxLayout();

    // Inputs
    titleLineEdit = new QLineEdit(); titleLineEdit->setPlaceholderText("Title");
    authorLineEdit = new QLineEdit(); authorLineEdit->setPlaceholderText("Author");
    idSpinBox = new QSpinBox(); idSpinBox->setPrefix("ID ");
    genreLineEdit = new QLineEdit(); genreLineEdit->setPlaceholderText("Genre");
    yearLineEdit = new QLineEdit(); yearLineEdit->setPlaceholderText("Year");
    yearLineEdit->setValidator(new QIntValidator(1900, 2100, this));
    publisherLineEdit = new QLineEdit(); publisherLineEdit->setPlaceholderText("Publisher");

    topLayout->addWidget(titleLineEdit);
    topLayout->addWidget(authorLineEdit);
    topLayout->addWidget(idSpinBox);
    topLayout->addWidget(genreLineEdit);
    topLayout->addWidget(yearLineEdit);
    topLayout->addWidget(publisherLineEdit);

    // Buttons
    addBookButton = new QPushButton("Add Book");
    addMagazineButton = new QPushButton("Add Magazine");
    searchButton = new QPushButton("Search");
    searchLineEdit = new QLineEdit(); searchLineEdit->setPlaceholderText("Search...");
    borrowButton = new QPushButton("Borrow");
    returnButton = new QPushButton("Return");
    importButton = new QPushButton("Import", this);
    exportButton = new QPushButton("Export", this);
    saveButton = new QPushButton("Save", this);

    buttonsLayout->addWidget(addBookButton);
    buttonsLayout->addWidget(addMagazineButton);
    buttonsLayout->addWidget(searchButton);
    buttonsLayout->addWidget(searchLineEdit);
    buttonsLayout->addWidget(borrowButton);
    buttonsLayout->addWidget(returnButton);
    buttonsLayout->addWidget(importButton);
    buttonsLayout->addWidget(exportButton);
    buttonsLayout->addWidget(saveButton);

    // Filter and sort
    filterComboBox = new QComboBox();
    filterComboBox->addItems({"All Items", "Books Only", "Magazines Only", "Available Only", "Borrowed Only"});
    sortComboBox = new QComboBox();
    sortComboBox->addItems({"By Title", "By ID"});
    filterSortLayout->addWidget(filterComboBox);
    filterSortLayout->addWidget(sortComboBox);

    // List and status
    listWidget = new QListWidget();
    statusLabel = new QLabel("Status");

    // Add layouts to main
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(buttonsLayout);
    mainLayout->addLayout(filterSortLayout);
    mainLayout->addWidget(listWidget);
    mainLayout->addWidget(statusLabel);

    // Connect signals
    connect(addBookButton, &QPushButton::clicked, this, &MainWindow::handleAddBook);
    connect(addMagazineButton, &QPushButton::clicked, this, &MainWindow::handleAddMagazine);
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::handleSearch);
    connect(borrowButton, &QPushButton::clicked, this, &MainWindow::handleBorrow);
    connect(returnButton, &QPushButton::clicked, this, &MainWindow::handleReturn);
    connect(listWidget, &QListWidget::itemDoubleClicked, this, &MainWindow::handleItemDoubleClicked);
    connect(filterComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleFilterChanged(int)));
    connect(sortComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(handleSortChanged(int)));
    connect(importButton, &QPushButton::clicked, this, &MainWindow::handleImport);
    connect(exportButton, &QPushButton::clicked, this, &MainWindow::handleExport);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::saveData);
    connect(saveButton, &QPushButton::clicked, this, &MainWindow::handleManualSave);


    // Load data
    if (!QFile::exists(dataFile)) {
        createDefaultDataset();
        saveData();
    } else {
        loadData();
    }
    updateItemList();
}

MainWindow::~MainWindow() {
    saveData();
}

// Implementation

void MainWindow::createDefaultDataset() {
    auto book1 = QSharedPointer<Book>::create("Introduction to Design Patterns in C++ with Qt", "Alan Ezust & Paul Ezust", 1, "Programming", 2011);
    auto mag1 = QSharedPointer<Magazine>::create("Physics and Reality", "Albert Einstein (Translation by Jean Piccard)", 2, 140, "Philosophy");
    storage.addItem(book1);
    storage.addItem(mag1);
}

void MainWindow::loadData() {
    auto items = LibraryUtils::loadFromFile(dataFile);
    storage = LibraryStorage();  // reset storage
    for (const auto& item : items) storage.addItem(item);
}

void MainWindow::saveData() {
    LibraryUtils::saveToFile(dataFile, storage.getAllItems());
}

void MainWindow::handleManualSave() {
    if (LibraryUtils::saveToFile(dataFile, storage.getAllItems())) {
            QMessageBox::information(this, "Saved", "Library data has been saved successfully.");
        } else {
            QMessageBox::critical(this, "Error", "Failed to save library data.");
        }
}

void MainWindow::updateItemList() {
    listWidget->clear();

    auto items = storage.getAllItems();

    // Apply filters
    QString filter = filterComboBox->currentText();
    if (filter == "Books Only") {
        items = LibraryUtils::filterByType(items, "Book");
    } else if (filter == "Magazines Only") {
        items = LibraryUtils::filterByType(items, "Magazine");
    } else if (filter == "Available Only") {
        items.erase(std::remove_if(items.begin(), items.end(),
                                  [](const QSharedPointer<LibraryItem>& item){ return item->getIsBorrowed(); }),
                    items.end());
    } else if (filter == "Borrowed Only") {
        items.erase(std::remove_if(items.begin(), items.end(),
                                  [](const QSharedPointer<LibraryItem>& item){ return !item->getIsBorrowed(); }),
                    items.end());
    }
    // Apply sorting
    QString sort = sortComboBox->currentText();
    if (sort == "By Title") {
        LibraryUtils::sortItemsByTitle(items);
    } else if (sort == "By ID") {
        LibraryUtils::sortItemsById(items);
    }

    // Populate the list widget
    for (const auto& item : items) {
        QListWidgetItem *listItem = new QListWidgetItem(listWidget);
        QString status = item->getIsBorrowed() ? "[Borrowed]" : "[Available]";
        listItem->setText(QString("%1 %2 - %3").arg(status, item->getTitle(), item->getAuthor()));
        listItem->setData(Qt::UserRole, item->getId());

        listItem->setForeground(item->getIsBorrowed() ? Qt::red : Qt::darkGreen);
    }
    statusLabel->setText(QString("Total Items: %1").arg(items.size()));
}

void MainWindow::clearInputFields() {
    titleLineEdit->clear();
    authorLineEdit->clear();
    idSpinBox->setValue(0);
    genreLineEdit->clear();
    yearLineEdit->clear();
    publisherLineEdit->clear();
}

void MainWindow::showItemDetails(QSharedPointer<LibraryItem> item) {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Item Details");
    msgBox.setText(item->displayInfo());
    msgBox.exec();
}

void MainWindow::handleAddBook() {
    QString title = titleLineEdit->text().trimmed();
    QString author = authorLineEdit->text().trimmed();
    int id = idSpinBox->value();
    QString genre = genreLineEdit->text().trimmed();

    int year = yearLineEdit->text().toInt();

    if (title.isEmpty() || author.isEmpty()) {
        QMessageBox::warning(this, "Error", "Title and author cannot be empty!");
        return;
    }

    if (storage.findItem(id)) {
        QMessageBox::warning(this, "Error", "ID already exists!");
        return;
    }

    auto book = QSharedPointer<Book>::create(title, author, id, genre, year);
    storage.addItem(book);
    updateItemList();
    clearInputFields();
    QMessageBox::information(this, "Success", "Book added successfully!");
}

void MainWindow::handleAddMagazine() {
    QString title = titleLineEdit->text().trimmed();
    QString author = authorLineEdit->text().trimmed();
    int id = idSpinBox->value();
    int issue = yearLineEdit->text().toInt();
    QString publisher = publisherLineEdit->text().trimmed();

    if (title.isEmpty() || author.isEmpty()) {
        QMessageBox::warning(this, "Error", "Title and author cannot be empty!");
        return;
    }

    if (storage.findItem(id)) {
        QMessageBox::warning(this, "Error", "ID already exists!");
        return;
    }

    auto magazine = QSharedPointer<Magazine>::create(title, author, id, issue, publisher);
    storage.addItem(magazine);
    updateItemList();
    clearInputFields();
    QMessageBox::information(this, "Success", "Magazine added successfully!");
}

void MainWindow::handleSearch() {
    QString searchText = searchLineEdit->text().trimmed();
    if (searchText.isEmpty()) {
        updateItemList();
        return;
    }

    listWidget->clear();

    // Search by title and author
    auto resultsTitle = storage.searchByTitle(searchText);
    auto resultsAuthor = storage.searchByAuthor(searchText);

    // Combine results and remove duplicates
    QList<QSharedPointer<LibraryItem>> results = resultsTitle;
    for (const auto& item : resultsAuthor) {
        if (!results.contains(item)) {
            results.append(item);
        }
    }

    for (const auto& item : results) {
        QListWidgetItem *listItem = new QListWidgetItem(listWidget);
        QString status = item->getIsBorrowed() ? "[Borrowed]" : "[Available]";
        listItem->setText(QString("%1 %2 - %3").arg(status, item->getTitle(), item->getAuthor()));
        listItem->setData(Qt::UserRole, item->getId());
        listItem->setForeground(item->getIsBorrowed() ? Qt::red : Qt::darkGreen);
    }

    statusLabel->setText(QString("Search Results: %1").arg(results.size()));
}

void MainWindow::handleBorrow() {
    auto selectedItems = listWidget->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select an item to borrow!");
        return;
    }
    int id = selectedItems.first()->data(Qt::UserRole).toInt();
    auto item = storage.findItem(id);
    if (item) {
        if (item->getIsBorrowed()) {
            QMessageBox::warning(this, "Error", "This item is already borrowed!");
            return;
        }
        item->setIsBorrowed(true);
        updateItemList();
        QMessageBox::information(this, "Success", "Item borrowed successfully!");
    }
}

void MainWindow::handleReturn() {
    auto selectedItems = listWidget->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please select an item to return!");
        return;
    }
    int id = selectedItems.first()->data(Qt::UserRole).toInt();
    auto item = storage.findItem(id);
    if (item) {
        if (!item->getIsBorrowed()) {
            QMessageBox::warning(this, "Error", "This item is not currently borrowed!");
            return;
        }
        item->setIsBorrowed(false);
        updateItemList();
        QMessageBox::information(this, "Success", "Item returned successfully!");
    }
}

void MainWindow::handleItemDoubleClicked(QListWidgetItem *item) {
    int id = item->data(Qt::UserRole).toInt();
    auto libraryItem = storage.findItem(id);
    if (libraryItem) {
        showItemDetails(libraryItem);
    }
}

void MainWindow::handleFilterChanged(int index) {
    Q_UNUSED(index);
    updateItemList();
}

void MainWindow::handleSortChanged(int index) {
    Q_UNUSED(index);
    updateItemList();
}

void MainWindow::handleExport() {
    QString fileName = QFileDialog::getSaveFileName(this, "Export Library Data", "", "Data Files (*.txt)");
    if (!fileName.isEmpty()) {
        if (LibraryUtils::saveToFile(fileName, storage.getAllItems())) {
            QMessageBox::information(this, "Success", "Data exported successfully!");
        } else {
            QMessageBox::critical(this, "Error", "Failed to export data!");
        }
    }
}

void MainWindow::handleImport() {
    QString fileName = QFileDialog::getOpenFileName(this, "Import Library Data", "", "Data Files (*.txt)");
    if (!fileName.isEmpty()) {
        auto items = LibraryUtils::loadFromFile(fileName);
        if (!items.isEmpty()) {
            storage = LibraryStorage();
            for (const auto& item : items) {
                storage.addItem(item);
            }
            updateItemList();
            QMessageBox::information(this, "Success", QString("Imported %1 items").arg(items.size()));
        } else {
            QMessageBox::critical(this, "Error", "Failed to import data or file was empty!");
        }
    }
}

