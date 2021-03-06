#ifndef PARSER_H
#define PARSER_H

#include <QList>
#include <QString>
#include <QVariant>
#include <QMap>
#include <QFile>

class Parser
{
private:
    QMap<QString, QVariant> prop;
public:
    Parser(QFile& file);

    QVector<QPair<QString, QVariant> > getVector() const;

    static bool check();
};

#endif // PARSER_H
