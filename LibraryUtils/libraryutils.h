#ifndef LIBRARYUTILS_H
#define LIBRARYUTILS_H

#include <QString>
#include <QList>
#include <QSharedPointer>
#include "..\libraryitem.h"
#include "..\book.h"
#include "..\magazine.h"

class LibraryUtils {
public:
    static bool saveToFile(const QString& filename, const QList<QSharedPointer<LibraryItem>>& items);
    static QList<QSharedPointer<LibraryItem>> loadFromFile(const QString& filename);
    static void sortItemsByTitle(QList<QSharedPointer<LibraryItem>>& items);
    static void sortItemsById(QList<QSharedPointer<LibraryItem>>& items);
    static QList<QSharedPointer<LibraryItem>> filterByType(
        const QList<QSharedPointer<LibraryItem>>& items, const QString& type);
};

#endif // LIBRARYUTILS_H
