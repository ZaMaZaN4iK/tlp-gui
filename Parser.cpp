#include "Parser.h"
#include "Contstants.h"
#include <QTextStream>
#include <QDebug>

Parser::Parser(QFile& file)
{
    QTextStream input(&file);
    QFile outf("/home/zamazan4ik/azaza.txt");
    outf.open(QIODevice::WriteOnly);
    QTextStream out(&outf);
    QString str;
    while(input.readLineInto(&str))
    {
        for(const auto& x : NamesOfProp)
        {
            if(str.contains(x))
            {
                QString value;
                int posEqual = str.indexOf('=');
                value = str.mid(posEqual + 1).trimmed();
                prop.insert(x, value);
                break;
            }
        }
    }
    outf.close();
}

QVector<QPair<QString, QVariant> > Parser::getVector() const
{
    QVector<QPair<QString, QVariant> > result;
    for(const auto& x : NamesOfProp)
    {
        result << QPair<QString, QVariant>(x, prop[x]);
    }
    return result;
}

