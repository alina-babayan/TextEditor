#include <QApplication>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>
#include <QMainWindow>
#include <QAction>
#include <QTextEdit>
#include <QTabWidget>
#include <QInputDialog>
#include <QString>
#include <QMessageBox>

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    QMainWindow window;
    window.resize(600, 400);

    QTabWidget* tabWidget = new QTabWidget(&window);
    tabWidget->setTabsClosable(true);
    tabWidget->setMovable(true);
    window.setCentralWidget(tabWidget);

    QMenuBar* menuBar = window.menuBar();

    QMenu* fileMenu = menuBar->addMenu("File");

    // QAction* newProject = fileMenu->addAction("New Project");
    // newProject->setShortcut(QKeySequence::New);

    QAction* newFile = fileMenu->addAction("New File");
    newFile->setShortcut(QKeySequence::New);

    QAction* saveAll = fileMenu->addAction("Save All");
    saveAll->setShortcut(QKeySequence::SaveAs);

    QMenu* recentFiles = new QMenu("Recent Files", &window);
    fileMenu->addMenu(recentFiles);
    QAction* mainCpp = recentFiles->addAction("1|C:/USER/Documents/task5/main.cpp");
    QAction* task5Pro = recentFiles->addAction("2|C:/USER/Documents/task5/task5.pro");
    QAction* paint = recentFiles->addAction("3|C:/USER/Documents/Picsart_QT/Paint/Paint/main.cpp");

    QAction* closeAll = fileMenu->addAction("Close All");
    closeAll->setShortcut(QKeySequence::Close);

    QAction* print = fileMenu->addAction("Print");
    print->setShortcut(QKeySequence::Print);

    QAction* exit = fileMenu->addAction("Exit");

    QMenu* editMenu = menuBar->addMenu("Edit");
    QAction* undo = editMenu->addAction("Undo");
    undo->setShortcut(QKeySequence::Undo);

    QAction* redo = editMenu->addAction("Redo");
    redo->setShortcut(QKeySequence::Redo);

    QAction* cut = editMenu->addAction("Cut");
    cut->setShortcut(QKeySequence::Cut);

    QAction* copy = editMenu->addAction("Copy");
    copy->setShortcut(QKeySequence::Copy);

    QToolBar* toolBar = new QToolBar("Main Toolbar", &window);
    window.addToolBar(toolBar);
    //toolBar->addAction(newFile);

    QObject::connect(newFile, &QAction::triggered, [&](){
        bool ok;
        QString fileName = QInputDialog::getText(&window, "New File", "Enter file name:", QLineEdit::Normal, "", &ok);
        if (ok && !fileName.isEmpty()) {
            for (int i = 0; i < tabWidget->count(); ++i) {
                if (tabWidget->tabText(i) == fileName) {
                    QMessageBox::warning(&window, "Error", "A file with this name is already open!");
                    return;
                }
            }

            QTextEdit* textEdit = new QTextEdit();
            int index = tabWidget->addTab(textEdit, fileName);
            tabWidget->setCurrentIndex(index);
        }
    });

    // QObject::connect(newProject, &QAction::triggered, [&](){
    //     QTextEdit* textEdit = new QTextEdit();
    //     int index = tabWidget->addTab(textEdit, "New Project");
    //     tabWidget->setCurrentIndex(index);
    // });

    QObject::connect(mainCpp, &QAction::triggered, [&](){
        QTextEdit* textEdit = new QTextEdit();
        textEdit->setText("// main.cpp content here...");
        int index = tabWidget->addTab(textEdit, "main.cpp");
        tabWidget->setCurrentIndex(index);
    });

    QObject::connect(task5Pro, &QAction::triggered, [&](){
        QTextEdit* textEdit = new QTextEdit();
        textEdit->setText("# task5.pro content here...");
        int index = tabWidget->addTab(textEdit, "task5.pro");
        tabWidget->setCurrentIndex(index);
    });

    QObject::connect(paint, &QAction::triggered, [&](){
        QTextEdit* textEdit = new QTextEdit();
        textEdit->setText("// Paint main.cpp content here...");
        int index = tabWidget->addTab(textEdit, "Paint.cpp");
        tabWidget->setCurrentIndex(index);
    });

    QObject::connect(exit, &QAction::triggered, &app, &QApplication::quit);


    QObject::connect(closeAll, &QAction::triggered, [&](){
        while (tabWidget->count() > 0) {
            QWidget* widget = tabWidget->widget(0);
            tabWidget->removeTab(0);
            delete widget;
        }
    });
    QObject::connect(tabWidget, &QTabWidget::tabCloseRequested,
                     [&](int index){
                         QWidget* widget = tabWidget->widget(index);
                         tabWidget->removeTab(index);
                         delete widget;

    });

    window.show();
    return app.exec();
}
