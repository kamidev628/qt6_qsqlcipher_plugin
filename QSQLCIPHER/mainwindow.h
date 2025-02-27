#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

class QVBoxLayout;
class QHBoxLayout;
class QTableWidget;
class QPushButton;
class QLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QSqlDatabase db;  // Use stack-allocated database object
    QWidget *mainWidget = nullptr;
    QVBoxLayout *mainLayout = nullptr;
    QHBoxLayout *formLayout = nullptr;
    QTableWidget *mainTable = nullptr;
    QWidget *form = nullptr;
    QLineEdit *input = nullptr;
    QPushButton *addBtn = nullptr;

    void applyDatabaseKey();  // Helper function to set encryption key
    void setupUI();           // Helper function for UI setup

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void refreshTable();
    void addUserToDatabase();
};

#endif // MAINWINDOW_H
