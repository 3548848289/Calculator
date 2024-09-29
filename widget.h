#ifndef WIDGET_H
#define WIDGET_H
#include "main.h"
#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    QStringList convertToPostfix(QString& infix);
    double evaluatePostfix(QStringList expression);
    bool isOperator(const QString& token);
    int getPrecedence(const QString& op);

    QString text;
    QString lab_text;
    QStringList expression;
    QFrame * frame;
    QLabel * label;
    QVBoxLayout * layout;
    QGridLayout * layout2;
    QPushButton * button[5][5];
    ~Widget();
};

#endif // WIDGET_H
