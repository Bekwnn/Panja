#ifndef PSPELLCHECKER_H
#define PSPELLCHECKER_H

#include <QString>

class PSpellChecker
{
public:
    PSpellChecker(const QString &dictionaryPath, const QString &userDictionary, const QString &projectDictionary);
    ~PSpellChecker();

    void addWordToUserDictionary(QString word);
    void addWordToProjectDictionary(QString word);
private:
    QString userDictionary;
    QString projectDictionary;
};

#endif // PSPELLCHECKER_H
