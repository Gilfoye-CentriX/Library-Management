#include "magazine.h"
#include <QStringList>

Magazine::Magazine(const QString& title, const QString& author, int id,
                   int issueNumber, const QString& publisher)
    : LibraryItem(title, author, id), issueNumber(issueNumber), publisher(publisher) {}

int Magazine::getIssueNumber() const { return issueNumber; }
QString Magazine::getPublisher() const { return publisher; }

void Magazine::setIssueNumber(int number) { issueNumber = number; }
void Magazine::setPublisher(const QString& publisher) { this->publisher = publisher; }

QString Magazine::displayInfo() const {
    QStringList info;
    info << QString("Magazine ID: %1").arg(getId());
    info << QString("Title: %1").arg(getTitle());
    info << QString("Author: %1").arg(getAuthor());
    info << QString("Issue #: %1").arg(issueNumber);
    info << QString("Publisher: %1").arg(publisher);
    info << QString("Status: %1").arg(getIsBorrowed() ? "Borrowed" : "Available");
    return info.join("\n");
}
