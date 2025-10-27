#ifndef CBUILTINDLG_H
#define CBUILTINDLG_H

#include <QDialog>
#include <QtWidgets>
#include <QTextEdit>
#include <QPushButton>


class CBuiltinDlg : public QDialog //class 子類別 : public 父類別
{
    Q_OBJECT //巨集

public:
    CBuiltinDlg(QWidget *parent = nullptr); //建構子
    ~CBuiltinDlg(); //解構子
private:
    QTextEdit   *displayTextEdit;
    QPushButton *colorPushBtn;
    QPushButton *errorPushBtn;
    QPushButton *filePushBtn;
    QPushButton *fontPushBtn;
    QPushButton *inputPushBtn;
    QPushButton *pagePushBtn;
    QPushButton *progressPushBtn;
    QPushButton *printPushBtn;
    QPushButton *textColorPushBtn;

private slots: //for 槽函數(slot)宣告
    void doPushBtn();
    void doTextColor();
};
#endif // CBUILTINDLG_H
