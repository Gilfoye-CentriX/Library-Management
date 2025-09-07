#include "libraryutils.h"
#include "../book.h"
#include "../magazine.h"
#include <QFile>
#include <QTextStream>
#include <QDataStream>
#include <QDebug>
#include <QSharedPointer>
#include <algorithm>

bool LibraryUtils::saveToFile(const QString& filename, const QList<QSharedPointer<LibraryItem>>& items) {
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Could not open file for writing:" << filename;
        return false;
    }

    QDataStream out(&file);
    out << items.size();

    for (const auto& item : items) {
        out << item->getId();
        out << item->getTitle();
        out << item->getAuthor();
        out << item->getIsBorrowed();

        if (auto book = dynamic_cast<Book*>(item.data())) {
            out << QString("Book");
            out << book->getGenre();
            out << book->getPublicationYear();
        }
        else if (auto magazine = dynamic_cast<Magazine*>(item.data())) {
            out << QString("Magazine");
            out << magazine->getIssueNumber();
            out << magazine->getPublisher();
        } else {
            // Unknown type - skip or mark as unknown
            out << QString("Unknown");
        }
    }

    file.close();
    return true;
}

QList<QSharedPointer<LibraryItem>> LibraryUtils::loadFromFile(const QString& filename) {
    QList<QSharedPointer<LibraryItem>> items;
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open file for reading:" << filename;
        return items;
    }

    QDataStream in(&file);
    int count = 0;
    in >> count;

    for (int i = 0; i < count; ++i) {
        int id;
        QString title, author, type;
        bool isBorrowed = false;

        in >> id >> title >> author >> isBorrowed >> type;

        if (type == "Book") {
            QString genre;
            int publicationYear;
            in >> genre >> publicationYear;

            auto book = QSharedPointer<Book>::create(title, author, id, genre, publicationYear);
            book->setIsBorrowed(isBorrowed);
            items.append(book);
        }
        else if (type == "Magazine") {
            int issueNumber;
            QString publisher;
            in >> issueNumber >> publisher;

            auto magazine = QSharedPointer<Magazine>::create(title, author, id, issueNumber, publisher);
            magazine->setIsBorrowed(isBorrowed);
            items.append(magazine);
        } else {
             qWarning() << "Unknown item type found in file:" << type;
        }
    }

    file.close();
    return items;
}

void LibraryUtils::sortItemsByTitle(QList<QSharedPointer<LibraryItem>>& items) {
    std::sort(items.begin(), items.end(),
        [](const QSharedPointer<LibraryItem>& a, const QSharedPointer<LibraryItem>& b) {
            return a->getTitle().compare(b->getTitle(), Qt::CaseInsensitive) < 0;
        });
}

void LibraryUtils::sortItemsById(QList<QSharedPointer<LibraryItem>>& items) {
    std::sort(items.begin(), items.end(),
        [](const QSharedPointer<LibraryItem>& a, const QSharedPointer<LibraryItem>& b) {
            return a->getId() < b->getId();
        });
}

QList<QSharedPointer<LibraryItem>> LibraryUtils::filterByType(
    const QList<QSharedPointer<LibraryItem>>& items, const QString& type)
{
    QList<QSharedPointer<LibraryItem>> result;
    for (const auto& it : items) {
        if (type.compare("Book", Qt::CaseInsensitive) == 0) {
            if (dynamic_cast<Book*>(it.data())) result.append(it);
        } else if (type.compare("Magazine", Qt::CaseInsensitive) == 0) {
            if (dynamic_cast<Magazine*>(it.data())) result.append(it);
        } else if (type.compare("All", Qt::CaseInsensitive) == 0 || type.isEmpty()) {
            result.append(it);
        }
    }
    return result;
}
