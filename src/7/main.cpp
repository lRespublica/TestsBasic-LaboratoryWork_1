#include<iostream>
#include<cstdlib>
#include<string>
#include<time.h>
#include<QImage>
#include<QPainter>
#include<QRectF>
#include<QString>
#include<QGuiApplication>
#include<QTimer>

using namespace std;

void generateAmount(uint64_t * amountOf, uint64_t size, int64_t length)
{
    int64_t amountSize = 0;
    for(int i = 0; i < size; i++)
    {
        if(amountSize >= length)
        {
            amountSize = 0;
            break;
        }
        amountOf[i] = rand() % (length - amountSize) + 1;
        amountSize += amountOf[i];
    }

    if(amountSize != length)
        generateAmount(amountOf, size, length);
}

//! Копировать значения одного массива в другой
//! \warning Предполагается то, что на новый массив уже выделена память, не меньше чем на оригинальный
void copyArray(uint64_t * originalArr, uint64_t * newArray, uint64_t size)
{
    for(int i = 0; i < size; i++)
    {
        newArray[i] = originalArr[i];
    }
}

char generateSpecialSymbol(uint64_t number)
{
    string symbols = {
      '!', '#', '%', ':', ',', '.', ';', '*', '(', ')', '[', ']', '{', '}', '<', '>', '/', '?', '@', '&', '-', '+', '='
    };

    return symbols.at(number % symbols.size());
}

// 0 - Lowercase;
// 1 - Uppercase;
// 2 - Nums;
// 3 - Special symbols
char generateSymbol(uint64_t type)
{
    if(type == 0)
        // From a to z
        return (rand() % 26) + 97;
    else if(type == 1)
        // From A to Z
        return (rand() % 26) + 65;
    else if(type == 2)
        // from 0 to 9
        return (rand() % 10) + 48;
    else
        return generateSpecialSymbol(rand());
}

int main(int argc, char * argv[])
{
    srand(time(0));

    int64_t length;

    cin >> length;
    if (cin.fail())
    {
        cerr << "Error. Input is not integer number. Please, try again" << endl;
        return 1;
    }

    if (length <= 0)
    {
        cerr << "Error. Numbers cannot be less or equal to 0!" << endl;
        return 1;
    }

    string textString;
    textString.reserve(length);

    // 0 - Lowercase;
    // 1 - Uppercase;
    // 2 - Nums;
    // 3 - Special symbols
    uint64_t amountOf[4];
    uint64_t amountOfReduced[4];

    generateAmount(amountOf, 4, length);
    copyArray(amountOf, amountOfReduced, 4);

    for(int i = 0; i < length; i++)
    {
        uint64_t type = rand() % 4;
        if(amountOfReduced[type] != 0)
        {
            textString += generateSymbol(type);
            amountOfReduced[type]--;
        }
        else
        {
            i--;
        }
    }

    for(int i = 86; i < textString.length(); i+= 86)
        textString.insert(i, "\n");                 // To fit text into an image

    QGuiApplication a(argc, argv);

    QImage textImage(QSize(720, 360), QImage::Format_RGB32);
    QPainter painter(&textImage);
    for(int i = 0; i < textImage.size().width(); i += 2)
    {
        for(int j = 0; j < textImage.height(); j += 2)
        {
            if(rand() % 2 == 1)
            {
                painter.setBrush(Qt::green);
            }
            else
            {
                painter.setBrush(Qt::white);
            }
            painter.fillRect(QRect(i, j, 5, 5), painter.brush());
        }
    }
    painter.setPen(QPen(Qt::yellow, 0.75));
    painter.drawLine(0, 360, 720, 0);
    painter.setPen(Qt::red);
    painter.drawText(QRect(10, 10, 700, 310), Qt::TextWordWrap, QString::fromStdString(textString));

    if(textImage.save("textImage.jpg") == false)
    {
        cerr << "Error. Cannot save file" << endl;
        return 1;
    }

    QTimer::singleShot(0, QCoreApplication::instance(), SLOT(quit()));

    return a.exec();
}
