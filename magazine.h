// magazine.h
#ifndef MAGAZINE_H
#define MAGAZINE_H

#include "libraryitem.h"
#include <QString>

class Magazine : public LibraryItem {
private:
    int issueNumber;
    QString publisher;

public:
    // Constructor
    Magazine(const QString& title, const QString& author, int id,
             int issueNumber, const QString& publisher);

    // Getters
    int getIssueNumber() const;
    QString getPublisher() const;

    // Setters
    void setIssueNumber(int number);
    void setPublisher(const QString& publisher);

    // Overridden virtual function from LibraryItem
    QString displayInfo() const override;
};

#endif // MAGAZINE_H
