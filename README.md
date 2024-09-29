计算器小部件文档
概述
该项目使用 Qt 实现了一个计算器小部件，可以计算中缀表达式并将其转换为后缀表达式进行求值。计算器支持基本算术运算以及一些高级运算，如平方根和位移操作。

特性
中缀到后缀转换：将数学表达式从中缀表示法（例如 3 + 5）转换为后缀表示法（例如 3 5 +）。
后缀表达式求值：对转换后的后缀表达式进行求值，返回数值结果。
用户界面：使用 Qt 构建的简单图形用户界面（GUI），允许用户输入表达式并查看结果。
运算符支持：支持加法、减法、乘法、除法、取模、指数、平方根和位移操作。
需求
Qt 5 或更高版本
C++11 或更高版本
安装
克隆仓库：

bash
复制代码
git clone https://github.com/你的用户名/你的仓库.git
cd 你的仓库
打开项目：在 Qt Creator 中打开项目。

构建项目：使用 Qt Creator 中的构建按钮编译项目。

运行应用程序：构建完成后，运行应用程序以查看计算器。

使用方法
输入表达式：使用计算器上的按钮输入数学表达式。
清除：按 AC 按钮清除当前输入。
退格：使用 回退 按钮删除最后一个字符。
计算：按 = 按钮计算表达式，结果将显示在计算器上。
代码结构
主类：Widget
方法：

isOperator(const QString& token)：检查给定的标记是否为运算符。
getPrecedence(const QString& op)：返回给定运算符的优先级。
convertToPostfix(QString& infix)：将中缀表达式转换为后缀表达式。
evaluatePostfix(QStringList expression)：计算后缀表达式并返回结果。
UI 元素：

QLabel label：显示当前输入和结果。
QPushButton button[5][5]：用于输入的按钮网格。
QVBoxLayout layout：小部件的主布局。
QGridLayout layout2：按钮网格的布局。
示例
输入
要计算 3 + 5 * 2，输入：

复制代码
3  +  5  *  2
输出
输出将显示：

复制代码
= 13
贡献
如果您想为此项目贡献代码，请创建一个拉取请求或打开一个问题进行讨论。

许可证
该项目根据 MIT 许可证发布。有关详细信息，请参阅 LICENSE 文件。
