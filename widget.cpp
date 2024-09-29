#include "widget.h"


// 检查字符是否为加、减、乘、除符号。
bool Widget::isOperator(const QString& token)
{
    return (token == "+" || token == "-"  || token == "*" ||
            token == "/" || token == "%"  || token == "^" || token == "√" ||
            token == "." || token == "<<" || token == ">>");
}
// 获取运算符的优先级.
int Widget::getPrecedence(const QString& op)
{
    if (op == "+" || op == "-")
        return 1;
    else if (op == "*" || op == "/"|| op == "%")
        return 2;
    else if (op == "^" || op == "√")
        return 3;
    else if (op == ".")
        return 4;
    else if (op == "<<" || op == ">>")
        return 5;
    return 0;
}

// 将中缀表达式转换为后缀表达式。
QStringList Widget::convertToPostfix(QString& infix)
{
    QStringList postfix;                    // 存储后缀表达式的列表
    QStack<QString> stack;                  // 运算符栈
    QStringList tokens = infix.split(' ', Qt::SkipEmptyParts);
    for (const QString& token : tokens)
    {
        if (token == "(")                    // 如果是左括号，则将其压入栈中
            stack.push(token);
        else if (token == ")")
        {   // 如果是右括号，则将栈中的运算符依次弹出直到遇到左括号为止，并将弹出的运算符添加到后缀表达式列表中
            while (!stack.isEmpty() && stack.top() != "(")
                postfix.append(stack.pop());
            if (!stack.isEmpty() && stack.top() == "(")  // 弹出左括号
                stack.pop();

        }
        else if (isOperator(token))    // 如果是运算符
        {
            // 当栈顶元素的优先级大于等于当前运算符的优先级时，将栈顶运算符弹出并添加到后缀表达式列表中
            while (!stack.isEmpty() && getPrecedence(token) <= getPrecedence(stack.top()))
                postfix.append(stack.pop());
            stack.push(token);         // 将当前运算符压入栈中
        }
        else                           // 如果是操作数，则直接添加到后缀表达式列表中
            postfix.append(token);
    }

    while (!stack.isEmpty())          // 将剩余的运算符依次弹出并添加到后缀表达式列表中
        postfix.append(stack.pop());
    return postfix;                   // 返回后缀表达式列表
}

//计算后缀表达式的值。
double Widget::evaluatePostfix(QStringList expression) {
    QStack<double> stack;
    qDebug() << expression;
    foreach (QString token, expression)
    {
        if (token.toDouble())           //如果它可以转换为double类型（即操作数），就将其压入栈中
            stack.push(token.toDouble());

        else
        {
            double operand2 = stack.pop();
            if (token == "^")
            {
                stack.push(operand2*operand2);
                continue;
            }
            if (token == "√")
            {
                stack.push(sqrt(operand2));
                continue;
            }
            double operand1 = stack.pop();
            if (token == "+")
                stack.push(operand1 + operand2);
            else if (token == "-")
                stack.push(operand1 - operand2);
            else if (token == "*")
                stack.push(operand1 * operand2);
            else if (token == "/")
                stack.push(operand1 / operand2);
            else if (token == "%")
                stack.push(operand1 - static_cast<int>(operand1 / operand2) * operand2);
//              stack.push(fmod(operand1, operand2));

            else if (token == "<<")
                stack.push(static_cast<int>(operand1) << static_cast<int>(operand2));
            else if (token == ">>")
                stack.push(static_cast<int>(operand1) >> static_cast<int>(operand2));
            else if (token == ".")
            {
                QString result = QString::number(operand1) + "." + QString::number(operand2);
                stack.push(result.toDouble());
            }
        }
    }

    return stack.pop();
}


Widget::Widget(QWidget *parent): QWidget(parent)
{
    this->resize(600, 800);
    layout = new QVBoxLayout(this);
    frame = new QFrame(this);
    label = new QLabel(this);
    label->setStyleSheet("border: 1px solid black;");
    QFont font;
    font.setPointSize(20);            // 设置字体大小为 12
    label->setFont(font);

    layout->addWidget(label, 1);
    layout->addWidget(frame, 2);

    layout2 = new QGridLayout(frame); // 将layout2作为frame的布局管理器
    int i = 0;
    QStringList list;
    list << "AC" << "回退" << "%" << "/" << "^" << "7" << "8" << "9"
         << "*" << "√" << "4" << "5" << "6" << "-" << "<<"<< "1" << "2" << "3"
         << "+" << ">>"<< "(" << "0" << "." << "=" << ")";

    // 遍历每个按钮的行和列
    for (int row = 0; row < 5; row++)
    {
        for (int col = 0; col < 5; col++)
        {

            button[row][col] = new QPushButton(frame);      // 创建一个新的按钮
            button[row][col]->setFont(font);
            button[row][col]->setText(list[i++]);
            button[row][col]->setFixedSize(100, 100);
            layout2->addWidget(button[row][col], row, col); // 将按钮添加到布局中，并为按钮添加点击事件的连接器

            connect(button[row][col], &QPushButton::clicked, [=]() {
                // 获取当前标签的文本内容并存储在 text 变量中，同时获取当前按钮的文本内容
                this->text = label->text();
                QString buttonText = button[row][col]->text();

                // 如果当前文本不为空，则判断是否需要在新字符前添加空格
                if (!this->text.isEmpty())
                {
                    QChar lastChar = this->text.right(1)[0];
                    bool lastIsDigit = lastChar.isDigit();
                    bool currIsDigit = buttonText.at(0).isDigit();
                    if ((lastIsDigit && !currIsDigit) || (!lastIsDigit && currIsDigit)||
                        (!lastIsDigit && !currIsDigit))
                          text.append(" ");
                }

                // 将当前按钮的文本内容添加到 text 变量中，并更新标签的文本内容
                text.append(buttonText);
                label->setText(text);
            });
        }
    }
    connect(button[0][0], &QPushButton::clicked, [=](){
        this->text.clear();
        label->setText("");

    });
    connect(button[4][3], &QPushButton::clicked, [=](){
        this->text.chop(1);
        double result = evaluatePostfix(convertToPostfix(this->text));
        this->text += "= " + QString::number(result);
        label->setText(this->text);
    });
    button[0][1]->setEnabled(false);
}

Widget::~Widget()
{

}
