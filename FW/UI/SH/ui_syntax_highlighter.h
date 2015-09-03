#ifndef UISYNTAXHIGHLIGHTER_H
#define UISYNTAXHIGHLIGHTER_H

#include "FW/variant.h"
#include <QSyntaxHighlighter>
#include <QTextCharFormat>

class QTextDocument;

class TypeUiSyntaxHighlighter : public QSyntaxHighlighter, public TypeVariant
{
    Q_OBJECT

public:
    TypeUiSyntaxHighlighter( QString rules_file, TypeVariant* variant = 0, QTextDocument* parent = 0 );

protected:

    void highlightBlock( const QString& text ) Q_DECL_OVERRIDE;

private:

    struct TypeHighlightingRule
    {
        QString name;
        QTextCharFormat format;
        QStringList tokens;
    };

    QVector<TypeHighlightingRule> m_HighlightingRules;
    QVector<TypeHighlightingRule> m_CommentHighlightingRules;

};

#endif // UISYNTAXHIGHLIGHTER_H
