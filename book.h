#ifndef BOOK_H
#define BOOK_H

#include "libraryitem.h"

class Book : public LibraryItem {
private:
    QString genre;
    int publicationYear;

public:
    Book(const QString& title, const QString& author, int id,
         const QString& genre, int publicationYear);

    QString getGenre() const;
    int getPublicationYear() const;

    void setGenre(const QString& genre);
    void setPublicationYear(int year);

    QString displayInfo() const override;
};

#endif // BOOK_H
