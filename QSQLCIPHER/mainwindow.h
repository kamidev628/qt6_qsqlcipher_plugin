#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QSqlDatabase;

class QVBoxLayout;
class QHBoxLayout;
class QTableWidget;
class QPushButton;
class QLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QSqlDatabase *db = nullptr;
    QWidget *mainWidget = nullptr;
    QVBoxLayout *mainLayout = nullptr;
    QHBoxLayout *formLayout = nullptr;
    QTableWidget *mainTable = nullptr;
    QWidget *form = nullptr;
    QLineEdit *input = nullptr;
    QPushButton *addBtn = nullptr;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void refreshTable();
};
#endif // MAINWINDOW_H
