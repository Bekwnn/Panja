#include "pspellchecker.h"

PSpellChecker::PSpellChecker(const QString &dictionaryPath, const QString &userDictionary, const QString &projectDictionary)
{
    this->userDictionary = userDictionary;
    this->projectDictionary = projectDictionary;

    QString dictFile = dictionaryPath + ".dic";
    QString affixFile = dictionaryPath + ".aff";
    QByteArray dictFilePathBA = dictFile.toLocal8Bit();
    QByteArray affixFilePathBA = affixFile.toLocal8Bit();
    //_hunspell = new Hunspell(affixFilePathBA.constData(), dictFilePathBA.constData());
}

PSpellChecker::~PSpellChecker()
{

}

