#include "mainwindow.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), db(QSqlDatabase::addDatabase("QSQLCIPHER"))
{
    db.setDatabaseName("encrypted.db");

    if (db.open()) {
        qDebug() << "Database opened successfully!";
        qDebug() << "Available drivers: " << QSqlDatabase::drivers();

        applyDatabaseKey();

        QSqlQuery query(db);
        if (!query.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT)")) {
            qDebug() << "Table creation error:" << query.lastError().text();
        }

        if (!query.exec("INSERT INTO users (name) VALUES ('John Doe')")) {
            qDebug() << "Insert error:" << query.lastError().text();
        }
    } else {
        qDebug() << "Error opening database:" << db.lastError();
    }

    setupUI();
    refreshTable();
}

MainWindow::~MainWindow() {}

void MainWindow::applyDatabaseKey() {
    QSqlQuery query(db);
    if (!query.exec("PRAGMA key = 'your-encryption-key';")) {
        qDebug() << "Failed to apply encryption key:" << query.lastError().text();
    }
}

void MainWindow::setupUI() {
    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    mainLayout = new QVBoxLayout(mainWidget);
    mainTable = new QTableWidget(mainWidget);
    mainTable->setColumnCount(2);
    mainTable->setHorizontalHeaderLabels({"ID", "Name"});
    mainTable->setColumnWidth(0, 80);
    mainTable->setColumnWidth(1, 300);

    form = new QWidget(mainWidget);
    formLayout = new QHBoxLayout(form);
    input = new QLineEdit(form);
    addBtn = new QPushButton("Add", form);
    addBtn->setFixedWidth(50);

    connect(addBtn, &QPushButton::clicked, this, &MainWindow::addUserToDatabase);

    formLayout->addWidget(input);
    formLayout->addWidget(addBtn);
    form->setLayout(formLayout);

    mainLayout->addWidget(mainTable);
    mainLayout->addWidget(form);
    mainWidget->setLayout(mainLayout);

    resize(600, 400);
}

void MainWindow::addUserToDatabase() {
    if (db.isOpen()) {
        applyDatabaseKey();
        QSqlQuery query(db);
        query.prepare("INSERT INTO users (name) VALUES (:name)");
        query.bindValue(":name", input->text());

        if (!query.exec()) {
            qDebug() << "Insert error:" << query.lastError().text();
        } else {
            input->clear();
            refreshTable();
        }
    } else {
        qDebug() << "Database is not open!";
    }
}

void MainWindow::refreshTable() {
    if (!db.isOpen()) {
        qDebug() << "Database is not open!";
        return;
    }

    applyDatabaseKey();
    QSqlQuery query(db);
    if (!query.exec("SELECT id, name FROM users")) {
        qDebug() << "Select query error:" << query.lastError().text();
        return;
    }

    mainTable->setRowCount(0);
    int row = 0;
    while (query.next()) {
        mainTable->insertRow(row);
        mainTable->setItem(row, 0, new QTableWidgetItem(query.value(0).toString()));
        mainTable->setItem(row, 1, new QTableWidgetItem(query.value(1).toString()));
        row++;
    }
}
