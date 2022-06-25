#ifndef RENAME_H
#define RENAME_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QString>

class Controller;

class Rename : public QDialog {
private:
    Controller* controller;
    QLineEdit* t_input;
    QLineEdit* d_input;
    QString title;
    QString desc;
    QPushButton* apply;
    QPushButton* cancel;
public:
    Rename(QString ="", QString ="");
    void SetController(Controller*);
    QString getTitle() const;
    QString getDescription() const;
    ~Rename();
};

#endif // RENAME_H
