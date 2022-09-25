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
    uint64_t amountOfWords = 0;
    uint64_t amountOfMarks = 0;
    for(auto word = words.begin() + 1; word != words.end(); word++)
    {
        if(word->length() % 2 == 1 and word->simplified().length() > 1)
        {
            word->remove(word->length()/2, 1);
            amountOfWords++;
        }
        else if (word->length() % 2 == 0 and word->simplified().length() > 1)
        {
            word->insert(word->length()/2, QChar(int(word->at(word->length()/2 - 1).unicode()) + 1));
            amountOfWords++;
        }
        else if(word->simplified().length() == 1 && word->simplified()[0].isPunct())
        {
            amountOfMarks++;
        }
    }
    std::cout << amountOfWords << " " << amountOfMarks << "\n";

    return 0;
}
