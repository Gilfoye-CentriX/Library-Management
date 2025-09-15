#ifndef LIBRARYSTORAGE_H
#define LIBRARYSTORAGE_H

#include <QList>
#include <QSharedPointer>
#include "libraryitem.h"

class LibraryStorage {
private:
    QList<QSharedPointer<LibraryItem>> items;

public:
    void addItem(QSharedPointer<LibraryItem> item);
    bool removeItem(int id);
    QSharedPointer<LibraryItem> findItem(int id) const;
    QList<QSharedPointer<LibraryItem>> getAllItems() const;
    QList<QSharedPointer<LibraryItem>> searchByTitle(const QString& title) const;
    QList<QSharedPointer<LibraryItem>> searchByAuthor(const QString& author) const;
    void sortByTitle();
    void sortById();
};

#endif // LIBRARYSTORAGE_H
