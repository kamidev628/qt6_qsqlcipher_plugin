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
    : QMainWindow(parent)
{
    db = new QSqlDatabase();
    *db = QSqlDatabase::addDatabase("QSQLCIPHER");
    db->setDatabaseName("encrypted.db");

    if (db->open()) {
        qDebug() << "Database opened successfully!";
        qDebug() << "Available drivers: " << QSqlDatabase::drivers();

        QSqlQuery query(*db);
        query.exec("PRAGMA key = 'your-encryption-key';");  // Apply key

        if (!query.exec("CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY, name TEXT)")) {
            qDebug() << "Table creation error:" << query.lastError().text();
        }

        if (!query.exec("INSERT INTO users (name) VALUES ('John Doe')")) {
            qDebug() << "Insert error:" << query.lastError().text();
        }

    } else {
        qDebug() << "Error opening database:" << db->lastError();
    }

    mainWidget = new QWidget(this);
    setCentralWidget(mainWidget);

    mainLayout = new QVBoxLayout(this->centralWidget());
    mainTable = new QTableWidget(this->centralWidget());

    mainTable->setColumnCount(2);
    mainTable->setColumnWidth(0, 80);
    mainTable->setColumnWidth(1, 300);

    form = new QWidget(this->centralWidget());
    formLayout = new QHBoxLayout(form);

    input = new QLineEdit(form);
    addBtn = new QPushButton("Add", form);

    connect(addBtn, &QPushButton::clicked, this, [this]() {
        if (db->open()) {
            QSqlQuery query(*db);
            query.exec("PRAGMA key = 'your-encryption-key';");
            query.prepare("INSERT INTO users (name) VALUES (:name)");
            query.bindValue(":name", input->text());

            if (!query.exec()) {
                qDebug() << "Insert error:" << query.lastError().text();
            }

            refreshTable();
        } else {
            qDebug() << "Error opening database:" << db->lastError();
        }
    });

    addBtn->setFixedWidth(50);

    formLayout->setContentsMargins(0, 0, 0, 0);
    formLayout->setSpacing(9);
    formLayout->addWidget(input);
    formLayout->addWidget(addBtn);
    form->setLayout(formLayout);

    mainLayout->setContentsMargins(9, 9, 9, 9);
    mainLayout->setSpacing(9);
    mainLayout->addWidget(mainTable);
    mainLayout->addWidget(form);
    this->centralWidget()->setLayout(mainLayout);

    resize(600, 400);
    refreshTable();
}

MainWindow::~MainWindow() {}

void MainWindow::refreshTable() {
    if (db->open()) {
        QSqlQuery query(*db);
        query.exec("PRAGMA key = 'your-encryption-key';");

        if (!query.exec("SELECT id, name FROM users")) {
            qDebug() << "Select query error:" << query.lastError().text();
        }

        mainTable->clear();
        mainTable->setRowCount(0);
        mainTable->setHorizontalHeaderLabels(QStringList() << "ID" << "Name");

        while (query.next()) {
            int id = query.value(0).toInt();
            QString name = query.value(1).toString();
            int row = mainTable->rowCount();
            mainTable->insertRow(row);
            mainTable->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
            mainTable->setItem(row, 1, new QTableWidgetItem(name));
        }
    } else {
        qDebug() << "Error opening database:" << db->lastError();
    }
}
