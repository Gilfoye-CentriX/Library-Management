#include "libraryitem.h"

LibraryItem::LibraryItem(const QString& title, const QString& author, int id)
    : title(title), author(author), id(id), isBorrowed(false) {}

// Getters
QString LibraryItem::getTitle() const { return title; }
QString LibraryItem::getAuthor() const { return author; }
int LibraryItem::getId() const { return id; }
bool LibraryItem::getIsBorrowed() const { return isBorrowed; }

// Setters
void LibraryItem::setTitle(const QString& title) { this->title = title; }
void LibraryItem::setAuthor(const QString& author) { this->author = author; }
void LibraryItem::setId(int id) { this->id = id; }
void LibraryItem::setIsBorrowed(bool borrowed) { isBorrowed = borrowed; }
