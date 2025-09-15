#include "book.h"
#include <QStringList>

Book::Book(const QString& title, const QString& author, int id,
           const QString& genre, int publicationYear)
    : LibraryItem(title, author, id), genre(genre), publicationYear(publicationYear) {}

QString Book::getGenre() const { return genre; }
int Book::getPublicationYear() const { return publicationYear; }

void Book::setGenre(const QString& genre) { this->genre = genre; }
void Book::setPublicationYear(int year) { publicationYear = year; }

QString Book::displayInfo() const {
    QStringList info;
    info << QString("Book ID: %1").arg(getId());
    info << QString("Title: %1").arg(getTitle());
    info << QString("Author: %1").arg(getAuthor());
    info << QString("Genre: %1").arg(genre);
    info << QString("Year: %1").arg(publicationYear);
    info << QString("Status: %1").arg(getIsBorrowed() ? "Borrowed" : "Available");
    return info.join("\n");
}
