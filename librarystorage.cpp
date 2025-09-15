#include "librarystorage.h"
#include <algorithm>

void LibraryStorage::addItem(QSharedPointer<LibraryItem> item) {
    items.append(item);
}

bool LibraryStorage::removeItem(int id) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if ((*it)->getId() == id) {
            items.erase(it);
            return true;
        }
    }
    return false;
}

QSharedPointer<LibraryItem> LibraryStorage::findItem(int id) const {
    for (const auto& item : items) {
        if (item->getId() == id) {
            return item;
        }
    }
    return QSharedPointer<LibraryItem>(nullptr);
}

QList<QSharedPointer<LibraryItem>> LibraryStorage::getAllItems() const {
    return items;
}

QList<QSharedPointer<LibraryItem>> LibraryStorage::searchByTitle(const QString& title) const {
    QList<QSharedPointer<LibraryItem>> result;
    for (const auto& item : items) {
        if (item->getTitle().contains(title, Qt::CaseInsensitive)) {
            result.append(item);
        }
    }
    return result;
}

QList<QSharedPointer<LibraryItem>> LibraryStorage::searchByAuthor(const QString& author) const {
    QList<QSharedPointer<LibraryItem>> result;
    for (const auto& item : items) {
        if (item->getAuthor().contains(author, Qt::CaseInsensitive)) {
            result.append(item);
        }
    }
    return result;
}

void LibraryStorage::sortByTitle() {
    std::sort(items.begin(), items.end(),
        [](const QSharedPointer<LibraryItem>& a, const QSharedPointer<LibraryItem>& b) {
            return a->getTitle().compare(b->getTitle(), Qt::CaseInsensitive) < 0;
        });
}

void LibraryStorage::sortById() {
    std::sort(items.begin(), items.end(),
        [](const QSharedPointer<LibraryItem>& a, const QSharedPointer<LibraryItem>& b) {
            return a->getId() < b->getId();
        });
}
