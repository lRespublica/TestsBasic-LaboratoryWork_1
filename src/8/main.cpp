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
        if(word->simplified().length() > 1)
        {
            std::reverse(word->begin(), word->end());
        }
        std::cout << word->toStdString();
    }
    std::cout << std::endl;
    return 0;
}
