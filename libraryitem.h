#ifndef LIBRARYITEM_H
#define LIBRARYITEM_H

#include <QString>

class LibraryItem {
protected:
    QString title;
    QString author;
    int id;
    bool isBorrowed;

public:
    LibraryItem(const QString& title, const QString& author, int id);
    virtual ~LibraryItem() = default;

    // Getters
    QString getTitle() const;
    QString getAuthor() const;
    int getId() const;
    bool getIsBorrowed() const;

    // Setters
    void setTitle(const QString& title);
    void setAuthor(const QString& author);
    void setId(int id);
    void setIsBorrowed(bool borrowed);

    // Virtual function to display item information
    virtual QString displayInfo() const = 0;
};

#endif // LIBRARYITEM_H
