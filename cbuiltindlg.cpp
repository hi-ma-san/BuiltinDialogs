#include "cbuiltindlg.h"
#include <QGridLayout>
#include <QDebug>
#include <QWidget> /*所有元件都引入 編譯速度較慢*/

/*printer*/
#include <QtPrintSupport/QPrinter.h>
#include <QtPrintSupport/qpagesetupdialog.h>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>

CBuiltinDlg::CBuiltinDlg(QWidget *parent)
    : QDialog(parent)
{
    QGridLayout *gridLayout = new QGridLayout;
    displayTextEdit = new QTextEdit(QStringLiteral("Qt標準通用對話盒"));
    colorPushBtn    = new QPushButton(QStringLiteral("顏色對話盒"));
    errorPushBtn    = new QPushButton(QStringLiteral("錯誤訊息盒"));
    filePushBtn     = new QPushButton(QStringLiteral("檔案對話盒"));
    fontPushBtn     = new QPushButton(QStringLiteral("字體對話盒"));
    inputPushBtn    = new QPushButton(QStringLiteral("輸入對話盒"));
    pagePushBtn     = new QPushButton(QStringLiteral("頁面設定對話盒"));
    progressPushBtn = new QPushButton(QStringLiteral("進度條對話盒"));
    printPushBtn    = new QPushButton(QStringLiteral("列印對話盒"));
    textColorPushBtn = new QPushButton(QStringLiteral("字體顏色對話盒"));

    gridLayout->addWidget(colorPushBtn, 0, 0, 1, 1); //addwidget(item, col, row, h, w)
    gridLayout->addWidget(errorPushBtn, 0, 1, 1, 1);
    gridLayout->addWidget(filePushBtn, 0, 2, 1, 1);
    gridLayout->addWidget(fontPushBtn, 1, 0, 1, 1);
    gridLayout->addWidget(inputPushBtn, 1, 1, 1, 1);
    gridLayout->addWidget(pagePushBtn, 1, 2, 1, 1);
    gridLayout->addWidget(progressPushBtn, 2, 0, 1, 1);
    gridLayout->addWidget(printPushBtn, 2, 1, 1, 1);
    gridLayout->addWidget(displayTextEdit, 3, 0, 3, 3);
    gridLayout->addWidget(textColorPushBtn, 2, 2, 1, 1);
    //以上將QPushButton元件以及QTextEdit納入gridLayout管理

    setLayout(gridLayout); //將目前對話盒視窗設為gridLayout

    setWindowTitle(tr("內建對話盒函式"));
    resize(400, 300);

    //鍊結至槽函數
    connect(colorPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));      //當colorPushBtn clicked 則把訊號呼叫至doPushBtn()
    connect(errorPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(filePushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));       //鍊結
    connect(progressPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(fontPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(inputPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(pagePushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));
    connect(printPushBtn, SIGNAL(clicked()), this, SLOT(doPushBtn()));

    connect(textColorPushBtn, SIGNAL(clicked()), this, SLOT(doTextColor()));  //字形顏色

}

CBuiltinDlg::~CBuiltinDlg() {}

//::範圍運算子
void CBuiltinDlg::doPushBtn() //slot 實作
{
    //將sender強迫轉型成QPushButton的指標
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    //sender 為訊號傳送者

    if (btn == colorPushBtn)
    {
        //qDebug() << "Hello World!";
        // 取得 displayTextEdit 目前使用的調色盤（QPalette）
        QPalette palette = displayTextEdit->palette();
        // QColorDialog::getColor() 呼叫標準顏色選擇對話框
        // 這是一個靜態方法 (static function)
        //
        // getColor(預設顏色, 父視窗, 對話框標題)
        //
        // palette.color(QPalette::Base)：
        //   - 取得文字編輯框背景的顏色（Base 是主要內容區域的顏色角色 也就是背景顏色）
        //   - 作為顏色選擇器的初始顏色
        //
        // this：
        //   - 表示以「CBuiltinDlg 對話框」作為父視窗
        //
        //
        // tr("設定背景顏色")：
        //   - 對話框標題，可支援多語系翻譯

        //回傳為QColor 的顏色物件
        const QColor &color =
            QColorDialog::getColor(palette.color(QPalette::Base),
                                                     this, tr("設定背景顏色"));

        if (color.isValid()) //數值合法
        {
            palette.setColor(QPalette::Base, color);
            displayTextEdit->setPalette(palette);
            //qDebug() << color;
        }
    }
    else if (btn == errorPushBtn)
    {
        QErrorMessage box(this);
        box.setWindowTitle(tr("錯誤訊息盒"));
        box.showMessage(tr("錯誤訊息盒實例xx"));
        box.showMessage(tr("錯誤訊息盒實例yy"));
        box.showMessage(tr("錯誤訊息盒實例zz"));

        box.exec();
    }
    else if(btn == fontPushBtn)
    {
        bool ok;
        const QFont &font = QFontDialog::getFont(&ok, displayTextEdit->font(), this, tr("字體對話盒"));
        if (ok) displayTextEdit -> setFont(font);
    }
    else if(btn == filePushBtn)
    {
        //getOpenFileName(父視窗, titel, 工作目錄, 過濾檔案);
        //回傳 檔案絕對路徑/檔案名稱
        QString fileName = QFileDialog::getOpenFileName(this, tr("開啟檔案"), ".", tr("任何檔案(*.*)"
                                                                                      ";;文字檔(*.txt)"
                                                                                      ";;XML檔(*.xml)"));

        //如果是存檔需要改成getSaveFileName

        displayTextEdit->setText(fileName);
    }
    else if(btn == inputPushBtn)
    {
        bool ok;
        QString text = QInputDialog::getText(this,
                                             tr("輸入對話盒"),
                                             tr("輸入文字"),
                                             QLineEdit::Normal,
                                             QDir::home().dirName(),
                                             &ok);
        if (ok && !text.isEmpty()) displayTextEdit->setText(text);
    }
    else if(btn == pagePushBtn)
    {
        QPrinter printer(QPrinter::HighResolution);
        QPageSetupDialog *dlg = new QPageSetupDialog(&printer, this);
        dlg -> setWindowTitle(QStringLiteral("頁面設定方塊"));
        if (dlg -> exec() == QDialog::Accepted)
        {

        }
    }
    else if(btn == progressPushBtn)
    {
        QProgressDialog progress(tr("正在複製檔案..."), tr("取消"), 0, 100, this);
        progress.setWindowTitle(tr("進度條對話盒"));
        progress.show();
        for (int i = 0; i <= 100; i++)
        {
            progress.setValue(i);
            //QCoreApplication::processEvents(); //讓視窗不要被凍結 使得進度條正常顯示
            qApp->processEvents(); //等效上面的功能
            QThread::msleep(30); // 模擬延遲 (30ms)
            qDebug() << i;
            if (progress.wasCanceled())
            {
                displayTextEdit->setText("取消進度");
                break;

            }
        }
    }
    else if(btn == printPushBtn)
    {
        QPrinter printer(QPrinter::HighResolution);
        QPrintDialog dialog(&printer, this);
        if (dialog.exec() != QDialog::Accepted)
        {
            return;
        }
    }
}

void CBuiltinDlg::doTextColor() //slot 實作
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if(btn == textColorPushBtn)
    {
        QPalette palette = displayTextEdit->palette();
        const QColor &color =
            QColorDialog::getColor(palette.color(QPalette::Text),
                                   this, tr("設定字形顏色"));
        if (color.isValid()) //數值合法
        {
            palette.setColor(QPalette::Text, color);
            displayTextEdit->setPalette(palette);
            //qDebug() << color;
        }
    }
}
