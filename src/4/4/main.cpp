#include <iostream>
#include <string>
#include <QString>
#include <QRegularExpression>

int main()
{
    std::string tmpString;
    std::getline(std::cin, tmpString);
    QString string(tmpString.c_str());
    auto words = string.split(QRegularExpression("\\b", QRegularExpression::UseUnicodePropertiesOption));
    for(auto word = words.begin() + 1; word != words.end(); word++)
    {
        if(word->size() % 2 == 1 and word->simplified().length() > 1)
        {
            word->remove(word->size()/2, 1);
        }
        else if (word->size() % 2 == 0 and word->simplified().length() > 1)
        {
            word->insert(word->size()/2, QChar(int(word->at(0).unicode()) + 1));
        }
        std::cout << word->toStdString();
    }
    std::cout << std::endl;
    return 0;
}
