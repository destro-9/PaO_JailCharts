#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QSpinBox>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QLabel>
#include <QDialogButtonBox>
#include <QTextEdit>

class Controller;

class NewWindow : public QDialog {
private:
    Controller* controller;
    QSpinBox* rows;
    QComboBox* WhatChart;
    QLineEdit* WhatTitle;
    QTextEdit* Description;
    QPushButton* apply;
    QPushButton* cancel;
public:
    NewWindow(QWidget* =nullptr);
    void SetController(Controller*);
    int RowsValue() const;
    QString getTitle() const;
    QString getDescription() const;
    int getComboIndex() const;
    ~NewWindow();
};

#endif // NEWWINDOW_H
